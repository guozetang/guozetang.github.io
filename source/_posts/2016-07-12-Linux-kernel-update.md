---
title: Ubuntu编译、更换、删除内核
date: 2016-05-07 13:04:27
updated: 2016-05-07 13:04:27
categories: Linux
tags: Linux kernel
---

一直想将自己的linux内核更换一下，换一个低版本的方便平时做实验课程的时候使用，于是就开始了Ubuntu下换内核的过程．

<!--more-->

# 简要概述

原系统：Ubuntu 10.10（Virtualbox）平台中的linux内核2.6.35-22

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-26-50.png)

降级为：linux内核2.6.39  

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-27-06.png)

具体操作：  
1. 首先下载Linux2.6.39内核并解压到/usr/src下
2. 安装必备软件编译工具
`#apt-get install libncurses5-dev build-essentialkernel-package`
3. 做个链接文件#ln -s /usr/src/linux2.6.33/usr/src/linux
4. 进入linux文件#cd linux
5. #make mrproper (删除以前到.o文件，初次更换可不用)
6. #make menuconfig (这里可以设置一些参数，并生成.config文件)
7. #make dep (建立依赖关系)
8. #make clean (删除没有用的文件)
9. #make bzImage (编译linux内核)
10. #make modules (编译linux模块)
11. #makemodules_install (安装linux模块)
12. #make install (建立initrd文件, 加载LKM用的程序)
13. 生成initrd.img文件：

```bash
cd /lib/modules/2.6.39
update-initramfs -c -k 2.6.39
```

14. 自动查找新内核，并添加到grub引导#update-grub

15. #shutdown -r now （立即重启，重启后会发现多了一个linux2.6.33到启动项）

以下过程全部在root权限下操作**:**\

******

# 详细步骤分析

### 下载内核

内核下载官网：[https://www.kernel.org/](https://www.kernel.org/)

下载内核：2.6.39 该内核版本与自己当前系统内核版本2.6.35-22比较接近

概念：内核，是一个操作系统的核心。它负责管理系统的进程、内存、设备驱动程序、文件和网络系统，决定着系统的性能和稳定性。在广大爱好者的支持下，内核版本不断更新。新的内核修订了旧内核的bug，并增加了许多新的特性。如果用户想要使用这些新特性，或想根据自己的系统度身定制一个更高效，更稳定的内核，就需要重新编译内核。

为什么需要重新编译内核？

增加对某部分功能的支持，比如网络之类，可以把相应部分编译到内核中（build-in），在内核启动时就可以自动支持相应部分的功能，这样的优点是方便、速度快，机器一启动，你就可以使用这部分功能了,我们可将经常使用的部分直接编译到内核中，比如网卡。静态调用的缺点是会使内核变得庞大起来，不管你是否需要这部分功能，它都会存在。也可以把该部分编译成模块（module），要使用的时候再动态调用。如果编译成模块，就会生成对应的.o 文件，在使用的时候可以动态加载，优点是不会使内核过分庞大，缺点是你得自己来调用这些模块。

安装必备软件编译工具:.

```bash
apt-get install libncurses5-dev build-essential kernel-package**
```

这几个文件介绍：

- libncurses5-dev是为之后配置内核能运行 make menuconfig程序做准备
- Build-essential为编译工具；
- kernel-package是编译内核工具。

如果系统显示无法查找到这三个文件，输入#apt-get update更新数据源，更新完之后即可找到这三个文件了。

### 编译替换内核

#### 解压内核文件linux 2.6.39到/usr/src下xx

首先先将下载的内核拷贝到/usr/src目录下；/usr/src/目录是linux内核源码存放的目录，里面的内核源码目录为：linux-2.XX.XX目录等。

这里解压到任何目录都行，因为在这里我们是要增加一个内核，而不是覆盖掉原有系统的内核，即使是覆盖掉原有系统内核，也可以在后面执行#make install 自动就会将对应文件拷贝到本机相应的目录下去了。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-27-39.png)

解压命令：

```bash
tar -jxvf linux-2.6.39.tar.bz2
```

注：较新的内核文件以tar.xz结尾的压缩文件时，如何解压

```bash
xz -d ***.tar.xz
tar -xvf ***.tar
```

可以看到这个压缩包也是打包后再压缩，外面是xz压缩方式，里层是tar打包方式。补充：目前可以直接使用 `tar xvJf ***.tar.xz`来解压

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-28-54.png)

