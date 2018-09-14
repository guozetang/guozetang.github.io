---
title: Ubuntu里面update,upgrade和dist-upgrade的区别
date: 2018-09-09 15:09:31
updated: 2018-09-14 15:09:31
categories: Linux
tags: Linux
top:
---

## Introduce

**常用的三个命令：**

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
```

`apt-get`是某些linux发行版使用的一个“包管理器”（还有别的发行版使用yum等，以及brew等其他平台上的包管理器，工作原理类似）。包管理器的作用是从源（Source）服务器那里下载最新的软件包列表，然后在你需要安装某个软件包（apt-get install）的时候从列表里面查询这个软件包的版本信息、系统要求、翻译、依赖项（该软件正常运行必须安装的其它软件）并且添加到同时安装的列表里面，再查询所有安装列表里面的软件包的.deb文件下载地址，最后批量下载，自动分析安装顺序然后安装完成。  

<!--more-->
******

## update & upgrade & dist-upgrade

`sudo apt-get update`和`sudo apt-get upgrade`分别更新的是什么：

- update是下载源里面的metadata的. 包括这个源有什么包, 每个包什么版本之类的，最新版本是什么.  
- upgrade是根据update命令下载的metadata决定要更新什么包(同时获取每个包的位置)，对已经安装的软件包本身进行更新的过程。由于确定要更新的软件包需要对本地安装的版本和列表的版本进行比较，所以要在update以后运行这一条.  
- dist-upgrade:可以聪明的解决相依性的问题,如果有相依性问题,需要安装/移除新的Package,就会试着去安装/移除它. (所以通常这个会被认为是有点风险的升级)  

> 注明：在install操作之前执行update和upgrade，实际上是确保本地软件列表信息和已安装软件均为最新的过程。这样做可以最大限度地确保新安装的软件包正常工作。  

PS：软件源服务器地址可以在/etc/apt/sources.list里面看到。  
  
**Example: upgrade and dist-upgrade**

apt-get upgrade 和 apt-get dist-upgrade 本质上是没有什么不同的。只不过，dist-upgrade 会识别出当依赖关系改变的情形并作出处理，而upgrade对此情形不处理。  

例如软件包 a 原先依赖 b c d，但是在源里面可能已经升级了，现在是 a 依赖 b c e。这种情况下，dist-upgrade 会删除 d 安装 e，并把 a 软件包升级，而 upgrade 会认为依赖关系改变而拒绝升级 a 软件包。
