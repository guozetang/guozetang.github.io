---
title: C++之Rule of Five
date: 2018-09-05 10:14:31
updated: 2018-09-05 12:14:31
categories: C++
tags: C++
---

### Rule of five
Because the presence of a user-defined destructor, copy-constructor, or copy-assignment operator prevents implicit definition of the  [move constructor](https://en.cppreference.com/w/cpp/language/move_constructor "cpp/language/move constructor")  and the  [move assignment operator](https://en.cppreference.com/w/cpp/language/move_operator "cpp/language/move operator"), any class for which move semantics are desirable, has to declare all five special member functions:

```cpp
class rule_of_five
{
    char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block
    rule_of_five(const char* s, [std::size_t](http://en.cppreference.com/w/cpp/types/size_t) n) // to avoid counting twice
    : cstring(new char[n]) // allocate
    {
        [std::memcpy](http://en.cppreference.com/w/cpp/string/byte/memcpy)(cstring, s, n); // populate
    }
 public:
    rule_of_five(const char* s = "")
    : rule_of_five(s, [std::strlen](http://en.cppreference.com/w/cpp/string/byte/strlen)(s) + 1)
    {}
    ~rule_of_five()
    {
        delete[] cstring;  // deallocate
    }
    rule_of_five(const rule_of_five& other) // copy constructor
    : rule_of_five(other.cstring)
    {}
    rule_of_five(rule_of_five&& other) noexcept // move constructor
    : cstring([std::exchange](http://en.cppreference.com/w/cpp/utility/exchange)(other.cstring, nullptr))
    {}
    rule_of_five& operator=(const rule_of_five& other) // copy assignment
    {
         return *this = rule_of_five(other);
    }
    rule_of_five& operator=(rule_of_five&& other) noexcept // move assignment
    {
        [std::swap](http://en.cppreference.com/w/cpp/algorithm/swap)(cstring, other.cstring);
        return *this;
    }
// alternatively, replace both assignment operators with 
//  rule_of_five& operator=(rule_of_five other) noexcept
//  {
//      std::swap(cstring, other.cstring);
//      return *this;
//  }
};
```
Unlike Rule of Three, failing to provide move constructor and move assignment is usually not an error, but a missed optimization opportunity.

**第五条：再谈重载、覆盖和隐藏**

在C++中，无论在类作用域内还是外，两个（或多个）同名的函数，可能且仅可能是以下三种关系：重载（Overload）、覆盖（Override）和隐藏（Hide），因为同名，区分这些关系则是根据参数是否相同、是否带有const成员函数性质、是否有virtual关键字修饰以及是否在同一作用域来判断。在第四条中，我们曾提到了一些关于重载、覆盖的概念，但只是一带而过，也没有提到隐藏，这一篇我们将详细讨论。

1、首先说的是重载，有一个前提必须要弄清楚的是，如果不在类作用域内进行讨论，两个（或多个）同名函数之间的关系只可能是重载或隐藏，这里先说重载。考虑以下事实：
```cpp
int foo(char c){...} 
void foo(int x){...}
```
这两个函数之间的关系是**重载（overload），即相同函数名但参数不同，并注意返回类型是否相同并不会对重载产生任何影响**。

也就是说，**如果仅仅是返回类型不相同，而函数名和参数都完全相同的两个函数，不能构成重载**，编译器会告知"ambiguous"（二义性）等词以表达其不满：

```cpp
//Can't be compiled!

int fooo(char c){...}
void fooo(char c){...}

char c = 'A';
fooo(c); // Which one? ambiguous
```
在第四条中，已经讲述过，重载是编译期绑定的静态行为，不是真正的多态性，那么，编译器是根据什么来进行静态绑定呢？又是如何确定两个（或多个）函数之间的关系是重载呢？

有以下判定依据：

（1）相同的范围：即作用域，这里指在同一个类中，或同一个名字空间，即**C++的函数重载不支持跨越作用域进行**（读者可再次对比Java在这问题上的神奇处理，既上次Java给我们提供了未卜先知的动态绑定能力后，Java超一流的意识和大局观再次给Java程序员提供了跨类重载的能力，如有兴趣可详细阅读《Thinking in Java》的相关章节，其实对于学好C++来讲，去学一下Java是很有帮助的，它会告诉你，同样或类似的问题，为什么Java要做这样的改进），这也是区别重载和隐藏的最重要依据。

关于“C++不能支持跨类重载”，稍后笔者会给出代码来例证这一点。

（2）函数名字相同（基本前提）

（3）函数参数不同（基本前提，否则在同一作用域内有两个或多个同名同参数的函数，将产生ambiguous，另外注意，对于成员函数，是否是const成员函数，即函数声明之后是否带有const标志， 可理解为“参数不同“），第（2）和第（3）点统称“函数特征标”不同

（4）virtual关键字可有可无不产生影响（因为第（1）点已经指出，这是在同一个类中）

即**“相同的范围，特征标不同（当然同名是肯定的），发生重载“**。

2、覆盖（override），真正的多态行为，通过虚函数来实现，所以，编译器根据以下依据来进行判定两个（注意只可能是两个，即使在继承链中，也只是最近两个为一组）函数之间的关系是覆盖：

（1）不同的范围：即使用域，两个函数分别位于基类和派生类中

（2）函数名字相同（基本前提）

（3）函数参数也相同（基本前提），第（2）和第（3）点统称“函数特征标”相同

（4）基类函数必须用virtual关键字修饰

即**“不同的范围，特征标相同，且基类有virtual声明，发生覆盖“**。

3、隐藏（Hide），即：

（1）如果派生类函数与基类函数同名，但参数不同（特征标不同），此时，无论是否有virtual关键字，基类的所有同名函数都将被隐藏，而不会重载，因为不在同一个类中；

（2）如果派生类函数与基类函数同名，且参数也相同（特征标相同），但基类函数没有用virtual关键字声明，则基类的所有同名函数都将被隐藏，而不会覆盖，因为没有声明为虚函数。

即**“不同的范围，特征标不同（当然同名是肯定的），发生隐藏”**，或**"不同的范围，特征标相同，但基类没有virtual声明，发生隐藏“**。

可见有两种产生隐藏的情况，分别对应不能满足重载和覆盖条件的情况。

另外必须要注意的是，在类外讨论时，也可能发生隐藏，如在名字空间中，如下述代码所示：
```cpp
#include <iostream>
using namespace std;

void foo(void) { cout << "global foo()" << endl; }
int foo(int x) { cout << "global foo(int)" << endl; return x; }
namespace a
{
        void foo(void) { cout << "a::foo()" << endl; }
        void callFoo(void) 
        { foo();
           // foo(10); Can't be compiled! }
}

int main(int argc, char** argv)
{
        foo();
        a::callFoo();
        return 0;
}
```
输出结果：

```cpp
global foo() 
a::foo()
```
注意，名字空间a中的foo隐藏了其它作用域（这里是全局作用域）中的所有foo名称，foo(10)不能通过编译，因为全局作用域中的int foo(int)版本也已经被a::foo()隐藏了，除非使用::foo(10)显式进行调用。

这也告诉我们，无论何时，都**使用完整名称修饰（作用域解析符调用函数，或指针、对象调用成员函数）是一种好的编程习惯**。

好了，上面零零散散说了太多理论的东西，我们需要一段实际的代码，来验证上述所有的结论：
```cpp
#include <iostream>
using namespace std;

class Other
{
        void* p;
};

class Base
{
public:
        int iBase;
        Base():iBase(10){}
        virtual void f(int x = 20){ cout << "Base::f()--" << x << endl; }
        virtual void g(float f) { cout << "Base::g(float)--" << f << endl; }
        void g(Other& o) { cout << "Base::g(Other&)" << endl; }
        void g(Other& o) const { cout << "Base::g(Other&) const" << endl;}
};

class Derived : public Base
{
public:
        int iDerived;
        Derived():iDerived(100){}
        void f(int x = 200){ cout << "Derived::f()--" << x << endl; }
        virtual void g(int x) { cout << "Derived::g(int)--" << x << endl; }
};

int main(int argc, char** argv)
{
        Base* pBase = NULL;
        Derived* pDerived = NULL;
        Base b;
        Derived d;
        pBase = &b;
        pDerived = &d;
        Base* pBD = &d;
        const Base* pC = &d;
        const Base* const pCCP = &d;
        Base* const pCP = &d;

        int x = 5;
        Other o;
        float f = 3.1415926;

        b.f();
        pBase->f();
        d.f();
        pDerived->f();
        pBD->f();

        b.g(x);
        b.g(o);
        d.g(x);
        d.g(f);
        // Can't be compiled!
        // d.g(o);

        pBD->g(x);
        pBD->g(f);
        pC->g(o);
        pCCP->g(o);
        pCP->g(o);

        return 0;
}
```

在笔者Ubuntu 12.04 + gcc 4.6.3运行结果：

```bash
Base::f()--20 //b.f()，通过对象调用，无虚特性，静态绑定
Base::f()--20 //基类指针指向基类对象，虽然是动态绑定，但没有使用到覆盖
Derived::f()--200 //d.f，通过对象调用，无虚特性，静态绑定
Derived::f()--200 //子类指针指向子类对象，虽然是动态绑定，但没有使用到覆盖
Derived::f()--20 //基类指针指向子类对象，动态绑定，子类f()覆盖基类版本。但函数参数默认值，是静态联编行为，pBD的类型是基类指针，所以使用了基类的参数默认值，注意此处！

Base::g(float)--5 //通过对象调用，int被提升为float
Base::g(Other&) //没什么问题，基类中三个g函数之间的关系是重载
Derived::g(int)--5 //没什么问题
Derived::g(int)--3 //注意基类的g(float)已经被隐藏！所以传入的float参数调用的却是子类的g(int)方法！

Base::g(float)--5 //注意！pBD是基类指针，虽然它指向了子类对象，但基类中的所有g函数版本它是可见的！所以pBD->g(5)调用到了g(float)！虽然产生了动态联编也发生了隐藏，但子类对象的虚表中，仍可以找到g(float)的地址，即基类版本！
Base::g(float)--3.14159 //原理同上

//d.g(o)
//注意此处！再注意代码中被注释了的一行，d.g(o)不能通过编译，因为d是子类对象，在子类中，基类中定义的三个g函数版本都被隐藏了，编译时不可见！不会重载

Base::g(Other&) const //pC是指向const对象的指针，将调用const版本的g函数
Base::g(Other&) const //pCCP是指向const对象的const指针，也调用const版本的g函数
Base::g(Other&) //pCP是指向非cosnt对象的const指针，由于不指向const对象，调用非const版本的g函数
```

上述结果，是否和预想的是否又有些出入呢？问题主要集中于结果的第5、12、13和15行。

第5行输出结果证明：**当函数参数有默认值，又发生多态行为时，函数参数默认值是静态行为，在编译时就已经确定，将使用基类版本的函数参数默认值而不是子类的**。

而第12、13、15行输出结果则说明，尽管已经证明我们之前说的隐藏是正确的（因为d.g(o)不可以通过编译，确实发生了隐藏），但却可以**利用基类指针指向派生类对象后，来绕开这种限制！**也就是说，编译器根据参数匹配函数原型的时候，是在编译时根据指针的类型，或对象的类型来确定，指针类型是基类，那么基类中的g函数版本就是可见的；指针类型是子类，由于发生了隐藏，基类中的g函数版本就是不可见的。而到动态绑定时，基类指针指向了子类对象，在子类对象的虚函数表中，就可以找到基类中g虚函数的地址。

写到这里，不知道读者是否已经明白，这些绕来绕去的关系。在实际代码运用中，可能并不会写出含有这么多“陷阱”的测试代码，我们只要弄清楚重载、覆盖和隐藏的具体特征，并头脑清醒地知道，我现在需要的是哪一种功能（通常也不会需要隐藏），就能写出清析的代码。上面的代码其实是一个糟糕的例子，因为在这个例子中，重载、覆盖、隐藏并存，我们编写代码，就是要尽可能防止这种含混不清的情况发生。

记住一个原则：**每一个方法，功能和职责尽可能单一，否则，尝试将它拆分成为多个方法**。
