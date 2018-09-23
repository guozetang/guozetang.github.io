---
title: C++声明与定义的区别
date: 2018-09-11 02:09:31
updated: 2018-09-11 02:09:31
categories: C++
tags: C++
top:
---

# Introduce

## 声明

声明一个变量只是将变量名标识符的有关信息告诉编译器，使编译器“认识”该标识符，但声明`不一定引起内存的分配`(没有内存分配)。声明有两个作用：

- 告诉编译器，这个名字已经匹配到一块内存上，下面的代码用到变量或者对象是在别的地方定义的。声明可以出现多次。
- 告诉编译器，这个名字已经被预定了，别的地方再也不能用它来作为变量名或对象名。

```cpp
class MyClass
{
  //数据成员细节...
  //成员函数细节...
};
```

上述声明仅告诉编译器有自定义类型MyClass,编译器仅对其进行语汇分析及名字的决议，并未占用内存!

## 定义

定义就是（编译器）创建一个对象，为这个对象`分配一块内存`，并给它取上一个名字，这个名字就是就是我们经常所说的变量名或对象名。

在C++程序中，大多数情况下变量声明也就是变量定义，声明变量的同时也就完成了变量的定义，只有声明外部变量时例外。

**声明Vs定义**： 是声明还是定义，判断的原则是看是否占用内存

```cpp
class MyClass //类的声明，无内存占有
{
  string myString; //string的声明
};
```

这里面的`string myString;`实在类的声明里面，并没有实际申请内存，所以这就是声明，因为它并没有实际申请内存。

```cpp
#include<iostream>

//全局作用域
string myString;//定义，myString是实例化的string！

int main()
{
  //Main函数体内
  string myAnotherString;//定义，myAnotherString是实例化的string！
  return 0;
}

```

这里面的`string myString;`是全局定义，全局对象一开始就是要申请内存的。

小结：变量和对象不加extern永远是定义,类中的除外。 函数只有函数头是声明，有函数体的是定义。类永远只是声明。类成员函数的函数体是定义。

```cpp
class MyClass
{
    static int x; //这里的x是声明
    static const int a; //这里的a是声明
    //非static变量在类实例化时才分配内存.
    MyClass();//这里的函数是声明
};
int MyClass::x;//这是定义
const int MyClass::a=11;//这是定义
```

```cpp
//这里的Fun是定义，因为有函数体
int  fun(int a,int b)
{  
    int  c;
    c=a+b;
    return c;
}

//这里的Fun是声明，因为这里只有函数头
int  fun(int a,int b)；
```