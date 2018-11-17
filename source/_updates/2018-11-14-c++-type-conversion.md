---
title: C++类型转换方式分析
date: 2018-11-14 10:14:31
updated: 2018-11-14 12:14:31
categories: C++
tags: C++
---

# 前言

C++通过引进四个新的类型转换操作符克服了C风格类型转换中不清晰明了的缺点，这四个操作符是：

- static_cast: 在功能上基本上与C风格的类型转换一样强大，含义也一样。它也有功能上限制。比如，不能用static_cast象用C风格的类型转换一样把struct转换成int类型或者把double类型转换成指针类型，另外，static_cast不能从表达式中去除const属性。
- const_cast：用于类型转换掉表达式的`const或volatileness`属性。通过使用const_cast，你向人们和编译器强调你通过类型转换想做的只是改变一些东西的constness 或者 volatileness属性
- dynamic_cast：用于安全地沿着类的继承关系向下进行类型转换。这就是说，你能用dynamic_cast把指向基类的指针或引用转换成指向其派生类或其兄弟类的指针或引用，而且你能知道转换是否成功。失败的转换将返回空指针（当对指针进行类型转换时）或者抛出异常（当对引用进行类型转换时）。
- reinterpret_cast

在大多数情况下，对于这些操作符你只需要知道原来你习惯于这样写，`(type) expression`。而现在你总应该这样写： `static_cast(expression)`。