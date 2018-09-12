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

因为这里面`static const int NumTurns = 5;`这是放在类的声明里面的，在这里就是一个变量的声明，并不是变量的定义，在内存里面是没有的。但是c++如果你在其他地方去使用的话，那是需要我们对这个进行先定义在使用的。如果要在其他地方使用，就需要提供一个定义：

`const int GamePlayer::Numturns;`

这个就可以放在你需要使用`GamePlayer::NumTurns`这个变量的文件里面，放在`*.cpp`文件里，而不是`*.h`文件中。

**注明:**由于在类的声明中已经给`GamePlayer::NumTurns`进行了赋值操作，所以在这里单独直接定义就可以调用声明进行赋值操作。

另外一种针对老式编译器不支持上述语法的解决方法：

```cpp
//在头文件中
class CostEstimate {
private:
    static const double FudgeFactor; //static class 常量声明
    ...
}
//在实现文件中去做
const double CostEstimate::FudgeFactor = 1.35;
```

> 上面这种方式可能问题：class在编译区间需要一个class的长两只，就是编译器不允许`static const int a` 完成初始设定，这样我们就要使用到 `the enum hack`的方式进行补偿。理论：一个属于enumerated type的数值是可以当成ints来使用的
 
```cpp
class GamePlayer {
private:
    enum {NumTurns = 5};
    int scores[Numturns];
}
```

**说明：** emum hack定义的内容，是不能够取地址的，取地址的操作是不合法的，而取#define的地址也是不合法的，但是取一个const的地址是合法的。如果不想让其他人获得这个pointer或者reference指向你的整数变量，enum就可以很好的实现这个功能。

`emum`和`#define`是绝对不会导致非必要的内存分配的。


## 实现宏定义

宏定义看起来像一个函数，但是不会导致函数的调用导致的额外开销，比如：

`#define CALL_WITH_MAX(a,b) f((a) > (b) ?(a):(b)）`

首先，写这样的宏必须为所有的实参都加上小括号，否则其他地方调用的时候会出现问题。但即使加上了，如果你实现这样的代码：

```cpp
int a = 5, b = 0;
CALL_WITH_MAX(++a,b);
CALL_WITH_MAX(++a,b+10);
```

在调用之前，a会递增之后在去调用，并且是否递增取决与它和谁比较。

![](/images/in-post/2018-09-11-EffectiveC++-item2/2018-09-12-19-20-59.png)

![](/images/in-post/2018-09-11-EffectiveC++-item2/2018-09-12-19-21-37.png)


## 小结

- 对于单纯变量，使用const对象或者enums替换`#define`
- 形如函数的宏，修改为inline函数替换#define