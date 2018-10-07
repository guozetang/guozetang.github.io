---
title: Git不同场景常用命令
date: 2018-05-12 16:14:31
updated: 2018-05-12 16:14:31
categories: Git
tags: Git
---

# Git子模块:仓库中包含另外一个仓库

## 场景  
在工作的项目中需要包含另外的项目，这个时候我们就需要引出其他的项目，但是我们希望在引入的项目变化的时候，我们也可以很快的合并到我们现有的分支中。
<!--more-->
## 操作指令
### 现有repo加入子repo
在你想要添加的目录位置输入添加子repo的命令即可
```bash
git submodule add https://github.com/guozetang/paper_code_tracker
```
查看状态参数：
`git status`

在repo(不是子repo)的根目录查看当前加入的子模块(子repo)。
```bash
$ cat .gitmodules
[submodule "python/paper_code_tracker"]
	path = python/paper_code_tracker
	url = https://github.com/guozetang/paper_code_tracker

```
### 提交添加的子模块

```bash
$ git commit -am "added subproject module"
[master (root-commit) 9168027] added subproject module
 2 files changed, 7 insertions(+)
 create mode 100644 .gitmodules
 create mode 160000 python/paper_code_tracker

```

其他更多操作请参考: [【Git】子模块：一个仓库包含另一个仓库](https://www.jianshu.com/p/491609b1c426)

# 分支操作
## 场景
开发过程中经常用到从master分支copy一个开发分支,进行开发  
  
## 操作指令介绍
```sh
$git checkout master        //切换到被copy的分支（master）
$git pull                   //从远端拉取最新版本
$git checkout -b NewBranch  //Switched to a new branch 'dev'
$git push origin NewBranch  //新建分支push到远端
```

## 遇到的问题

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

**关联**

`$git branch --set-upstream-to=origin/NewBranch`

注意：这里branch之后都是没有空格的，如果有空格则是错误命令

**再次拉取**

`$git pull`

---

# 关联远程repo
## 场景
我们经常由于一起不知道的问题，造成我们需要删除`.git`文件夹之后，使用`git init`来新建一个文件夹，这时候就需要我们将新建的repo关联到远程的repo上去。

## 操作命令介绍
### 在本地目录下关联远程repository

```bash
git remote add origin git@github.com:git_username/repository_name.git
```
  

### 取消本地目录下关联的远程库：
```bash
git remote remove origin
```

# 文件操作

## 场景
如果一个文件不小心被删除了，可以有两种方法恢复。

## 操作命令介绍
1、需要记住所需恢复文件的名字和版本号(commit id)

```bash
git checkout commit_id -- file_name
```

### fatal: remote origin already exists.

如果输入:  
$ git remote add origin [git@github.com:djqiang（github帐号名）/gitdemo（项目名）.git](https://link.jianshu.com?t=mailto:git@github.com:djqiang/gitdemo.git)  
提示出错信息：**fatal: remote origin already exists**.  
解决办法如下：

1、先输入$ git remote rm origin

2、再输入$ git remote add origin [git@github.com:djqiang/gitdemo.git](https://link.jianshu.com?t=mailto:git@github.com:djqiang/gitdemo.git) 就不会报错了！

3、如果输入$ git remote rm origin 还是报错的话，error: Could not remove config section 'remote.origin'. 我们需要修改gitconfig文件的内容

4、找到你的github的安装路径，我的是

C:\Users\ASUS\AppData\Local\GitHub\PortableGit_ca477551eeb4aea0e4ae9fcd3358bd96720bb5c8\etc

5、找到一个名为gitconfig的文件，打开它把里面的[remote "origin"]那一行  
删掉就好了！

### Permission denied (publickey)

如果输入:  
$ ssh -T [git@github.com](https://link.jianshu.com?t=mailto:git@github.com)  
出现错误提示：**Permission denied (publickey)**.因为新生成的key不能加入ssh就会导致连接不上github。  
解决办法如下：

1、先输入$ ssh-agent，再输入$ ssh-add ~/.ssh/id_key，这样就可以了。

2、如果还是不行的话，输入ssh-add ~/.ssh/id_key 命令后出现报错Could not open a connection to your authentication agent.解决方法是key用Git Gui的ssh工具生成，这样生成的时候key就直接保存在ssh中了，不需要再ssh-add命令加入了，其它的user，token等配置都用命令行来做。

3、最好检查一下在你复制id_rsa.pub文件的内容时有没有产生多余的空格或空行，有些编辑器会帮你添加这些的。

### error:failed to push som refs to .......

如果输入:  
$ git push origin master  
提示出错信息：**error:failed to push som refs to .......**  
解决办法如下：

1、先输入$ git pull origin master //先把远程服务器github上面的文件拉下来

2、再输入$ git push origin master

3、如果出现报错 fatal: Couldn't find remote ref master或者fatal: 'origin' does not appear to be a git repository以及fatal: Could not read from remote repository.

4、则需要重新输入$ git remote add origin[git@github.com:djqiang/gitdemo.git](https://link.jianshu.com?t=mailto:git@github.com:djqiang/gitdemo.git)

### 使用git在本地创建一个项目的过程

```
$ makdir ~/hello-world    //创建一个项目hello-world    

$ cd ~/hello-world       //打开这个项目    

$ git init             //初始化     

$ touch README   

$ git add README        //更新README文件    

$ git commit -m 'first commit'     //提交更新，并注释信息“first commit”    

$ git remote add origin [git@github.com:defnngj/hello-world.git](mailto:git@github.com:defnngj/hello-world.git)     //连接远程github项目     

$ git push -u origin master     //将本地项目更新到github项目上去
```


### Permission denied(publickey)
```bash
➜  workspace_config git:(document) git push origin document
Permission denied (publickey).
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```
**Solution:**
- Testing: `$ssh -T git@github.com`
If there is a mistake about: `Permission Dnied(publickey)`, this is because your new private key is not fit with the public key in the server.
- Input: `$ssh-agent`, after that, you can input`ssh-add ~/.ssh/id_key`
### fatal: Could not read from remote repository.
```bash
➜  workspace_config git:(document) git push origin document
Permission denied (publickey).
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

---

# 关联两个Rep:一个开发repo，一个release的repo

## 使用场景

团队在一个`private`的仓库(repo1)中进行项目的开发, 但是在开发的某一个进度的时候，想将这一个版本发布出去，这就需要建立另外一个`repo2`来管理发布的项目。我们想实现能够在开发的`repo1`里面添加直接将`code` push 到 `repo2`里面去。、

## 操作命令介绍

先检查自己当前的远程分支

```bash
git remote -v
github  https://github.com/zxbetter/test.git (fetch)
github  https://github.com/zxbetter/test.git (push)
```

然后添加另外一个管理项目发布的`repo2`

```bash
git remote add oschina https://git.oschina.net/zxbetter/test.git
```

注意，这里的名字有点区别，`repo1`对应的名字是`github test`, 而`repo2`对应的名字是`oschina test`

```bash
git push oschina test
```

关于关联两个repo的其他用法参考博客： [一个项目push到多个远程Git仓库](https://segmentfault.com/a/1190000011294144)