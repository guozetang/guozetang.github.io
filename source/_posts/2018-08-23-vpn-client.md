---
title: vpn-Shadowsocks使用教程
date: 2018-08-23 16:14:31
categories: vpn
tags: vpn
---

# Shadowsocks使用教程

## 浏览器插件

依然记得自己使用「红杏」的畅快体验──哪个网站不能访问了，按下图标添加到规则列表中，就可以「科学」地访问了。这种无缝的体验，靠 Shadowsocks 加另一款 Chrome 扩展 SwitchyOmega 也能实现，这里是[使用教程](https://github.com/FelisCatus/SwitchyOmega/wiki/GFWList)。

### Windows桌面应用

部署 Shadowsocks 完成后，浏览器就能实现科学上网了，但是像 Dropbox 等桌面应用的流量，还不能由 Shadowsocks 来代理。要实现桌面应用的代理，需要再借助其他应用，比如 [Proxifier](https://www.proxifier.com/)、[Surge for Mac](https://nssurge.com/)。

### 手机端应用

安卓手机只需要下载安装 [Shadowsocks 安卓版](https://github.com/shadowsocks/shadowsocks-android/releases)，并与桌面版一样，填入服务器 IP、端口、密码和加密方式，就可以设置全局或分应用代理。但是要实现「真正意义上」的 PAC 规则的话（也就是自定义哪些域名走代理、哪些不走），目前似乎还没有一个便捷可行的解决方案。

iOS 可以通过类 [Surge](https://itunes.apple.com/us/app/surge-3-web-developer-tool/id1329879957?ls=1&mt=8) 的 App 实现 PAC 规则下的自动翻墙。

Surge 目前定价 328 元，另有 Mac 版（另外收费）。作为一款兼具「科学上网」功能的网络开发调试利器，它完全值这个价。觉得太贵的话，可以使用相对便宜的 [Wingy](https://itunes.apple.com/us/app/wingy-smart-proxy-for-http/id1148026741?mt=8) 或者 [Potatso](https://itunes.apple.com/us/app/potatso-2/id1162704202?mt=8)，不过二者都没有前者来得稳定好用。
