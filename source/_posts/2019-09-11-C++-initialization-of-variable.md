---
title: C++ 变量的初始化问题
date: 2018-09-11 02:09:31
updated: 2018-09-11 02:09:31
categories: C++
tags: C++
top:
---

# 介绍

在C++语言中int a;表示声明了整型a但未初始化，而C++中的对象总是会被初始化的，无论是否写了圆括号或者是否写了参数列表，例如：

```c++
int basic_var;      // 未初始化：应用"默认初始化"机制
CPerson person;     // 初始化：以空的参数列表调用构造函数
```

参考链接：[C++手稿：哪些变量会自动初始化？](https://harttle.land/2015/10/05/cpp-variable-init.html)

**默认初始化规则**
定义基本数据类型变量（单个值、数组）的同时可以指定初始值，如果未指定C++会去执行默认初始化(default-initialization)。 那么什么是”默认初始化”呢？

- 栈中的变量（函数体中的自动变量）和堆中的变量（动态内存）会保有不确定的值；
- 全局变量和静态变量（包括局部静态变量）会初始化为零(它们存储在进程的BSS段（这是全零的一段内存空间）)。
> C++11: If no initializer is specified for an object, the object is default-initialized; if no initialization is performed, an ?
> object with automatic or dynamic storage duration has indeterminate value. Note: Objects with static or thread storage
> duration are zero-initialized, see 3.6.2.

所以函数体中的变量定义是这样的规则：

```c++
int i;                    // 不确定值
int i = int();            // 0
int *p = new int;         // 不确定值
int *p = new int();       // 0
```

## 几种初始化情况对比

### 全局变量(全局静态变量) Vs 局部变量(局部静态变量)

全局变量，全局静态变量和局部静态变量是存放在BSS段的，所以默认初始化为 `0`。局部变量是在栈里面，所以初始化情况不确定。

### 类成员变量初始化

可见内置类型的成员变量的”默认初始化”行为取决于所在对象的存储类型，而存储类型对应的默认初始化规则是不变的。 所以为了避免不确定的初值，通常会在构造函数中初始化所有内置类型的成员。Effective C++: Item 4一文讨论了如何正确地在构造函数中初始化数据成员。 这里就不展开了，直接给出一个正确的初始化写法：

### 嵌套类的变量初始化

规则还是是一样的，默认初始化行为取决于它所属对象的存储类型。封闭类（Enclosing）中成员对象的内置类型成员变量的”默认初始化”行为取决于当前封闭类对象的存储类型，而存储类型对应的默认初始化规则仍然是不变

## 代码例子

```cpp
#include <iostream>

//1. 全局变量与静态全局变量
int g_var;
int *g_pointer;
static int g_static;


class A{
public:
    int v;
}; 

class B{
public:
    int v;
    A a;
};

//2. 全局成员变量
A class_g_var;
B class_b_g_var;

int main(){
    //1. 局部变量与静态局部变量
    int l_var;
    int *l_pointer;
    static int l_static;

    // 2. 具备成员变量
    A class_l_var;
    static A class_l_static;

    B class_b_l_var;

    std::cout<<"--------Global Vs Local Variate---------"<< std::endl;
    std::cout<<"Global Variate: "<< g_var << std::endl;
    std::cout<<"Global Point: "<< g_pointer << std::endl;
    std::cout<<"Global Static Variate: "<< g_static << std::endl;

    std::cout<<"Local Variate: "<< l_var << std::endl;
    std::cout<<"Local Point: "<< l_pointer << std::endl;
    std::cout<<"Local Static Variate: "<< l_static << std::endl;

    std::cout<<"--------Global Vs Local Class Variate---------"<< std::endl;
    std::cout<<"Global Class Variate: "<< class_g_var.v << std::endl;
    std::cout<<"Local Class Variate: "<< class_l_var.v << std::endl;
    std::cout<<"Local Static Class variate: "<< class_l_static.v << std::endl;  

    std::cout<<"--------2lGlobal Vs Local Class Variate---------"<< std::endl;
    std::cout<<"Global Class Variate: "<< class_b_g_var.v << "  " << class_b_g_var.a.v << std::endl;
    std::cout<<"Local Class Variate: "<< class_b_l_var.v << "   " << class_b_l_var.a.v <<std::endl;

    return 0;  
};

```

**Makefile**

```makefile
CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -std=c++11 -W -Wall -Weffc++ -Wextra -pedantic -O0

OBJS = \
	main.o
EXEC = run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
```