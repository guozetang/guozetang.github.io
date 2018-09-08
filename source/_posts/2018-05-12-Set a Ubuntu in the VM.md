---
title: 在VMware内构建一个外网可以访问的Ubuntu服务器
date: 2018-05-12 01:30:32
updated: 2018-05-12 01:30:32
categories: Network
tags: Linux
---
# 前言
每次使用学校Lab的时候，都会有在需要安装软件或者更新软件的时候，由于没有Root权限而导致自己需要重新想办法处理，或者换到VPS上去处理的情况发生。每当这个时候，都在考虑，是否可以在VM中构建一个自己在任何地方都可以访问的服务器？
<!--more-->
# 解决方案
## 设置静态IP地址
背景

在虚拟机下运行操作系统，尤其是Linux系统已经是非常常见的做法。有时你想在虚拟机下搭建一个(模拟)服务器来供主机访问，比如搭建一个telnet/ssh。此时你会发现，每次启动虚拟机，VMWare为虚拟机系统分配一个动态IP，这样每次去连接虚拟机的telnet时很不方便。如果设成静态IP就好了。

VMnet8和NAT

如果你的虚拟机是以NAT方式连入互联网的话，那么虚拟机的IP地址非配，网关以及互联网访问权限均由VMWare提供的叫做VMnet8虚拟网卡所提供。所以一切和设置静态IP有关的设置都可以从这里找到。通VMnet8虚拟网卡，主机可以访问虚拟机的IP，虚拟机可以连入主机的互联网连接连入外网。

确认VMnet8虚拟网卡已启用

在默认情况下，VMWare Workstation已经启用VMnet8虚拟网卡，Windows 7下，通过进入 控制面板>网络和Internet>网络和共享中心>更改适配器设置 可以查看该虚拟网卡的状态。如图1-1所示。

![2018-05-20 NAT network information](/images/in-post/2018-05-20NATNetworkInformation.png) 

得到可用IP范围、网关和子网掩码

在VMWare主界面，点击Edit>Virtual Network Editor菜单进入虚拟网卡参数设置界面（图1-2）。选择VMnet8条目，点击NAT Settings按钮后可以看到我们的VMWare Workstation为NAT连接的虚拟机设定的默认网关，此处为192.168.91.2，以及子网掩码，此处为255.255.255.0, 如图1-3所示。


![Get some ipaddress which you can use](/images/in-post/getSomeIpaddressWhichYouCanUse.png) 


![2018-05-20 ](/images/in-post/2018-05-20.png) 
点击DHCP Settings按钮，可以看到VMnet8为虚拟机分配的可用的子网IP范围，如图1-4所示。


![2018-05-20可用的IP地址范围](/images/in-post/2018-05-20可用的IP地址范围.png) 


在这里，我们可以得到
OK，至此，所有我们需要的信息都已经获取到，这里汇总一下，

- 子网IP可用范围：192.168.91.128~192.168.91.254

- 子网掩码：255.255.255.0

- 网关: 192.168.91.2

下面开始进入Ubuntu虚拟机设置静态IP。


Ubuntu设置IP得知

1. 启动虚拟机Ubuntu系统，打开终端，利用如下命令打开并编辑网络接口配置文件：

sudo vi /etc/network/interfaces
2. 编辑文件如下：

复制代码
auto lo
iface lo inet loopback

# Assgin static IP by eric on 26-SEP-2012
iface eth0 inet static
address 192.168.91.200 #change to your static IP
netmask 255.255.255.0  #change to your netmask
gateway 192.168.91.2    #change to your getway
#We must specify dns-nameserver here
#in order to get internet access from host
dns-nameservers 192.168.91.2
auto eth0
复制代码
说明

address是你要分配给你虚拟机的静态IP地址，可以从刚才我们找到的可用的子网IP范围中随便选择一个放在此处。

netmask是子网掩码

gateway是网关

注意：在相对较早的版本中，你需要设置/etc下的resolv.conf文件，并加入nameserver，这样才可以连接互联网。但在Ubuntu 12.04之后，已经不推荐这种方式了，因为无论你想该配置文件中设置什么值，重新启动之后都会被还原为初始状态。推荐的做法是直接在interfaces配置文件中加入dns-nameserver <网关IP>这一行。

3. 重启ubuntu的网卡

sudo /etc/init.d/networking restart
4. ping测试互联网连通性

ping www.baidu.com
如果ping有响应，那么恭喜你，你已经成功将虚拟机设置为静态IP，并且也已连入互联网。




开启防火墙
ufw enable

关闭防火墙
ufw disable



如果虚拟机里能ping同本机，而本机却ping不通虚拟机，或者虚拟机不能ping通本机，可能有如下原因：

一，如果是桥接模式，那么可能性1：虚拟机防火墙禁ping，请关闭虚拟机防火墙重试；可能性2：桥接设置的ip有冲突或者是虚拟机桥接服务不正常。

二，如果是nat模式，那么可能性1：虚拟机防火墙禁ping，请关闭虚拟机防火墙重试；可能性2：本机上的vmnet8网卡被禁用了。可能性3：vbox的nat模式，vpc的共享模式，本来就这样的。


三，如果主机同时装了visualbox和vm，也会导致其中一个虚拟机ping不通主机，因此使用vm或vb时，在主机上禁用另一个虚拟网卡即可。


SSH分客户端openssh-client和openssh-server
如果你只是想登陆别的机器的SSH只需要安装openssh-client（ubuntu有默认安装，如果没有则sudo 
apt-get install openssh-client），如果要使本机开放SSH服务就需要安装openssh-server
sudo apt-get install openssh-server
然后确认sshserver是否启动了：
ps -e |grep ssh
如果看到sshd那说明ssh-server已经启动了。
如果没有则可以这样启动：sudo /etc/init.d/ssh start 或者 service ssh start
ssh-server配置文件位于/etc/ssh/sshd_config，在这里可以定义SSH的服务端口，默认端口是22，你可以自己定义成其他端口号，如222。
然后重启SSH服务：
sudo 
/etc/init.d/ssh stop
sudo /etc/init.d/ssh start
然后使用以下方式登陆SSH：
ssh username@192.168.1.112 username为192.168.1.112 机器上的用户，需要输入密码。




在刚安装完ubuntu后，屏幕不能全屏显示，此时：

 1、安装VMware Tools

 

 步骤：
  

    1.1     进入ubuntu系统后，点击虚拟机上的【虚拟机】->【安装 vmware tools】，回到桌面回看到一个vmware tools的 

 cdrom图标。

 

    1.2   复制 VMwareTools-10.0.10-4301679.tar.gz（版本根据自己的实际情况） 到/home/lance/目录下。  用命令【tar -xzvf  VMwareTools-10.0.10-4301679.tar.gz】解压。

 

     1.3    解压后 cd vmware_tools_distrib，打开终端



     1.4    输入“sudo ./vmware-install.pl”，输入用户密码便可开始安装了。

 

     1.5     接下来N多的enter，N多的YES，自己慢慢按吧。

 

     1.6   直到你看到—the vmware team 后 reboot 重启即可




     1.7  若还没有全屏显示，则将虚拟机的【查看】->【自动调整大小】->【自适应客户机】,都选上。即可实现全屏。

      1.8  安装vmware tools实现全屏后，即也实现了在主机（WIN7）和虚拟机VMware （ubuntu）间直接拖拽文件。

enjoy yourself


Ubuntu 16.04 执行下面命令默认启动到命令行：
$ sudo systemctl set-default multi-user.target
执行如下命令启动到桌面：
$ sudo systemctl start lightdm
