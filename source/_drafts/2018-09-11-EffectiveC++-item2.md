---
title: Book. Effective C++ item2-尽量使用const, enum, inline替换#define
date: 2018-09-11 02:09:31
updated: 2018-09-11 02:09:31
categories: EffectiveC++
tags: EffectiveC++
top:
---
# Introduce

##常规变量

`c++`里面的`#define`后面的定义部分，是不算代码的一部分的。所以如果你使用`#define`:

`#define ASPECT_RATIO 1.653`

你希望这个代号`ASPECT RATIO`这个代号是能够被编译器加入到记号表（symbol table）里面，如果调试的时候，这个部分出现问题，能够很快的发现出来。但是很多时候我们的预处理器会把这个变量移除，只保留了一个`1.653`的常量，如果Debug的时候这个常量出现了错误，你是很难定位到自己需要修改代码的地方的，这就会造成我们在使用中Debug的时候很不方便。我们可以使用另外的方式来定义

```cpp
const double AspectRatio = 1.653;
```

修改之后，AspectRatio这个常量肯定会写入到记号表里面，是可以被编译器找到的。另外使用`#define` 可能会造成我们的代码里面有很多的object code 为 1.653, 但是使用`const`的方式，我们的代码里面就只会有一个`AspectRatio`。

如果是常量指针(constant pointers), 由于我们的常量一般是定义在`头文件`中的，所以我们需要将指针声明为`const`。如：

`const char* const authorName = "Scott Meyers";`

这里可以修改为`String`类型，使用String来存储字符串会比`char*`更加的合适，可定义为`const std::string authorName("Scott Meyers");`

## Class内部专属变量

**问题：**限制常量的作用域是在Class内部，这样就要将这个常量作为Class的一个membeer， 这样就能够确保这个常量至多只有一个实体，并且必须将其声明为`static member`。

```cpp
class GamePlayer {
private:
    static const int NumTurns = 5; //常量声明
    int scores[NumTurns];
}
```



In the begining, C++ was just C with some object-oriented features tacked on. `c++ = C with classes`. 但是到了后来，C++就包含了很多复杂的事物，我们在使用C++的时候可以将其看成四种不同的使用方式。

<!--more-->

- C语言。 按照C语言的规则去使用，没有模板，没有异常，没有重载
- Object-Oriented C+。这一部分是C with CLasses所追求的，classes, encapsulation, inheritance, polymorphism, virtual。按照面向对象的设计准则去做就好了
- Template C++. 泛型编程
- STL。STL是一个template程序库，对containers, iterators, algorithms 和 Function objects进行了限制。如果在编程中使用了STL, 那就必须遵守STL的规则

当你使用到其中的几种方式的时候，要习惯对自己的编程方式进行更换