进入内核源码目录：`#cd /usr/src/linux-2.6.39/`可以查看相应内核文件

做个链接文件`#ln -s /usr/src/linux2.6.39 /usr/src/linux ` 
进入linux文件`#cd /usr/src/linux`

`/usr/src/linux`这个目录是编译内核时存放源代码的目录，而／usr/src/linux2.6.33这个目录是实际存放代码的目录．即在`/usr/src`中建立一个软链接

  

#### 定制内核

**#make mrproper**

清理以前加载的模块，第一次可省略

在每次配置并重新编译内核前需要先执行“makemrproper”命令清理源代码树，包括过去曾经配置的内核配置文件“.config”都将被清除。实验完成之后，在测试了一下这个命令，如下图所示，即进行新的编译工作时将原来旧的配置文件给删除到，以免影响新的内核编译。

![](https://img-blog.csdn.net/20141203173804265)  

即检查有无不正确的.o文件和依赖关系，如果使用刚下载的完整的源程序包即第一次进行编译，那么本步可以省略。而如果你多次使用了这些源程序编译内核，则最好要先运行一下这个命令。

`#make menuconfig`

这里可以设置一些参数，并生成.config文件, 使用makemenuconfig 生成的内核配置文件，决定将内核的各个功能系统编译进内核还是编译为模块，或者不编译。

在这里就不介绍具体的内核配置操作，但是建议就算不打算配置什么也执行一下make menuconfig这个命令，并在退出的时候进行保存，因为如果不执行此操作的话在后面make编译内核的时候会提示你回答很多问题。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-29-47.png)

这一步可以`#cp /boot/config-XX /usr/src/linux/.config`，即使用当前系统配置文件，之后进入`make menuconfig `选择load配置文件之后，再做细微改动，或者不改动也可。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-29-58.png)

执行`#cp /boot/config`-，然后按下Tab键，系统会自动填上该目录下符合条件的文件名，然后继续输入` .config`，目的是使用在boot目录下的原配置文件。  

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-30-07.png)

3.编译安装内核和模块

`#make dep 建立依赖关系`

根据上一步中加载的配置内容（.config）建立文件的依赖关系。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-30-17.png)

`#make clean 清除内核编译的目标文件`

清理一些不必要的文件，如果你在上次编译的基础上，删去了一些选项，建议你执行这一步操作，否则，就没有必要了。

`#make bzImage 编译内核`

内核编译成功后，会在源码树根目录即/usr/src/linux-2.6.39/arch/x86/boot/目录中生成一个新内核的映像文件bzImage。

`#make modules 编译模块`

编译可加载模块（即内核选项中选择为M的选项），以便将来使用insmod命令进行加载。编译时间跟M选项的数量有关。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-30-29.png)


`#make modules_install 安装模块`

编译成功后，系统会在/lib/modules目录下生成一个2.6.39子目录，里面存放着新内核的所有可加载模块(即将编译好的modules拷贝到/lib/modules下)。


`#make install`

安装内核,即复制.config，vmlinuz，initrd.img，System.map文件到/boot目录、更新grub。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-30-45.png)

当然，在这里我们也可以分别拷贝到/boot目录：

- 将生成的linux-2.6.39/.config 拷贝到要替换内核系统的/boot下，并重命名为config-2.6.39
- 将生成的linux-2.6.39/arch/x86-64/boot/bzImage拷贝到要替换内核系统的/boot下，并重命名为vmlinuz-2.6.39（注：这里需特别注意拷贝后的文件名变为vmlinuz-x.x.x）。
- 将生成的linux-2.6.39/System.map拷贝到要替换内核系统的/boot下，并重命名为System.map-2.6.39
- 将make modules_install生成的系统目录/lib/modules/linux-2.6.39拷贝到要替换内核系统的/lib/modules下。

