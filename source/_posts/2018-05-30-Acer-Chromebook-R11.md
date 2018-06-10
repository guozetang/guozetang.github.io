---
title:  Acer Chromebook R11使用手册(坑)
date: 2018-05-30 20:30:32
categories: Chromebook
tags: laptop
---
## 前言
之前使用了两年的MSI GE60 2PG 笔记本散热问题越来越严重，导致风扇永远转到最高转速，否则CPU温度一直无法降下来。但是，风扇转到最高转速，这台电脑产生的噪音会非常大，如果咋图书馆或者实验室使用，很容易就影响到周围学习的其他同学了，于是考虑到都买另外一个轻便的，待机时间比较长的笔记本到学校，能够支持自己的常规使用。
<!--more-->

## 购买 Acer Chromebook R11
综合对比的自己的预算以及网友的评价，最后选择了[Acer Chromebook R11](https://www.acer.com/ac/en/US/content/series/acerchromebookr11)(内存4G, SSD:32G), 主要考虑的是只需要279刀，待机时间到10小时左右，屏幕触屏，画面显示给力，触摸板键盘比较舒服。
个人使用Chromebook的目标是是：
- 阅读网页，PDF文档，使用Google doc书写文档
- 简单使用SSH登陆到服务器书写代码
- 代码阅读，简单编译一些练习代码
- 远程连接MSI GE60 电脑完成开发或处理紧急问题
我并不想使用一台279刀的Chromebook来完成自己的项目开发或者运行Matlab之类的软件，它的定位就是辅助自己完成一些简单的不需要消耗太大内存资源的工作，后续我对Acer Chromebook的使用过程中也是这样去安排的。

## 使用手册
### 常用功能&插件
- [Kami](https://www.kamihq.com/) ： 这并不能算作是一个插件，这是一个在线的PDF阅读标注网站，你可以绑定Google邮箱，上传自己本地的文件，然后在线阅读并做笔记，然后它会自动把你的笔记以及文档保存到Google云盘里面，十分方便，随时在何地都可以通过浏览器来打开使用，一样的笔记，一样的阅读进度，很适合作为云端的PDF阅读工具。

- [stackedit](https://stackedit.io/app#): 网页应用，这是开源世界的markdown利器，让你随时随地做笔记、做记录。如果你喜欢写博客，或者喜欢Markdown这种专注于写作的方式，强烈推荐尝试。

- [Evernote Web](https://chrome.google.com/webstore/detail/evernote-web-clipper/pioclpoplcdbaefihamjohnefbikjilc?hl=en-US) : 这是chrome端的Evernote笔记的收集插件，能够快速的把网页资料收集到自己的Evernote里面去。  

- [Telegram](https://chrome.google.com/webstore/detail/desktop-messenger-for-tel/dafiggkhlbbhfcpgggcfeeoliillkabn?hl=en-US) : 这是一款加密的通信软件，可以很好的在手机端和电脑端同步消息，互传文件(大小没有限制)，并且消息和文件永久保存，并不会因为你换收集或者电脑而导致你的消息和文件丢失。  

- [Gmail Ofline](https://chrome.google.com/webstore/detail/gmail-offline/ejidjjhkpiempkbhmpbfngldlkglhimk?hl=en): 这是没有办法的时候，总是有周围没有无线的地方，所以你就需要一个离线的Gmail，让自己能够离线编辑一些邮件消息，当Chromebook连接到网络的时候，能够快速发送邮件出去。  

- [Chrome Remote Desktop](https://chrome.google.com/webstore/detail/chrome-remote-desktop/gbchcmhmhahfdphkhkmpfmihenigjmpp?hl=en) 但我们的资料在家里的电脑上，或者在公司的电脑上面时，我们需要短暂的连接过去，处理一些工作的时候，这个插件就能够很好的帮助你快速的完成任务。  

- [Caret](https://chrome.google.com/webstore/detail/caret/fljalecfjciodhpcledpamjachpmelml?hl=en): Chromebook端的代码阅读工具，对中文支持比较友好。  

- [MathStudio](https://chrome.google.com/webstore/detail/mathstudio/pcpedkecdcnobiheblbhgleenlbdoknp?hl=en-US): 很小但是功能很强大的数学工具，能够画出简单的正弦图形，以及一些常用的数学图形，当然也可以作为数学计算器来使用，很方便。  

- [PDF Mergy](https://chrome.google.com/webstore/detail/pdf-merge-pdf-files-merge/ndolbcaghkmhjhgggldkgjibdilpbdbm?hl=en-US): 小插件，完成PDF文件的合并工作  

- Write: 书写小插件，能够打开一个很绚丽的网页，让你专注的书写内容  

- [listen1_chrome_extension](https://github.com/listen1/listen1_chrome_extension)  听歌利器，在 Chromebook 里更是神器，不用安装不兼容的 Android apps
-   [Tampermonkey](https://chrome.google.com/webstore/detail/tampermonkey/dhdgffkkebhmkfjojejmpbldmpobfkfo?hl=en-US) 和 ublock 这种神器就不介绍了  

-   [Cog - System Info Viewer](https://chrome.google.com/webstore/detail/cog-system-info-viewer/difcjdggkffcfgcfconafogflmmaadco?utm_source=chrome-app-launcher-info-dialog)  查看性能的工具

这些插件是我使用过一段时间之后，依旧还保留在我的Chromebook上面的内容，如果你感兴趣，不妨尝试一下。
### 进阶操作：远程桌面
#### 场景
长时间使用Chromebook连接到公司或者家里自己的主机进行工作，完成项目等，这就需要考虑使用远程桌面来很好的完成工作。经过一个月的时间，陆续地尝试了能够支持Chromebook的远程桌面软件。
个人要求：
- 通过Chromebook的chrome插件或者App能够进行远程连接(并不是通过安卓APP)  

- 使用过程中不通过IP地址直接连接(尝试过这种方式，但是并不能达到我的画质要求)  

- 长时间(超过10小时)连接使用比较稳定  

- 操作方便，Chromebook的按键能够正常工作  

经过对比Teamviewer,  Splashtop, Chrome Remote Desktop app, UltraVNC这几款能够在Chromebook上面使用的插件或者APP，去掉了收费的Splashtop，以及需要IP地址点对点连接的UltraVNC，最后保留了Teamviewer和Chrome Remote Desktop.  

#### Teamviewer
Teamviewer在chromebook上连接Win10的画面效果，延时情况应该是上述软件里面最好的了，并且面向个人使用是完全免费的，你只需要登录你的账号，就可以免费无广告的连接自己的远程主机，并不需要考虑IP地址，防火墙以及NAT代理之类的。但也有这么几个缺点。
- Chromebook端的软件功能不完善，必须每次登录到网页端才能够看到自己账号下面的机器，通过在网页端点击然后调用APP连接，过程比较繁琐

- 对Chromebook的键盘没有适配，导致操作起来并不是很方便。比如：不能使用`Windows`按键

#### Chrome Remote Desktop
谷歌自己的远程桌面软件，所以对Chromebook的支持比较好，把Chromebook右侧的`Ctrl`按键转换为了`Windows`按键，以及很多的Chromebook快捷键也可以在远程桌面的时候使用。初次之外，和Teamviewer对比起来有这么几个缺点：
- 图像质量不是太好，打字的时候，能够明显感觉到字体周围模糊  

- 延时有时候比较大

综合起来，我同时保留的这两个远程桌面软件，在需要长时间工作的时候，那我就会选用Teamviewer, 因为这个时候图像的清晰对我很重要，我不想对着有些模糊的图像长达八个小时。但当我只是需要快速远程连接过去，提交文件或者发一封简短的邮件的时候，我就会选择Chrome Remote Desktop，它能够让我以最快的速度完成我远程连接的工作。

### 进阶操作：SSH连接 ---**[Secure Shell](https://chrome.google.com/webstore/detail/secure-shell-app/pnhechapfaindjhompbnflcldabbghjo?hl=en)**
这是google官方出的SSH插件，到google应用商店下载扩展即可，下载之后打开即可。
使用说明：
```
username@hostname or free form text  //填写你想为这个session定制的名字,比如：lab.university  

username位置：填写你要连接的服务器的账号名称，比如:root  

hostname位置：这里可以直接填写IP地址，也可以填写域名，一致的。比如：192.168.2.121  

port：填写服务器开放的SSH端口连接地址,一般服务器默认的是：22  

SSH relay severs options：这个位置不用填写，可以空出来
```
填完上述的内容，就可以选择连接了，上述内容相当于你在终端输入了：`ssh -p 22 root@192.168.2.121`，根据反馈的提示内容，输入你的登陆密码就可以了。
但是如果每次连接都需要你时输入密码，这就是一个比较烦躁的事情了，所以你需要导入你的秘钥信息
```
Identity:[default] 这个位置可以导入你的秘钥信息，点击`import`，同时选中自己的id_rsa和id_rsa.pub文件之后，点击`open`.（注意：这需要同时导入两个文件）
```
到这里你还不能够直接免密码登陆到服务器，需要你将自己的`id_rsa.pub`文件中的字符内容拷贝到服务器端的`~/.ssh/authorized_keys`文件中。至于如何生成秘钥文件，请参考[教程](http://cs.umw.edu/~finlayson/class/cpsc225/notes/01-ssh-chrome.html)。

### 进阶操作: 通过crouton安装Ubuntu
#### 进入开发者模式
关机之后，同时按下 esc + 刷新键(第一排左边数过去第四个）+电源键即可。然后 Chromebook 重启，然后按 Ctrl+D 继续，回车确定关闭chromebook 的安全认证，然后chromebook重启，上面的进度条走完了之后自动重启，就进入开发者模式了。

#### 通过Crouton安装Ubuntu
-	crouton的下载链接： [crouton](https://github.com/dnschneid/crouton/raw/master/installer/crouton), 下载之后默认在`Downloads`文件夹下面

-	用 `Ctrl+ALT+ t` 调出 `crosh` 窗口，输入 `shell`  

-	输入`sh ~/Downloads/crouton -r list`查看croutonz支持的Ubuntu版本  

-	安装Ubuntu unity: `sudo sh ~/Downloads/crouton -t unity` 这里我选择的是Ubuntu的unity桌面，如果你喜欢其他桌面，可以把`unity`换成`xfce`  
> 如果你不想安装桌面，或者Chromebook的资源比较少，就可以只输入: `sudo sh ~/Downloads/crouton -t core`，这样就只会安装最简单的终端CLI  

- 进入桌面：`sudo startunity`
> 其他命令：
`sudo enter-chroot` 进入终端
`sudo startxfce4` 启动 xfce 桌面 
在 Chrome os 和 Linux 之间切换：
从 Chrome os  到 Linux：`shift + ctrl + alt + 前进键（第1排第3个键）`
从 Linux 到 Chrome os ：`shift + ctrl + alt + 后退键（第1排第2个键）`

官方通过Crouton安装Ubuntu的教程：[Installing Ubuntu with crouton](https://tutorials.ubuntu.com/tutorial/install-ubuntu-on-chromebook#0)

#### Ubuntu环境配置
我们通过`sudo sh ~/Downloads/crouton -t unity`这条命令安装的Ubuntu并不是完整版本的，并没有软件管理中心，也没完整的系统设置功能。所以，如果你的电脑是32G以上的SSD的话，
##### 安装完整的Ubuntu桌面版
在Ubuntu内打开终端：
```bash
sudo apt-get install ubuntu-desktop 			   //下载完整版 Ubuntu
sudo apt-get remove libreoffice-common -y          //删除 libreoffice
sudo apt-get remove unity-webapps-common -y        //删除 amazon
sudo apt-get remove thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install onboard deja-dup -y   
```
##### 设置中文工作环境
```bash
sudo apt-get install language-pack-zh-hans language-pack-zh-hans-base language-pack-gnome-zh-hans language-pack-gnome-zh-hans-base
sudo apt-get install `check-language-support -l zh`
sudo localectl set-locale LANG=zh_CN.UTF-8
```
#### crouton常规使用(chromebook中的crosh中操作)
##### crouton的升级
```bash
sudo ~/Downloads/crouton -u -n croutonname
```
这里的croutonname替换成你安装的版本：如xenial

##### crouton内的Ubuntu关机
一般选择在Ubuntu里面点击关机按钮(右上角设置里面)，然后自动退出到Chrome OS里面
##### 删除crouton安装的ubuntu
```bash
sudo delete-chroot chrootname //chrootname: 所安装 ubuntu 的版本代号，比如xenial：代表的是Ubuntu16。04
```
##### 备份与恢复Crouton里面的Ubuntu
**备份**
```bash
sudo edit-chroot -b xenial
```
注：xenial为ubuntu的版本名称，即16.04为xenial

**恢复**
```bash
sudo sh ~/Downloads/crouton -f ~/Downloads/*.tar.gz
```
注：将*.tar.gz改为你的备份文件名。

**删除备份**
```bash
sudo edit-chroot -d xenial
```
##### 解决音频的Bug问题
暂时没有解决(遗留)
网上解决方案(未在我的Chromebook上面成功)：
1. 在Chrome OS中shift+alt+T调出crosh窗口，输入`shell`。 
2. 输入`sudo enter-chroot -n trusty` 
3. 输入`sudo apt-get dist-upgrade` 
4. Ctrl+D登出 
5. 输入`sudo sh -e ~/Downloads/crouton-master/installer/main.sh(下载的哪个文件用哪个文件名） -u -n xenial` 等待更新完成。一般出现的无声音、不能播放视频等BUG都可以解决。
 **注：xenial为版本号，你使用哪个版本填写哪个版本号**x

#### crouton进阶操作
##### 在Chromebook里面的chrome中以窗口的方式运行Ubuntu
先在Chromebook的chrome 网上应用商店里下载 [cronton-integration](https://chrome.google.com/webstore/detail/crouton-integration/gcpneefbbnfalgjniomfjknbcgkbijom)
然后在crosh中，安装xiwi桌面
```bash
sudo sh ~/Downloads/crouton -t unity,extension,xorg,xiwi //我是在 xfce 桌面下使用的 unity 也可行 但要求下载 extension,xorg,xiwi
sudo startxunity -X xiwi // 使用 xiwi 来实现 窗口化
```
## 使用中遇到的问题
### Wifi开关无法开启的问题
问题描述：在Chrome OS系统中，当休眠状态恢复之后，出现过Wifi无法连接，系统的Wifi状态是关闭的，即使点击的开启的按钮，但是在三到五秒之后就会自动关闭。
解决方案：经过自己检查，发现是Wifi模块有一些松动，所以拆机之后，重新固定了Wifi模块。