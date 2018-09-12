---
title: Book. Effective C++ item1-View C++ as a federatime of languages
date: 2018-09-11 02:09:31
updated: 2018-09-11 02:09:31
categories: EffectiveC++
tags: EffectiveC++
top:
---

# View C++ as a federation of Languages

In the begining, C++ was just C with some object-oriented features tacked on. `c++ = C with classes`. 但是到了后来，C++就包含了很多复杂的事物，我们在使用C++的时候可以将其看成四种不同的使用方式。

<!--more-->

- C语言。 按照C语言的规则去使用，没有模板，没有异常，没有重载
- Object-Oriented C+。这一部分是C with CLasses所追求的，classes, encapsulation, inheritance, polymorphism, virtual。按照面向对象的设计准则去做就好了
- Template C++. 泛型编程
- STL。STL是一个template程序库，对containers, iterators, algorithms 和 Function objects进行了限制。如果在编程中使用了STL, 那就必须遵守STL的规则

当你使用到其中的几种方式的时候，要习惯对自己的编程方式进行更换