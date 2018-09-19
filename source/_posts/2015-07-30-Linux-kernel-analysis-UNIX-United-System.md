---
title: Linux内核分析课程9_UNIX United操作系统分析
date: 2015-05-07 13:04:27
updated: 2015-05-07 13:04:27
categories: Linux
tags: Linux kernel
---

Linux内核课第九周作业。本文在云课堂中实验楼完成。  
[唐国泽](http://guozet.me/about/) 原创作品转载请注明出处.  
[《Linux内核分析》MOOC课程](http://mooc.study.163.com/course/USTC-1000029000)

<!--more-->


UNIX操作系统，是一个强大的多用户、多任务操作系统，支持多种处理器架构，按照操作系统的分类，属于分时操作系统
>UNIX  United  is  an  architecture  for  a  distributed  system  based  on UNIX.    
>UNIX United可以看做是一种多台UNIX组成分布式系统的解决方案。

# 1.Introduction
UNIX United系统是通过将一组的UNIX系统计算机，在上层叠加一个系统方式，是值在操作的时候，完全隐藏所有的处理器通信和网络协议。并且所有的UNUX工作方式（如：设备保护，访问和文件访问，进程间通信，输入/输出，重定向）都是一样的，和独立的UNIX没有任何差别。
>参考文献：
《The Newcastle Connection or UNIXes of the world Unite!》
《The Architecture of UNIX United》
<!-- more -->
**疑问：对文件访问的控制是怎么处理的呢？**
# 2.对文件访问的处理

![](/images/in-post/2015-07-30-Linux-kernel-analysis-UNIX-United-System/2018-09-19-02-08-10.png)

简单的举一个例子，我们有两个独立的UNIX系统主机，现在将其构建成UNIX United System, 构建之后，UNIX1的用户如何读取UNIX2的文件呢？

![](/images/in-post/2015-07-30-Linux-kernel-analysis-UNIX-United-System/2018-09-19-02-08-21.png)

　　不知道大家是否还记得: **“ / ” 表示根目录，“** .. ”表示当前目录的上一层目录，那么问题来了，“ /..  ”表示什么呢？
> 如果在UNIX１主机上复制文件a到UNIX２上，可以这样操作。
> cp  /user/brian/a   /../unix2/user/brian/a
> 现在问题再一次出现，这个cp使用的是UNIX1中的cp还是UNIX2中的cp呢？

# ３.用户认证和访问权限控制

UNIX中用户认证相关的文件：用户，组，用户密码，Root
UNIX United System中，各个子UNIX System拥有自己独立的users,user groups and user password file,root; 但每个系统都有义务对要登录UNIX United System的用户进行认证，那怎么认证呢？
比如机器A上的用户u, 我们记为“A/u”，身份认证由A完成，但用户u可以访问所有A和B上属于该用户的文件。

# 4.连接通信-远程文件访问的处理

![](/images/in-post/2015-07-30-Linux-kernel-analysis-UNIX-United-System/2018-09-19-02-08-37.png)

在原有UNIX的基础上添加了一个通信链路和一个软件层, 这两部分的位置在UNIX Kernel和UNIX software之间。Newcastle Connection相当于是一个“过滤器”，过滤出要重定向其他系统的系统调用，而UNIX1和UNIX2之间的通信是通过远程过程调用(Remote Procedure Call，RPC)来交流的。

![](/images/in-post/2015-07-30-Linux-kernel-analysis-UNIX-United-System/2018-09-19-02-09-48.gif)

流程如下所示：
1. 上层应用发出一个系统调用；
2. Newcastle Connection检测该系统调用是不是远程调用；不是远程调用则直接转换为本地的系统调用（内核服务）；如果是对远程的文件进程操作，则是远程调用。
3. 远程调用，则通过连接层将命令(加上额外信息，如当前用户id)发送到远程主机上（连接层相当于管道，连接了UNIX1和UNIX2）;
4. 连接层解析文件的名称（如： /../UNIX2/）将其传递给对应的计算机。
5. 远程主机调用对应进程来处理（即UNIX United中只有本地操作），远程主机返回执行情况
