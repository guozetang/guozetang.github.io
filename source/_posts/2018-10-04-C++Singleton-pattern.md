---
title: C++软件设计模式之Singleton
date: 2018-10-04 15:09:31
updated: 2018-10-05 15:09:31
categories: C++
tags: C++
top:
---

![](/images/in-post/2018-10-04-C++Singleton-pattern/2018-10-09-07-43-58.png)

什么是`Singleton`? 单例模式（Singleton），保证一个类仅有一个实例，并提供一个访问它的全局访问点。

> 可以考虑在下面的一些场景中应用：
> - Windows的Task Manager（任务管理器）就是很典型的单例模式（这个很熟悉吧），想想看，是不是呢，你能打开两个windows task manager吗？ 不信你自己试试看哦~ 
> - windows的Recycle Bin（回收站）也是典型的单例应用。在整个系统运行过程中，回收站一直维护着仅有的一个实例。
> - 网站的计数器，一般也是采用单例模式实现，否则难以同步。
> - 应用程序的日志应用，一般都何用单例模式实现，这一般是由于共享的日志文件一直处于打开状态，因为只能有一个实例去操作，否则内容不好追加。
> - Web应用的配置对象的读取，一般也应用单例模式，这个是由于配置文件是共享的资源。
> - 在数据库连接池的设计一般也是采用单例模式，因为数据库连接是一种数据库资源。数据库软件系统中使用数据库连接池，主要是节省打开或者关闭数据库连接所引起的效率损耗，这种效率上的损耗还是非常昂贵的，因为何用单例模式来维护，就可以大大降低这种损耗。
> - 多线程的线程池的设计一般也是采用单例模式，这是由于线程池要方便对池中的线程进行控制。
> - 操作系统的文件系统，也是大的单例模式实现的具体例子，一个操作系统只能有一个文件系统
> 引用部分内容来自于：[单例模式的常见应用场景](https://blog.csdn.net/tanyujing/article/details/14160941?utm_source=copy)

单例模式应用的场景一般发现在以下条件下：

- 资源共享的情况下，避免由于资源操作时导致的性能或损耗等。如上述中的日志文件，应用配置
- 控制资源的情况下，方便资源之间的互相通信。如线程池等。

<!--more-->

---

## 如果不使用单例模式是什么样子呢？

**应用场景：** 我们使用`srand(time(0))`去生产一个随机数字，因为这个函数生成的是伪随机数，所以如果我们很快的频率去调用这个函数的话，就会出现这个函数给出一个同样的随机数字。

```cpp
#include <cstdlib>  // for rand()
#include <iostream>

class Random {
 public:
  Random() {
    int seed = time(0);
    srand(seed);
  }
  int operator()(int a, int b) const { return (rand() % b) + a; }

 private:
  Random(const Random&);
  Random& operator=(const Random&);
};

int main() {
  Random random;
  std::cout << random(1, 100) << std::endl;
}
```

Output:

```bash
$./run
44
$./run //和第一次间隔时间比较长
72
$./run //后面三个运行程序的速度比较快的话，就会出现得到一样的随机数
44
$./run
44
$./run
44
```

> Function rand () Vs srand()
> - rand() function is used in C to generate random numbers. If we generate a sequence of random number with rand() function, it will create the same sequence again and again every time program runs. Say if we are generating 5 random numbers in C with the help of rand() in a loop, then every time we compile and run the program our output must be the same sequence of numbers.
> - The srand() function sets the starting point for producing a series of pseudo-random integers. If srand() is not called, the rand() seed is set as if srand(1) were called at program start. Any other value for seed sets the generator to a different starting point. Standard prac tice is to use the result of a call to srand(time(0)) as the seed

## 使用单例模式

单一模式的实现方式：

- Place constructors and assignment in private section.
- Declare a static instance variable as a data attribute of the class
- Define the static instance variable somewhere in the anonymous namespace.
- Define a static class member function(`getInstance`) to access the instance variable. 

## glut实现模式 (懒汉模式（线程不安全）)

```cpp
#include <cstdlib>  // for rand()
#include <iostream>

class Random {
public:
  static Random* getInstance(); //Define a static class member function
  int operator()(int a, int b) const {
    return (rand() % b) + a;
  }
private:
  static Random* instance;  //Declare a static instance variable
  Random(const Random&);
  Random& operator=(const Random&); // Constructors and assignment in private
  Random() {
    int seed = time(0);
    srand(seed);
  }
};
Random* Random::getInstance() {
  if ( !instance ) instance = new Random;
  return instance;
}
Random* Random::instance = NULL; //Define the static instance variable somewherr

int main() {
  Random* random = Random::getInstance();
  std::cout << (*random)(1,100) << std::endl;
  delete random;
}

```

这种`glut`的单例模式存在这一定的问题，在《程序员的自我修养》中给出了一个例子。在单例模式中，这是一段典型的 double-check 的代码.

```cpp
volatile T* pInst = nullptr;
T* GetInstance() {
    if (nullptr == pInst) {
        lock();
        if (nullptr == pInst) {
            pInst = new T;
        }
        unlock();
    }
    return pInst;
}
```

- `if (nulptr == pInst)` 中的if 确保仅在 pInst 是空指针的情况下才去获取锁并尝试构造对象；
- `if (nullptr == pInst)` 的 if 则是为了防止这样一种可能，避免重复操作和内存泄露：在外层 if 检测是，pInst 尚为空，但是，待 lock() 执行完毕后，别的线程已经为 pInst 赋值。

这段代码，乍一看是没有问题的；但仍需小心揣摩。我们看 `pInst = new T`; 这一行代码，它基本完成了三件事情

- 为 T 类型的对象分配内存；
- 在这片内存上执行 T 的构造函数；
- 将这片内存的起始地址赋值给 pInst。

由于构造函数的执行和指针的赋值是互不依赖的，所以 CPU 可能会交换这两个步骤的顺序。因此，在线程执行的过程中，可能存在这样一种情况：nullptr != pInst，但是它指向的对象尚未构造成功。于是，如果在这一时刻，当前线程被中断，并且其它线程调用 GetInstance 函数，那么函数在外层 if 执行之后，会直接返回 pInst 的值。而此时 pInst 实际上指向的是一片尚未初始化的内存。如果线程代码对 pInst 进行访问，那么程序很有可能就会崩溃。

为了解决这类 CPU 动态调度导致的问题，我们需要有在某些情况下阻止指令换序执行的能力。然而遗憾的是，由于动态调度是 CPU 的功能，所以在高级语言的层次，我们没有通用的解决办法——只能依赖具体的 CPU 架构，对代码进行调整。对于 i386 架构的 CPU 来说，它提供了一条指令 mfence（memory fence 的缩写），可以阻止这种换序执行。

```cpp
#define barrier() __asm__ volatile("mfence")
volatile T* pInst = nullptr;
T* GetInstance() {
    if (nullptr == pInst) {
        lock();
        if (nullptr == pInst) {
            T* temp = new T;
            barrier();
            pInst   = temp;
        }
        unlock();
    }
    return pInst;
}
```

用 barrier() 保证了在 pInst 被赋值之前，相关内存区域已经正确地初始化了。

## Meyers单例模式实现

```cpp
#include <cstdlib>  // for rand()
#include <iostream>

class Random {
public:
  static Random& getInstance();
  int operator()(int a, int b) const { 
    return (rand() % b) + a; 
  }
private:
  Random(const Random&);
  Random& operator=(const Random&);
  Random() {
    int seed = time(0);
    srand(seed);
  }
};
Random& Random::getInstance() {
  static Random instance;
  return instance;
}

int main() {
  Random& random = Random::getInstance();
  std::cout << random(1,100) << std::endl;
}
```

第二种实现方式和之前一种实现方式的区别在：
第一种

- 懒汉模式申明了一个静态对象，在用户第一次调用时初始化，虽然节约了资源，但第一次加载时需要实例化，反映稍慢一些，而且在多线程不能正常工作。


```cpp
//First one
Random* Random::getInstance() {
  if ( !instance ) instance = new Random;
  return instance;
}
Random* Random::instance = NULL; //Define the static instance variable somewherr

```

第二种：

- 在类加载时就完成了初始化，所以类加载较慢，但获取对象的速度快。 这种方式基于类加载机制避免了多线程的同步问题，但是也不能确定有其他的方式（或者其他的静态方法）导致类装载，这时候初始化instance显然没有达到懒加载的效果。

```cpp
//Second One
Random& Random::getInstance() {
  static Random instance;
  return instance;
}
```

推荐阅读： [设计模式（二）单例模式的七种写法](https://blog.csdn.net/itachi85/article/details/50510124)