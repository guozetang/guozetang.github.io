---
title: Bro源代码分析---IP数据包处理流程
date: 2018-06-09 01:02:39
categories: Network
tags: Network
---
# 前言
Bro是一款非常优秀的网络协议分析器。Bro里面的Binpac解析器可以很方便的让我们使用Binpac语言书写协议解析器，并通过Binpac转换成C++语言，这在使用中能够很大程度的减少开发时间，也可以避免手写容易考虑不全的问题。但是在使用Binpac之前，我们需要去了解Bro在处理网络数据包的时候的处理流程，能够方便我们在Binpac使用中去掉和Bro耦合的部分，生成我们需要的协议解析器的C++文件。
<!--more-->

# 源代码阅读
> 重点：关注于网络数据包的处理部分代码

## Bro的网络数据包处理流程  
### Bro启动初始化函数main.cc

> int main(int argc, char** argv) (main.cc)

![2018-06-09Bro-Main](/images/in-post/2018-06-09Bro-Main.png) 

在Bro的`main.cc`文件里面的Main函数是Bro启动过程中的首先执行的函数，而在这个`main`函数里面，和我们的数据包处理部分相关密切的函数是`net_run()`函数，这个函数是一个一直循环的函数，一旦出来这个函数之后，后面差不多就结束了。接下来阅读该函数代码。

### 数据包处理的主要函数： net_run()
> net_run() (Net.cc)
```cpp
void net_run()
	{
	set_processing_status("RUNNING", "net_run");

	while ( iosource_mgr->Size() ||
		(BifConst::exit_only_after_terminate && ! terminating) )
		{
		double ts;
		iosource::IOSource* src = iosource_mgr->FindSoonest(&ts); //打开之后，获取所以的网卡或者文件的句柄

		current_iosrc = src;
		bool communication_enabled = using_communication;

		if ( src )  //如果这个句柄不是空的话就进入Process()函数
			src->Process();	// which will call net_packet_dispatch()

		else if ( reading_live && ! pseudo_realtime)
			{ // live but  no source is currently active
			double ct = current_time();
			if ( ! net_is_processing_suspended() )
				{
				net_update_time(ct);
				expire_timers();
				usleep(1); // Just yield.
				}
			}

		else if ( (have_pending_timers || communication_enabled) &&
			  ! pseudo_realtime )
			{

			net_update_time(current_time());
			expire_timers();

			if ( ! communication_enabled )
				usleep(100000);
			else
				usleep(1000);

		mgr.Drain();

		processing_start_time = 0.0;	// = "we're not processing now"
		current_dispatched = 0;
		current_iosrc = 0;

		extern void termination_signal();

		if ( signal_val == SIGTERM || signal_val == SIGINT )

			termination_signal();

		if ( ! reading_traces )
			have_pending_timers = timer_mgr->Size() > 0;
		}
	net_get_final_stats();
	}

```

这个函数并不是很长，仔细阅读，我们可以发现我们只需要关注函数`src->Process`, 其中`src`是`iosource::IOSource* src = iosource_mgr->FindSoonest(&ts);`相当于就是打开文件或者网卡数据的句柄（文件句柄或者网卡的句柄）。所以它的处理函数也就是我们想要的数据处理过程了。

![2018-06-09-Bro_net_run](/images/in-post/2018-06-09-Bro_net_run.png) 

接下来看`Process`函数,在这个函数中我们可以看到它处理了Packet，处理完之后，调用了一个`DoneWithPacket()`函数，但我们重点是关注的处理过程，所以我们需要关注函数`net_packet_dispatch(net_packet_dispatch(current_pseudo, &current_packet, this);)`,在这个函数中传入了当前数据包的指针。

> void Pktsrc::Process() (Pktsrc.cc)

![2018-06-09-src_process](/images/in-post/2018-06-09-src_process.png) 

接下来阅读`net_packet_dispatch(current_pseudo, &current_packet, this);`的处理过程。这个函数是在`net.cc`文件中，和`net_run()`函数是在同一个文件中。
> void net_packet_dispatch(double t, const Packet* pkt, iosource::PktSrc* src_ps) (net.cc)

![2018-06-09-net_packet_dispatch](/images/in-post/2018-06-09-net_packet_dispatch.png)