`#new-kernel-pkg --install --mkinitrd --depmod 2.6.33`(将启动信息写入grub.conf中，这里也可以去/etc/编辑grub.conf文件，将启动信息模仿原来到写进去。注：有的linux版本是 lilo.conf文件) (测试了一下网上流传的这条指令，在我的电脑上这条命令没有反应)  
```bash
cd /lib/modules/2.6.39
update-initramfs –c –k 2.6.39  
#生成/boot/initrd.img-2.6.39文件
```

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-31-04.png)

`#update-grub`

 自动查找新内核，并添加到grup引导中

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-31-16.png)

`#shutdown -r now`

立即重启，重启后按shift会发现多了一个linux2.6.39启动项。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-31-32.png)

补充：如何在启动界面中加入你想要的个人信息

方法有许多，在这里介绍三个方法：

1. Ubuntu的登陆和欢迎信息控制/etc/issue和/etc/motd  
其中/etc/issue与/etc/motd区别在于：当一个网络用户或通过串口登录系统 上时,/etc/issue的文件内容显示在login提示符之前,而/etc/motd内容显示在用户成功登录系统之后。修改这两个文件都可以达到加入个人信息的效果。

2. 修改/boot/grub/grub.cfg文件来改动我们的引导项的名字来完成显示个人信息。

3. 在编译之前加入个人信息，将信息编译进内核：对/usr/src/linux-3.6/init.c文件进行修改，在最后一个函数中，加入printk（"***"）打印想要的信息，在这里要注意打印的优先级，必须设置超过一定的优先级方可在控制台打印出想要的信息（可参考相关printk函数的介绍）。


**卸载内核**  

首先我们需要查看一下当前使用的是哪个内核：  

```bash
uname -r
```

该命令会告诉你当前使用的内核版本，在登录时候，不能卸载当前的内核，以免造成无法启动的悲剧~~  
接下来，如果你是自己**动手编译**的内核的话，请删除以下文件和文件夹  
1. 删除掉/lib/modules/目录下过时的内核库文件  
2. 删除掉/usr/src/kernels/目录下过时的内核源代码  
3. 删除掉/boot目录下启动的核心档案以及内核映像  
4. 更改/boot/grub/menu.lst，删除掉不用的启动列表

在这里就只接受自己动手编译的内核如何卸载了，如果是安装包安装的内核，百度查询相关指令即可卸载，当然，自己手动卸载也是可以的。  
  

# 重要Linux内核文件分析

`.config`

使用make menuconfig 生成的内核配置文件，决定将内核的各个功能系统编译进内核还是编译为模块还是不编译。

`vmlinuz和vmlinux`

vmlinuz是可引导的、压缩的内核，“vm”代表“Virtual Memory”。Linux 支持虚拟内存，不像老的操作系统比如DOS有640KB内存的限制，Linux能够使用硬盘空间作为虚拟内存，因此得名“vm”。vmlinuz是可执行的Linux内核，位于/boot/vmlinuz

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-32-24.png)

vmlinuz的建立有两种方式：

1. 编译内核时通过“make zImage”创建，然后通过：“cp /usr/src/linux-2.4/arch/i386/linux/boot/zImage /boot/vmlinuz”产生zImage适用于小内核的情况，它的存在是为了向后的兼容性；

2. 内核编译时通过命令make bzImage创建，bzImage是压缩的内核映像，需要注意，bzImage不是用bzip2压缩的，bzImage中的bz容易引起误解，bz表示“big zImage”，bzImage中的b是“big”意思。 zImage（vmlinuz）和bzImage（vmlinuz）都是用gzip压缩的。它们不仅是一个压缩文件，而且在这两个文件的开头部分内嵌有gzip解压缩代码，所以你不能用gunzip 或 gzip –dc解包vmlinuz。内核文件中包含一个微型的gzip用于解压缩内核并引导它。两者的不同之处在于，老的zImage解压缩内核到低端内存（第一个640K），bzImage解压缩内核到高端内存（1M以上）。如果内核比较小，那么可以采用zImage 或bzImage之一，两种方式引导的系统运行时是相同的。大的内核采用bzImage，不能采用zImage。

vmlinux是未压缩的内核，vmlinuz是vmlinux的压缩文件。

