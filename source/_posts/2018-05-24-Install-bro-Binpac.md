---
title: Ubuntu 16.04安装bro和Binpac
date: 2018-05-24 13:30:32
categories: Network
tags: Network
---
# 前言
﻿Bro is a powerful network analysis framework that is much different from the typical IDS you may know. 
 
BinPAC is a high level language for describing protocol parsers and generates C++ code. It is currently maintained and distributed with the Bro Network Security Monitor distribution, however, the generated parsers may be used with other programs besides Bro.
<!--more-->

# 软件安装
## 安装Bro
### 前期依赖包安装
Bro requires the following libraries and tools to be installed before you begin:

> -   Libpcap ([http://www.tcpdump.org](http://www.tcpdump.org/))
> -   OpenSSL libraries ([http://www.openssl.org](http://www.openssl.org/))
> -   BIND8 library
> -   Libz
> -   Bash (for BroControl)
> -   Python 2.6 or greater (for BroControl)

To build Bro from source, the following additional dependencies are required:

> -   CMake 2.8 or greater ([http://www.cmake.org](http://www.cmake.org/))
> -   Make
> -   C/C++ compiler with C++11 support (GCC 4.8+ or Clang 3.3+)
> -   SWIG ([http://www.swig.org](http://www.swig.org/))
> -   Bison (GNU Parser Generator)
> -   Flex (Fast Lexical Analyzer)
> -   Libpcap headers ([http://www.tcpdump.org](http://www.tcpdump.org/))
> -   OpenSSL headers ([http://www.openssl.org](http://www.openssl.org/))
> -   zlib headers
> -   Python

To install the required dependencies, you can use:
-   DEB/Debian-based Linux:

```bash
sudo apt-get install cmake make gcc g++ flex bison libpcap-dev libssl-dev python-dev swig zlib1g-dev
```

### Installing from Source

Bro releases are bundled into source packages for convenience and are available on the  [bro downloads page](https://www.bro.org/download/index.html).

Alternatively, the latest Bro development version can be obtained through git repositories hosted at  `git.bro.org`. See their  [git development documentation](https://www.bro.org/development/howtos/process.html).
```sh
git clone --recursive git://git.bro.org/bro
cd bro
./configure
make
make install
```
### 配置环境变量
`export PATH=/usr/local/bro/bin:$PATH`
> 注意：由于Export的方式，只是在本次登录sh的过程中有效果的，所以后续需要重新配置


## 安装Binpac
## [依赖包文件](https://www.bro.org/sphinx-git/components/binpac/README.html#id7)

BinPAC relies on the following libraries and tools, which need to be installed before you begin:

> -   Flex (Fast Lexical Analyzer)
>     
>     Flex is already installed on most systems, so with luck you can skip having to install it yourself.
>     
> -   Bison (GNU Parser Generator)
>     
>     Bison is also already installed on many system.
>     
> -   CMake 2.6.3 or greater
>     
>     CMake is a cross-platform, open-source build system, typically not installed by default. See  [http://www.cmake.org](http://www.cmake.org/)  for more information regarding CMake and the installation steps below for how to use it to build this distribution. CMake generates native Makefiles that depend on GNU Make by default
>
###  Installing from Source
To build and install into  `/usr/local`:
```
git clone --recursive git@github.com:bro/binpac.git
cd binpac
./configure
cd build
make
make install
```
This will perform an out-of-source build into the build directory using the default build options and then install the binpac binary into  `/usr/local/bin`.

You can specify a different installation directory with:

./configure --prefix=<dir>

Run  `./configure --help`  for more options.

## 下载 BinPAC Sample Analyzer
这个是一个python脚本，能够按照bro的规则生成出Binpac需要书写的文件，生成出来之后，我们只需要填写这些文件就可以了。

##  Installing from Source
 从Github上面拷贝例子的文件下来
`git clone https://github.com/grigorescu/binpac_quickstart`
Inside the  binpac_quickstart  directory, simply run:

`python start.py Sample "Sample Protocol" ../bro --tcp --buffered`

This will generate all the necessary files for this sample analyzer. The  ../bro  argument here just points to the Bro source tree. Make sure to change it if yours lives in a different location. See the  start.py  —helpoptions for more explanation of the options.

Bro should be able to compile the generated template code right away, but files may have some “TODO” comments in them to mark places that typically need to be changed depending on the specifics of the protocol analyzer you want to make.

# 遇到的问题

## 书写Analyzer时候遇到的问题
### Bro安装过程中遇到的错误
#### 错误1 ./configure错误
```
bro# ./configure --with-pcap=/opt/pfring  
Build Directory : build  
Source Directory: /root/install/bro  
CMake Error at CMakeLists.txt:7 (include):  
include could not find load file:

cmake/CommonCMakeConfig.cmake

CMake Error at CMakeLists.txt:52 (include):  
include could not find load file:

FindRequiredPackage

– Found sed: /bin/sed  
CMake Error at CMakeLists.txt:64 (FindRequiredPackage):  
Unknown CMake command "FindRequiredPackage".

– Configuring incomplete, errors occurred!  
See also "/root/install/bro/build/CMakeFiles/CMakeOutput.log".
```
解决方案：
克隆的时候需要添加--recursive参数，保证自己下载的子模块
`git clone --recursive git://git.bro.org/bro`

### 编译自己书写的Analyzer时候的问题
#### 错误1 
```
 make[3]: Entering directory '/users/Guoze/00_Workbench/bro/build'
make[3]: *** No rule to make target '../src/binpac', needed by 'src/binpac-lib_pac.h'.  Stop.
make[3]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
CMakeFiles/Makefile2:946: recipe for target 'src/CMakeFiles/pac-binpac-lib.pac.dir/all' failed
make[2]: *** [src/CMakeFiles/pac-binpac-lib.pac.dir/all] Error 2
make[2]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
Makefile:138: recipe for target 'all' failed
make[1]: *** [all] Error 2
make[1]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
Makefile:15: recipe for target 'all' failed
make: *** [all] Error 2
 ```
解决方案：
这个错误很大可能性是你使用了在该文件目录下没有权限，加入sudo make

#### 错误2
```
[  1%] Completed 'project_caf'
make[3]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
[  2%] Built target project_caf
make[2]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
Makefile:138: recipe for target 'all' failed
make[1]: *** [all] Error 2
make[1]: Leaving directory '/users/Guoze/00_Workbench/bro/build'
Makefile:15: recipe for target 'all' failed
make: *** [all] Error 2
```
解决方案：
这个错误很大可能性是你使用了`make -j 4`多核编译的方式导致的，取消多核编译，仅仅使用make

