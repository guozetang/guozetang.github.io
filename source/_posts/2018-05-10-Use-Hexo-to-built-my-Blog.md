---
title: 使用Hero+Next主题+Github搭建博客
date: 2018-05-10 15:13:51
categories: Lift
tags: Hexo
---
使用Jekyll搭建在github上博客已经快一年了，但一年的时间并没有写很多的文章。一部分原因是由于自己懈怠，另一部分也由于Jekyll写博客有很多不便之处。不能自动生成目录，以及每次新建文章都需要自己的手动设置目录结构以及添加Jekyll解析的格式内容在每一篇文章中，这是一件非常繁琐而无趣的工作。遵循自己动手丰衣足食的原则，查询目前比较流行的搭建博客的方式之后，决定使用Hero+Next主题在github上搭建博客。本篇博客记录搭建过程中的配置与优化。

> 具体搭建博客过程请参考：
> - [Jekyll迁移到Hexo搭建个人博客](https://www.ezlippi.com/blog/2016/02/jekyll-to-hexo.html)  
适合熟悉原理的同学，作者详细的讲解了使用Hexo与Next主题搭建博客的过程。
>   
> - 如果完全不熟悉Hexo的原理以及之前没有使用过git的同学，请参考：  
   [使用 Hexo 基于 GitHub Pages 搭建个人博客（一）](https://ehlxr.me/2016/07/23/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%B8%80%EF%BC%89/)   
   [使用 Hexo 基于 GitHub Pages 搭建个人博客（二）](https://ehlxr.me/2016/07/23/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%BA%8C%EF%BC%89/)
<!-- more -->
完成Hexo搭建博客之后，可以参考一些配置说明,做一些优化：
[使用 Hexo 基于 GitHub Pages 搭建个人博客](https://ehlxr.me/2016/08/30/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%B8%89%EF%BC%89/)
# Hexo基本操作
### 基本命令
```sh
hexo new "postName" #新建文章
hexo new page "pageName" #新建页面
hexo generate #生成静态页面至public目录
hexo server #开启预览访问端口（默认端口4000，'ctrl + c'关闭server）
hexo deploy #将.deploy目录部署到GitHub
hexo help  # 查看帮助
hexo version  #查看Hexo的版本
hexo deploy -g  #生成加部署
hexo server -g  #生成加预览
命令的简写
hexo n == hexo new
hexo g == hexo generate
hexo s == hexo server
hexo d == hexo deploy
```
*****
# Hexo 文章图片管理
数无形时少直觉，很多时候一个配图能清晰的表达我们的观点。所以，我们需要研究Hexo写文章时插入图片的方法。主要有两种方式：
- 本地引用  
**适用场景：**少量图片 + Blog搭载平台空间充足  
**优势：** 简洁方便

- 远程图床引用  
**适用场景：**深度使用用户 + 文章插入图片的需求较高 + Blog搭载平台空间不足  
**优势：** 能够满足自己插入图片的需求，不用考虑空间问题  
**缺点：** 所有文章中的图片受制于远程图床服务器的限制，如果服务器出现问题，所有图片都不能加载了

## 本地引用
### 绝对路径引用(我选择的方式，需要能够在首页上显示图片)
当Hexo项目中只用到少量图片时，可以将图片统一放在source/images文件夹中，通过markdown语法访问它们。  
 > source/images/image.jpg  
`![](/images/image.jpg)`  

优势：图片既可以在**首页内容中访问到，也可以在文章正文中访问到**。

### 相对路径引用
#### 配置站点_config.yml文件
另外也可以将图片放在文章自己的目录中。文章的目录可以通过配置站点_config.yml来生成。  
> _config.yml  
'post_asset_folder: true'  

将post_asset_folder设为true后，执行命令：  
`$ hexo new post_name`  
在source/_posts中会生成文章post_name.md和同名文件夹post_name。将图片资源放在post_name中，文章就可以使用相对路径引用图片资源了。  
`_posts/post_name/image.jpg`
> 参考博文：[在 hexo 中无痛使用本地图片](http://www.cnblogs.com/lmf-techniques/articles/6911051.html)

#### Markdown直接引用图片
`![](image.jpg)`  

上述是markdown的引用方式，图片放在文章所在的目录下，或者子目录下，图片只能在文章中显示，但无法在首页中正常显示。

如果希望图片在文章和首页中同时显示，可以使用标签插件语法。  
> _posts/post_name/image.jpg
```
{% asset_img image.jpg This is an image %}
```
## 远程图床引用
除了在本地存储图片，还可以将图片上传到一些免费的CDN服务中。比如Cloudinary提供的图片CDN服务，在Cloudinary中上传图片后，会生成对应的url地址，将地址直接拿来引用即可。
> 参考博文：[使Hexo文章图文并茂](https://mapan.tech/posts/c9c3.html)  
> 该篇文章详细讲解如何使用新浪微博图床来实现在Hexo文章中插入图片
********

# Hexo的版本控制方式
我们将Hexo生出来的静态网站放到了Github Pages上面去托管了。而我们一般也在在本地搭建Hexo的环境，编写新文章，然后利用hexo deploy来发布到Git，那么对于本地的Hexo的原始文件怎么管理呢？管理Hexo的原始文件的好处是：
- 换电脑布置环境非常方便
- 不用担心本地环境挂了导致源文件流失，毕竟一折腾就容易搞坏环境的

我们可以把Hexo博客的源文件也Host在github上，这里我们可以选择把Hexo博客的源文件布置到和Blog同一个`username.github.io`仓库，也可以选择将Hexo的源文件推到新建的一个Github Repo.
## 利用Github分支进行版本控制
### 利用分支进行版本控制的流程
通过新建一个hexo分支用于专门存放hexo代码。原先的master分支依然不变，作为hexo部署的分支。
每次在部署后，再把代码提交到hexo分支:
1. 到达Blog的本地文件根目录，本地创建git仓库  
`git init`

2. 添加远程库  
`git remote add origin git@github.com:user.name/user.name.github.io`  
注意，将其中的两个user.name置换成你自己的github名称

3. 创建hexo分支  
`git checkout -b hexo`  

4. 添加文件并提交，push到远程仓库  
`git add`  
> 可能出现的问题：如果你使用了第三方主题，在进行代码提交的时候，是无法将第三方主题提交到你的github repository中，会出现 untracked content的提示。  
> **原因：**第三方主题自身就是一个git项目，是没有办法将比人的git项目通过add和commit的方式添加到自己的git repository的。  
> **解决方式：** 删除第三方主题根目录下面的.git文件夹，再尝试提交git add

### 日常改动过程中的执行流程：
- 依次执行git add .、git commit -m "..."、git push origin hexo指令将改动推送到GitHub（此时当前分支应为hexo）；

- 执行hexo g -d发布网站到master分支上。

### 本地资料丢失或者换电脑，在其他电脑上面修改博客的步骤流程
- 使用 `git clone git@github.com:user.name/user.name.github.io.git`(默认的分支为hexo)
- 在本地clone下来的user.name.github.io文件夹下面通过git bash依次执行以下指令：
```sh
npm install -g hexo-cli
npm install hexo --save
npm install hexo-deployer-git
```
> 参考博客  
> [GitHub Pages + Hexo搭建博客](http://crazymilk.github.io/2015/12/28/GitHub-Pages-Hexo%E6%90%AD%E5%BB%BA%E5%8D%9A%E5%AE%A2/#more)  
> [Hexo博客代码版本控制](http://chenhuichao.com/2016/02/22/hexo/hexo-guide-3/)  

# 其他功能参考网页

****
## 博客首页的显示问题
### 内容全部显示，不收缩
解决方式：配置Next主题中的`_config.yml`里面的
`auto_excerpt = true`
### 内容显示一部分，但是显示格式不是Markdown的格式
使用 <!-- more --> 替代 auto_excerpt

## 添加文章阅读量统计与评论功能
[为NexT主题添加文章阅读量统计功能](https://notes.wanghao.work/2015-10-21-%E4%B8%BANexT%E4%B8%BB%E9%A2%98%E6%B7%BB%E5%8A%A0%E6%96%87%E7%AB%A0%E9%98%85%E8%AF%BB%E9%87%8F%E7%BB%9F%E8%AE%A1%E5%8A%9F%E8%83%BD.html#%E9%85%8D%E7%BD%AELeanCloud)

[hexo博客评论新神器——Valine](https://giserdaishaoqing.github.io/2017/11/24/hexo%E5%8D%9A%E5%AE%A2%E8%AF%84%E8%AE%BA%E6%96%B0%E7%A5%9E%E5%99%A8%E2%80%94%E2%80%94Valine/)

****
## 添加搜索功能 
### 场景  
博文多了之后，就需要一个搜索功能能够快速的找到自己以前的博客。所以在我们的博客上加入搜索功能是很有必要的一件事情。
### 安装插件  
- 直接在自己的博客文件夹下，点击鼠标右键选择Git Bash Here  
`npm install hexo-generator-searchdb --save`

- 修改站点配置文件:博客根目录下的_config.yml文件，可以在任意位置加入：

```c
search：
	path: search.xml
	field: post
	format: html
	limit: 10000
```
PS:每个冒号后面都有空格。
修改主题配置文件
我的路径：/blog/themes/next下的_config.yml文件，进行编辑。
```c
local_search:
	enable: true
```
PS:冒号后面都有空格。
此时，部署到github，打开网页就可以看到搜索功能了，容易添加，使用起来很方便，推荐添加，增加网站友好度。

****
## 添加站内聊天对话功能
[Hexo博客添加在线联系功能](https://www.ezlippi.com/blog/2018/01/next-chat.html)
****

## 添加RSS功能
### 基本步骤
#### 安装 RSS 插件
在blog根目录下执行命令安装 RSS 插件: hexo-generator-feed  
`npm install hexo-generator-feed --save`  

#### 配置 RSS 插件
编辑 Hexo 的配置文件 _config.yml，添加以下代码
```c
# RSS 订阅插件
plugin:
- hexo-generator-feed
#RSS 插件配置
feed:
  type: rss2
  path: rss.xml
  limit: 20
  hub:
  content: true
```
#### 主题开启 RSS 支持
NexT 主题，默认开启 RSS。其它主题请参考主题文档。

#### 生成 RSS
执行 `hexo clean && hexo g && hexo d` 重新生成博客文件并完成部署即可。

### 问题
打开RSS的时候：出现错误提示
> This page contains the following errors:  
> error on line 317 at column 18: PCDATA invalid Char value 11  
> Below is a rendering of the page up to the first error.

根据错误提示，用编辑器打开 public 目录下 的rss.xml 或 atom.xml。找到第317行18列，是一个未知字符小方块（原因应该是我从我的CSDN博客里面导出来的文章，出现了一些未知的问题）。根据小方块前后内容判断出来是哪个文章出现的问题。

打开对应的打开对应文章的.md文档，找到相应的的位置，替换出问题的字符。

重新生成 rss.xml 并部署: `hexo clean && hexo g && hexo d`  
问题解决