`initrd.img`

initrd是“initial ramdisk”的简写。initrd一般被用来临时的引导硬件到实际内核vmlinuz能够接管并继续引导的状态。比如initrd- 2.4.7-10.img主要是用于加载ext3等文件系统及scsi设备的驱动。如果你使用的是scsi硬盘，而内核vmlinuz中并没有这个 scsi硬件的驱动，那么在装入scsi模块之前，内核不能加载根文件系统，但scsi模块存储在根文件系统的/lib/modules下。为了解决这个问题，可以引导一个能够读实际内核的initrd内核并用initrd修正scsi引导问题，initrd-2.2.39.img是用gzip压缩的文件。initrd映象文件是使用mkinitrd创建的，mkinitrd实用程序能够创建initrd映象文件，这个命令是RedHat专有的，其它Linux发行版或许有相应的命令。这是个很方便的实用程序。具体情况请看帮助：man mkinitrd

`System.map`

System.map是一个特定内核的内核符号表，由“nm vmlinux”产生并且不相关的符号被滤出。

`几个重要的内核文件分析`

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-33-08.png)

arch子目录包括了所有和体系结构相关的核心代码。它的每一个子目录都代表一种支持的体系结构，例如i386就是关于intel cpu及与之相兼容体系结构的子目录。PC机一般都基于此目录；

include子目录包括编译核心所需要的大部分头文件。与平台无关的头文件在include/linux子目录下，与intel cpu相关的头文件在include/asm-i386子目录下,而include/scsi目录则是有关scsi设备的头文件目录；

init子目录包含核心的初始化代码(注：不是系统的引导代码)，包含的两个文件main.c和Version.c，这是研究核心如何工作的一个非常好的起点。

Mm子目录包括所有独立于cpu体系结构的内存管理代码，如页式存储管理内存的分配和释放等；而和体系结构相关的内存管理代码则位于arch/*/mm/，例如arch/i386/mm/Fault.c

Kernel子目录包括主要的核心代码，此目录下的文件实现了大多数linux系统的内核函数，其中最重要的文件当属sched.c；同样，和体系结构相关的代码在arch/*/kernel中；

Drivers子目录放置系统所有的设备驱动程序；每种驱动程序又各占用一个子目录：如，/block下为块设备驱动程序，比如ide（ide.c）。如果你希望查看所有可能包含文件系统的设备是如何初始化的，你可以看drivers/block/genhd.c中的device_setup()。它不仅初始化硬盘，也初始化网络，因为安装nfs文件系统的时候需要网络；

其他子目录：

Lib放置核心的库代码；Net,核心与网络相关的代码；Ipc,这个目录包含核心的进程间通讯的代码；

Fs,所有的文件系统代码和各种类型的文件操作代码，它的每一个子目录支持一个文件系统，例如fat和ext2；Scripts,此目录包含用于配置核心的脚本文件等。一般，在每个目录下，都有一个.depend文件和一个Makefile文件，这两个文件都是编译时使用的辅助文件，仔细阅读这两个文件对弄清各个文件这间的联系和依托关系很有帮助；而且，在有的目录下还有Readme文件，它是对该目录下的文件的一些说明，同样有利于我们对内核源码的理解。

# 遇到的问题

1.源的问题  
安装必备软件编译工具:#apt-get installlibncurses5-dev build-essential kernel-package 的时候，无法更新，输入#sudo apt-get update也无法更新数据。

![](/images/in-post/2016-07-12-Linux-kernel-update/2018-09-19-02-33-19.png)

在这里是由于ubuntu10.10的源出现问题，导致无法更新、下载软件，这里需要重新修改源文件。处理如下：  
http://www.cnblogs.com/linuxcat/archive/2012/12/29/2839216.html

参考该网站内容后，将源换为http://old-releases.ubuntu.com/ubuntu/地址，即可更新、下载软件（当然，其他可用的源地址也是可以的）。

2.权限问题  
在这个内核的编译、安装过程中，涉及到的操作都是需要root权限才能进行操作的，如果权限不够，则产生错误。处理方法：使用sudo(必须给了给用户申请root的权限)或者直接su root切换到root用户下进行整个过程操作。