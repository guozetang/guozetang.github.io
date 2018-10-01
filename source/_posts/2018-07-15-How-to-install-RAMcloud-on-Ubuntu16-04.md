---
title: How to install RAMcloud on Ubuntu16.04
date: 2018-07-15 11:38:13
updated: 2018-09-08 13:12:23
categories: Network
tags: Network
---

# Introduce

[RAMCloud](https://github.com/PlatformLab/RAMCloud) is a new class of super-high-speed storage for large-scale datacenter applications. It is designed for applications in which a large number of servers in a datacenter need low-latency access to a large durable datastore. RAMCloud offers the following properties:

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-16-47-41.png)

Project Link: [RAMCloud](https://ramcloud.atlassian.net/wiki/spaces/RAM/overview)

Office Installing introduce: [General Information for Developers](https://ramcloud.atlassian.net/wiki/spaces/RAM/pages/6848614/General+Information+for+Developers)

I have written the shell script to install the RAMCloud on Ubuntu 16.04 or Ubuntu18.04. If you want to build the RAMCloud as soon as possible, please fell free to use my repo on the github. Please read the README.md file in the repo and know how to use the scripts to help you.

- Github repo Link: [RAMCloud For Ubuntu16.04](https://github.com/guozetang/RAMCloud_Ubuntu16.04)
- Bitbucket repo Link: [RAMCloud For Ubuntu16.04](https://bitbucket.org/guozetang/ramcloud/src/master/)

If you have some issue with this script, please send [email](guoze.work@gmail.com) to me. I will reply it as soon as possible. In addtion, please read the next introduce about how to install Ramcloud by command if you want to understand each step to install RAMCloud.

<!--more-->
******

# Installing Ramcloud on Ubuntu16.04

## Necessary Tools
* GNU Make (Anything reasonably recent)
* GNU g++ (4.9.x)
* git (>= 1.6.0)
* Perl (Anything reasonably recent)
    * For mergedeps.pl, which automatically inserts included headers in source files into the make dependencies.
* Python 2.6, epydoc 
* Boost
    * If you're having issues with Boost on Ubuntu, check boost ticket #3844.
* pcre
* Doxygen 1.7.1
* protocol buffers
    * If you're getting lots of undefined reference errors during linking, it's likely that your libprotobuf is compiled with a different library ABI than RAMCloud. Check GCC's Dual ABI page and the "GLIBCXX_USE_CXX11_ABI" flag in GNUMakefile.
* ZooKeeper
* java and javac (>= 1.7.0_25)

If your system is Ubuntu 15.04 or 14.04, then you can just use this command to install these packets in your system.

```bash
apt-get install build-essential git-core doxygen=1.7.1 libpcre3-dev protobuf-compiler libprotobuf-dev libcrypto++-dev libevent-dev libboost-all-dev libgtest-dev libzookeeper-mt-dev zookeeper libssl-dev
```

## Analyze
I can't use this command to work on the Ubuntu 16.04. In addtion, I hope I can use the RAMCloud on any Ubuntu system. It means that it should be worked on Ubuntu 16.04 or 18.04. So I need to compile these packet by g++ or gcc or Cmake.

******

## Install Dependency

### Install build-essential, libssl-dev and git

We can get these two libs on Ubuntu 16.06 or 18.04. So we just need to use `apt-get` to get these lib.

```bash
sudo apt-get -y build-essential libssl-dev git
```

### Install gcc/g++ 4.9

The RAMCloud source code used some features in the C++11 Standard. As a result, we need to make sure the `gcc/g++` version have support the `C++11` Standard. Then we choose the `gcc/g++ 4.9` to install. Please follow the commands.

```bash
sudo apt-get install -y software-properties-common
sudo add-apt-repositocry -y ppa:ubuntu-toolchain-r/test
sudo apt-get update
mv /usr/bin/gcc /usr/bin/gcc.bak
mv /usr/bin/g++ /usr/bin/g++.bak
sudo apt-get install -y gcc-4.9
sudo apt-get install -y g++-4.9
lnif /usr/bin/g++-4.9 /usr/bin/g++
lnif /usr/bin/gcc-4.9 /usr/bin/gcc
g++ -v
gcc -v
```

If the `g++ -v` command can output the information like the followed graph. Then it means that you have installed the `g++ 4.9` correctly.

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-16-35-42.png)

If the `gcc -v` command can output the information like the followed graph. Then it means that you have installed the `gcc 4.9` correctly.

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-16-37-27.png)

You must to make sure you have installed the `gcc` and `g++` correctly when you want to continue the next steps.

### Install Java and Javac

```bash
sudo apt-add-repository -y ppa:webupd8team/java
sudo apt-get update
install_dependency oracle-java8-installer
java -version
```

If the `java -version` command can output the information like the followed graph. Then it means that you have installed the `java` correctly.

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-16-40-29.png)

### Install Cmake

We will use `Cmake` to compile the `Doxygen 1.7.2` in the next steps.

```bash
sudo apt-get install -y software-properties-common
sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get install -y cmake
cmake --version
```

Use `cmake --version` to check the version of cmake. If the `cmake --version` command can output the informaton like the followed graph. Then it means that you have installed the `cmake` correctly.

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-16-49-08.png)

