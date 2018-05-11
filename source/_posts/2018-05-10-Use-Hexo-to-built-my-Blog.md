---
title: 使用Hero+Next主题+Github搭建博客
date: 2018-05-10 15:13:51
categories:
tags: hexo
---
使用Jekyll搭建在github上博客已经快一年了，但一年的时间并没有写很多的文章。一部分原因是由于自己懈怠，另一部分也由于Jekyll写博客有很多不便之处。不能自动生成目录，以及每次新建文章都需要自己的手动设置目录结构以及添加Jekyll解析的格式内容在每一篇文章中，这是一件非常繁琐而无趣的工作。遵循自己动手丰衣足食的原则，查询目前比较流行的搭建博客的方式之后，决定使用Hero+Next主题在github上搭建博客。本篇博客记录搭建过程中的配置与优化。

> 具体搭建博客过程请参考：
> - [Jekyll迁移到Hexo搭建个人博客](https://www.ezlippi.com/blog/2016/02/jekyll-to-hexo.html)  
适合熟悉原理的同学，作者详细的讲解了使用Hexo与Next主题搭建博客的过程。
>   
> - 如果完全不熟悉Hexo的原理以及之前没有使用过git的同学，请参考：  
   [使用 Hexo 基于 GitHub Pages 搭建个人博客（一）](https://ehlxr.me/2016/07/23/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%B8%80%EF%BC%89/)   
   [使用 Hexo 基于 GitHub Pages 搭建个人博客（二）](https://ehlxr.me/2016/07/23/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%BA%8C%EF%BC%89/)
   
完成Hexo搭建博客之后，可以参考一些配置说明,做一些优化：
[使用 Hexo 基于 GitHub Pages 搭建个人博客](https://ehlxr.me/2016/08/30/%E4%BD%BF%E7%94%A8Hexo%E5%9F%BA%E4%BA%8EGitHub-Pages%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2%EF%BC%88%E4%B8%89%EF%BC%89/)

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

# 其他功能参考网页
### 添加阅读量统计功能
[为NexT主题添加文章阅读量统计功能](https://notes.wanghao.work/2015-10-21-%E4%B8%BANexT%E4%B8%BB%E9%A2%98%E6%B7%BB%E5%8A%A0%E6%96%87%E7%AB%A0%E9%98%85%E8%AF%BB%E9%87%8F%E7%BB%9F%E8%AE%A1%E5%8A%9F%E8%83%BD.html#%E9%85%8D%E7%BD%AELeanCloud)