在`net_packet_dispatch()`函数中，有一个特别重要的数据结构`sessions`,这是在`sessions.cc`文件中定义的一个全局变量。  
`NetSessions* sessions;`   
在这里我们需要阅读一下结构体`NetSessions`,这个结构体是在`sessions.h`文件中定义的。在这个结构体中有一个特别重要的函数`NextPacket`,这个函数也是在`net_packet_dispatch`中被调用的最重要的函数。

![2018-06-09-NetSessions_class](/images/in-post/2018-06-09-NetSessions_class.png) 

接下来阅读关键函数：`NextPacket`

> void NetSessions::NextPacket(double t, const Packet* pkt) (sessions.cc)

```cpp
void NetSessions::NextPacket(double t, const Packet* pkt) //t可能是时间戳
	{
	SegmentProfiler(segment_logger, "dispatching-packet");

        .....
  
	if ( pkt->hdr_size > pkt->cap_len ) //开始判断包的大小问题
		{
		Weird("truncated_link_frame", pkt);
		return;
		}

	uint32 caplen = pkt->cap_len - pkt->hdr_size; 
  //cap_len抓到的数据包的大小， hdr_size --- IP头里面的显示长度

	if ( pkt->l3_proto == L3_IPV4 )
		{
		if ( caplen < sizeof(struct ip) ) 
			{
			Weird("truncated_IP", pkt);
			return;
			}

		const struct ip* ip = (const struct ip*) (pkt->data + pkt->hdr_size);
		IP_Hdr ip_hdr(ip, false);
		DoNextPacket(t, pkt, &ip_hdr, 0);
		}

	else if ( pkt->l3_proto == L3_IPV6 )
		{
                  .....
		DoNextPacket(t, pkt, &ip_hdr, 0);
		}

	else if ( pkt->l3_proto == L3_ARP )
		{
		if ( arp_analyzer )
			arp_analyzer->NextPacket(t, pkt);
		}
              .......

	if ( dump_this_packet && ! record_all_packets )
		DumpPacket(pkt);
	}

```
经过分析，上述的代码中，最重要的是函数`DoNextPacket(t, pkt, &ip_hdr, 0)`,把数据包传入，指向ip头的指针传入。这个函数可以说是我们要找的最重要的函数了，在这个函数中，完成了`IP头`重组工作。
> void NetSessions::DoNextPacket(double t, const Packet* pkt, const IP_Hdr* ip_hdr,
			       const EncapsulationStack* encapsulation) (Sessions.cc)

![2018-06-09-DoNextPacket_Main](/images/in-post/2018-06-09-DoNextPacket_Main.png) 
这个函数已经开始处理IP数据包了,在这个函数里面，最主要的部分是处理片段的部分工作：


![2018-06-09-DoNextPacket_fuction](/images/in-post/2018-06-09-DoNextPacket_fuction.png) 

