---
title: synergy局域网共享鼠标键盘软件教程
date: 2018-10-27 10:14:31
updated: 2018-10-27 12:14:31
categories: Application
tags: Application
---

# Introduce

`synergy`可以实现 mac / linux / windows三个操作系统之间共享鼠标键盘，必须在所有机器上都安装这个软件，并进行相应的配置，有一台唯一的主机作为服务器端，其他主机作为客户端，要共享的那套鼠标键盘链接到端。所有主机都必须连入同一个局域网，会通过局域网交换鼠标键盘的输入信息，以实现其他主机共享使用这套鼠标键盘。

# Download and install

因为在Ubuntu16.04上面比较好安装的版本是`1.6.2`，所以我为了能够在共享的过程中比较顺利，也选用的这个版本来完成的，在Window端下载`1.6.2`就好了。

- Linux: 使用命令行安装
- Win10(64位): [下载地址](/download/application/synergy-1.6.2-Windows-x64.msi)

<!-- more -->

**Linux(Ubuntu16.04)**

```bash
sudo apt-get install synergy
```

安装完成之后在终端使用synergy命令就可以打开软件了。

```bash
synergy
```
  
**Window10端**

在Window端依旧选用安装的是`1.6.2`版本，为保证版本一致。下载下来之后，启动安装即可：

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-13-13.png)

分别在Linux和Window端安装完成之后运行软件检测版本是否对应，打开软件，在菜单栏`help`的位置可以看到版本信息。

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-14-49.png)

# Configure

配置过程比较方便，分别在`Windows`和`Linux`端运行软件：

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-16-38.png)

将你要使用的那台电脑的鼠标键盘共享给其他电脑使用的话，那就将这台电脑上面的`Synergy`设置成服务端，其余的全部设置成客户端就好了。

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-18-28.png)

这里需要特别注意，图片中的`192.168.1.161`并不是真正的你的IP地址，你需要打开网络适配器找到你真正的IP地址，这样其他的客户端才能够连接过来。然后再配置服务器里面需要连接过来的客户端的名称

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-21-49.png)

比如，在这里，我添加了一个叫做Chromebook的客户端，这里的名称是根据你客户端打开之后显示的名字决定的。在这里也配置了连接过来之后，屏幕显示的位置。

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-22-46.png)

然后打开客服端，在里面输入服务器的IP地址就可以连接了。

# Issue

## 连接被拒绝refued问题

这里需要保证两边的连接配置是一致的，在这里我给出我的配置方式，不需要使用加密的方式，如果使用加密的话，需要保证两端加密的秘钥是一致的。

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-26-43.png)

## 连接超时的问题：Time out

**这个问题有两种情况：**

第一种情况：输出了错误的服务器IP地址，服务器的IP地址一定要自己查看网络适配器得到真正的IP地址，不要使用这个软件配置的时候推荐的IP地址，它真的很有可能是错误的。

![](/images/in-post/2018-10-27-Application-Synergy/2018-10-27-00-28-49.png)

比如我使用的这一次，就会出现IP地址完全和它推荐的不一样的情况。这种情况怎么可以连接上的呢

第二种情况：Windows里面的`synergy`服务被关闭了，在服务的选项里面去打开就好了。

## 版本问题

尽量同时在客户端和服务器端使用相同的版本，保证最小限度的出现问题

## error：unrecognised client name XXXXX

screen name 是软件规定的，不能自己瞎取。在每个客户端/服务器上能查到，也可以通过edit->setting修改

## ERROR: failed to init synwinhk.dll

关闭synergy，从系统进程里关闭synergy的进程，再重新启动即可。