******

### Download the packages which will be need in the next few steps.

```bash
git clone git@bitbucket.org:guozetang/ramcloud.git
cd ./ramcloud/packages/
```

When you get in to this director, you can find these packages in this director.
![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-20-16-41.png)

We will use these packages in the next steps.

### Install Pcre

```bash
tar -xzvf pcre-8.42.tar.gz
cd pcre-8.42
./configure --prefix=/usr/local/pcre
make
sudo make install
sudo echo "/usr/local/pcre/lib/" /etc/ld.so.conf.d/pcre.conf
```

### Install Python2.6

```bash
tar zxvf Python-2.6.6.tgz
cd Python-2.6.6  
./configure --prefix=/usr/local/python2.6  
make
sudo make install
sudo ln -s /usr/local/python2.6/bin/python2.6 /usr/bin/python2.6 -f
config_ld_lib /usr/local/python2.6/lib/ /etc/ld.so.conf.d/python2.6.conf
python2.6 --version
```

![](/images/in-post/2018-07-15-How-to-install-RAMcloud-on-Ubuntu16-04/2018-09-08-17-08-22.png)

### Install Boost

```bash
tar -xvf boost_1_52_0.tar
cd boost_1_52_0  
sudo ./bootstrap.sh
sudo ./b2 -j
sudo ./b2 install --prefix=/usr/local/boost_1_52_0
sudo echo "/usr/local/boost_1_52_0/lib/" /etc/ld.so.conf.d/boost_1_52_0.conf
```

### Install Doxygen1.7.2

```bash
tar -xzvf doxygen.tar.gz
cd doxygen
cd build
cmake -G "Unix Makefiles" ..
make
sudo make Install
```

### Install Protocol Buffers

```bash
tar -xzvf protobuf-2.6.1.tar.gz
cd $CURRENT_DIR/packages/protobuf-2.6.1  
./configure --prefix=/usr/local/protobuf  
make
make check
sudo make install
sudo echo "/usr/local/protobuf/lib/" /etc/ld.so.conf.d/protobuf.conf
sudo ln -s /usr/local/protobuf/bin/protoc /usr/bin/protoc -f
```

### Install Zookeeper

```bash
tar -xzvf zookeeper-3.3.6.tar.gz
cd zookeeper-3.3.6/src/c  
./configure --prefix=/usr/local/zookeeper  
make
sudo make install
sudo echo "/usr/local/zookeeper/lib/" /etc/ld.so.conf.d/zookeeper.conf
```

This last command `sudo echo "/usr/local/zookeeper/lib/" /etc/ld.so.conf.d/zookeeper.conf` can make the other application can find the `zookeeper lib` in the system.

## Config the Path

Add the `include path`,`library path` in the `/etc/profile`.

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/pcre/lib/:/usr/local/python2.6/lib/:/usr/local/boost_1_52_0/lib/:/usr/local/protobuf/lib/:/usr/local/zookeeper/lib/
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/pcre/lib/:/usr/local/python2.6/lib/:/usr/local/boost_1_52_0/lib/:/usr/local/protobuf/lib/:/usr/local/zookeeper/lib/
export C_INCLUDE_PATH=$C_INCLUDE_PATH:/usr/local/pcre/include/:/usr/local/python2.6/include/:/usr/local/boost_1_52_0/include/:/usr/local/protobuf/include/:/usr/local/zookeeper/include/c-client-src/
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/pcre/include/:/usr/local/python2.6/include/:/usr/local/boost_1_52_0/include/:/usr/local/protobuf/include/:/usr/local/zookeeper/include/c-client-src/
export PATH=$PATH:/usr/local/pcre/bin/:/usr/local/python2.6/bin/:/usr/local/protobuf/bin/:/usr/local/zookeeper/bin/
export PKG_CONFIG_PATH=:/usr/local/protobuf/lib/pkgconfig/
```

## Install RAMCloud

```bash
git clone https://github.com/PlatformLab/RAMCloud.git
cd RAMCloud
make -j12 DEBUG=no
```