再初始化`f`之前，执行了：
```cpp
	if ( discarder && discarder->NextPacket(ip_hdr, len, caplen) )
		return;

	FragReassembler* f = 0;

	if ( ip_hdr->IsFragment() )
		{
		dump_this_packet = 1;	// always record fragments
```
主要看一下`NextPacket函数`的执行过程:
在这个函数中主要检查了IP数据包，判断是TCP还是UDP，然后处理IP嵌套的情况。
```cpp

int Discarder::NextPacket(const IP_Hdr* ip, int len, int caplen)
	{
	int discard_packet = 0;

	if ( check_ip )
		{
		val_list* args = new val_list;
		args->append(ip->BuildPktHdrVal());

		try
			{
			discard_packet = check_ip->Call(args)->AsBool();
			}

		catch ( InterpreterException& e )
			{
			discard_packet = false;
			}

		delete args;

		if ( discard_packet )
			return discard_packet;
		}

	int proto = ip->NextProto();
	if ( proto != IPPROTO_TCP && proto != IPPROTO_UDP &&
	     proto != IPPROTO_ICMP )
		// This is not a protocol we understand.
		return 0;

	// XXX shall we only check the first packet???
	if ( ip->IsFragment() )
		// Never check any fragment.
		return 0;

	int ip_hdr_len = ip->HdrLen();
	len -= ip_hdr_len;	// remove IP header
	caplen -= ip_hdr_len;

	int is_tcp = (proto == IPPROTO_TCP);
	int is_udp = (proto == IPPROTO_UDP);
	int min_hdr_len = is_tcp ?
		sizeof(struct tcphdr) :
		(is_udp ? sizeof(struct udphdr) : sizeof(struct icmp));

	if ( len < min_hdr_len || caplen < min_hdr_len )
		// we don't have a complete protocol header
		return 0;

	// Where the data starts - if this is a protocol we know about,
	// this gets advanced past the transport header.
	const u_char* data = ip->Payload();

	if ( is_tcp )
		{
		if ( check_tcp )
			{
			const struct tcphdr* tp = (const struct tcphdr*) data;
			int th_len = tp->th_off * 4;

			val_list* args = new val_list;
			args->append(ip->BuildPktHdrVal());
			args->append(BuildData(data, th_len, len, caplen));

			try
				{
				discard_packet = check_tcp->Call(args)->AsBool();
				}

			catch ( InterpreterException& e )
				{
				discard_packet = false;
				}

			delete args;
			}
		}

	else if ( is_udp )
		{
		if ( check_udp )
			{
			const struct udphdr* up = (const struct udphdr*) data;
			int uh_len = sizeof (struct udphdr);

			val_list* args = new val_list;
			args->append(ip->BuildPktHdrVal());
			args->append(BuildData(data, uh_len, len, caplen));

			try
				{
				discard_packet = check_udp->Call(args)->AsBool();
				}

			catch ( InterpreterException& e )
				{
				discard_packet = false;
				}

			delete args;
			}
		}

	else
		{
		if ( check_icmp )
			{
			const struct icmp* ih = (const struct icmp*) data;

			val_list* args = new val_list;
			args->append(ip->BuildPktHdrVal());

			try
				{
				discard_packet = check_icmp->Call(args)->AsBool();
				}

			catch ( InterpreterException& e )
				{
				discard_packet = false;
				}

			delete args;
			}
		}

	return discard_packet;
	}

```

在这里主要是关键是四个部分
- FragReassembler* f = 0; 定义片段重组标志位为0
- f = NextFragment(t, ip_hdr, pkt->data + pkt->hdr_size); 得到下一个片段的指针
- const IP_Hdr* ih = f->ReassembledPkt();
- FragReassemblerTracker frt(this, f);

### 详细分析DoNextPacket函数的处理过程
#### FragReassembler类结构解析
> class FragReassembler (Frag.h)

需要看一下`FragReassembler`这个类里面的成员变量以及相应的函数。在这个类当中，最重要的函数是`ReassembledPkt`  
![2018-06-09-class-FragReassembler](/images/in-post/2018-06-09-class-FragReassembler.png) 

#### NextFragment函数处理过程
> FragReassembler* NetSessions::NextFragment(double t, const IP_Hdr* ip,
					const u_char* pkt) (sessions.cc)


![2018-06-09-FragReassembler-NextFragment](/images/in-post/2018-06-09-FragReassembler-NextFragment.png) 

在这个函数中，主要查找了fragment，如果没有下一个，就新建一个新的Fragment并添加到`fragments`的结构体里面去。

#### ReassembledPkt函数处理过程
这个函数的处理过程只有一条。
> ReassembledPkt() (Frag.h)   

`	const IP_Hdr* ReassembledPkt()	{ return reassembled_pkt; }`  

对应的`IP_Hdr* reassembled_pkt;`,所以只是返回去了一个指针头


#### FragReassemblerTracker frt(this, f)处理过程


#### 处理Conn的过程
在`DoNextPacket`这个函数的最后，会去新建或者找到一个`Conn`处理处理数据包。执行代码:
> DoNextPacket()  (Sessions.cc)


![2018-06-09-DoNextPacket-new-conn](/images/in-post/2018-06-09-DoNextPacket-new-conn.png) 

在处理Conn这个部分的时候，检查是否有对应的`connection`,根据hash值去查询`HashKey* h = BuildConnIDHashKey(id);`,如果没有对应的`Conn`，那么就去新建一个，新建完之后，插入到connect的链表中。如果已经有了对应的`Conn`那就需要判断当前的`conn`是不是不正确的数据以及有没有被复用。如果有的话，删除对应的`conn`的Hash值。

