---
title: Hexo使用中的优化以及问题解决记录
date: 2018-09-08 02:09:31
updated: 2018-09-08 02:09:31
categories: Hexo
tags: Hexo
top:
---
# 前言
记录对Hexo的优化，以及配置Hexo中遇到的问题以及解决方案。

<!--more-->
# 问题

## 本地搜索路径不正确
### 问题描述
期待路径是`http://guozet.me/post/postname/`,然后实际得到的路径是`/post/postname/`。
先检查自己的[配置过程](https://github.com/wzpan/hexo-generator-search)：

```bash
$ npm install hexo-generator-search --save
```

站点配置文件：`_config.yml`中任意位置加入：

```bash
search:
  path: search.xml
  field: post
```

我本地的配置与上面的配置是一致的，但是路径位置就是不对，经过搜索，在这个[链接](https://github.com/iissnan/hexo-theme-next/issues/1852)解决了我的问题。

### 解决思路
在搜索页面，使用`F12`打开确定自己的搜索路径链接是否有问题。
![](/images/in-post/2018-09-08-Hexo-Optimize-and-patch/2018-09-08-02-18-22.png)
发现在路径位置：

```bash
<a href="//post/Write-first-Analyzer-rip/" class="search-result-title">在<b class="search-keyword">Bro</b>中完成第一个协议分析器—RIP协议</a>
```

这里有两个`//`在post前面，直接修改配置文件，去掉一个`/`。
修改localsearch.swig源码:

```bash
//var articleUrl = decodeURIComponent(data.url);
var articleUrl = decodeURIComponent(data.url).substring(1);//截取第一位/斜杠
```

## 修改页面宽度

我们用Next主题是发现在电脑上阅读文章时内容两边留的空白较多，这样在浏览代码块时经常要滚动滚动条才能阅读完整，体验不是很好，下面提供修改内容区域的宽度的方法。
NexT 对于内容的宽度的设定如下：

700px，当屏幕宽度 < 1600px
900px，当屏幕宽度 >= 1600px
移动设备下，宽度自适应
如果你需要修改内容的宽度，同样需要编辑样式文件。
在Mist和Muse风格可以用下面的方法：

编辑主题的 source/css/_variables/custom.styl 文件，新增变量：

```cpp
// 修改成你期望的宽度
$content-desktop = 700px

// 当视窗超过 1600px 后的宽度
$content-desktop-large = 900px
```