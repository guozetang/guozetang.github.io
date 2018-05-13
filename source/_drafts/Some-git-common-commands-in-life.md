---
title: Git常用命令
date: 2018-05-12 16:14:31
categories:
tags:
---

## 分支操作
1. 场景： 开发过程中经常用到从master分支copy一个开发分支,进行开发  
2. 操作指令介绍：
```sh
$git checkout master        //切换到被copy的分支（master）
$git pull                   //从远端拉取最新版本
$git checkout -b NewBranch  //Switched to a new branch 'dev'
$git push origin NewBranch  //新建分支push到远端
```
3. 遇到的问题

```sh
$git pull

There is no tracking information for the current branch.
Please specify which branch you want to merge with.
See git-pull(1) for details.

git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

git branch --set-upstream-to=origin/<branch> NewBranch
```

经过验证，当前的分支并没有和本地分支关联，根据提示进行下一步：

- 关联

`$git branch --set-upstream-to=origin/NewBranch`

注意：这里branch之后都是没有空格的，如果有空格则是错误命令

- 再次拉取 验证

`$git pull`



1、从远程拉取分支到本地(当远程已经有分支的时候可以这样用)

[html] view plain copy
git checkout -b 本地分支名x origin/远程分支名x  

2、提交本地test分支作为远程的test分支（合并分支后可以用）

git push origin test:test   // 提交本地test分支 作为远程的test分支



简单总结：

其实在git中要注意如下几点：

第一点就是分支，git因分支而强大，所以要理解git中的分支，我们在一个远程服务下可以拉多个分支，比如生产主分支、测试分支、每个人的开发分支。

第二点就是本地和远程，当我们在本地建了一个新分支有，还要把新分支推到远程也就是在远程建立一样的一个分支。所以我们在本地和远程建立分支后还要把他们关联起来，这样才有意义！！！

第三点 git远程服务和git远程分支，某一个或某几个分支是在一个服务下的，就好比A项目在远程的服务是a那么在a服务下我们可以创建 master、test、dev多个测试分支。其实一个远程服务就是一个project因为在github或gitlab都是创建project。

第四点 当我们从master分支上拉开发分支，我们在自己的开发分支上pull的时候会吧别人提交到master分支的代码回pull下来，而push的时候还是提交到了自己的开发分支，除非你把自己的开发分支合并到了master分支上。


1. 查看远程分支

$ git branch -a 
我在mxnet根目录下运行以上命令：

~/mxnet$ git branch -a
* master
  remotes/origin/HEAD -> origin/master
  remotes/origin/master
  remotes/origin/nnvm
  remotes/origin/piiswrong-patch-1
  remotes/origin/v0.9rc1
1
2
3
4
5
6
7
8
可以看到，我们现在在master分支下

2. 查看本地分支

~/mxnet$ git branch
* master
1
2
3. 切换分支

$ git checkout -b v0.9rc1 origin/v0.9rc1
Branch v0.9rc1 set up to track remote branch v0.9rc1 from origin.
Switched to a new branch 'v0.9rc1'

＃已经切换到v0.9rc1分支了
$ git branch
  master
* v0.9rc1

＃切换回master分支
$ git checkout master
Switched to branch 'master'
Your branch is up-to-date with 'origin/master'.




你是不是已经厌倦了每次git push的时候每次都要输入用户名密码，使用下面的方法可以让你使用ssh协议通过密钥验证的方式让你得到解脱。

有两种修改方法

不过再实施前，请先准备好自己的密钥

ssh-keygen -t rsa -C "your_name"
然后登录https://github.com/settings/ssh，添加当前计算机的~/.ssh/id_rsa.pub公钥内容到github。

之后我们使用ssh git@github.com验证是否添加成功，如果返回以下内容，即代表添加成功！

Hi phpgao! You've successfully authenticated, but GitHub does not provide shell access.
下一步就是让我们的git使用公钥验证。

clone
保存你的最后一次修改并提交。

删除项目

使用下面的命令clone项目

# 采用ssh的方式克隆项目
# someaccount/someproject.git 中 some account为github用户名/someproject为仓库名

git clone git@github.com:phpgao/BaiduSubmit.git
修改https
git remote set-url origin git@github.com:someaccount/someproject.git
顺便提一下，老高的git push总是报warning: push.default is unset错误，今天终于知道为啥了。原来是版本兼容性的原因，低版本的git push如果不指定分支名，就会全部推送，而新版只会推送当前分支。

解决的办法也很简单，我们只需要明确指定应该推送方式即可，至于选择哪种方式，It's up to you.


# 全部推送
git config --global push.default matching

# 部分推送
git config --global push.default simple