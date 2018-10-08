---
title: 编译原理课程学习目录(CU CPSC8270)
date: 2018-10-05 13:04:27
updated: 2018-10-05 13:04:27
categories: Translation of Programming Languages
tags: C++, Translation, Flex, Bision
---

![](/images/in-post/2018-10-04-Translation-of-Programming-Languages-index/2018-10-07-18-16-06.png)

编译原理这门课程是我在CU的2018 Fall选修的一门专业核心课程，老师是Clemson CS系比较受欢迎的[Brian Malloy教授](https://people.cs.clemson.edu/~malloy/)。在他的个人主页上面也有Python, C++， 2D游戏的教程，非常适合对CS感兴趣的同学学习。

<!--more-->
---

# 课程内容

### Week1

**Aug 28, Tue**
- Read Section 1, the Introduction, to grammarware paper
- Discuss slides about Grammars
- Answer questions about Basics and Classes
- Do the Rule of 3

本周的重点内容是`C++的基本语法以及Classes的使用` 和 `C++ Rule of 3`的规则应用。在这里分别整理了两个部分的博客文章：

- [C++ Rule of 3](/post/C++-Rule-Of-Three/)

<!-- TODO:完成关于Basics and Classes的内容 -->

**Aug 30, Thu**
- Regular grammars and regular expressions
- Review Rule of 3
- What gets called
- The Rule of 5
- The Rule of Zero

<!-- TODO:Post: Rule of 5
TODO:Post: Rule of Zero
TODO:Post: what get called.
TODO:Regular expressions -->

## Week2

**Sep 4, Tue**
- What gets called
  - Why prefer init over assign?!
- Introduce vectors
  - size vs capacity
  - value semantics
- Intro to Flex
- Project #2
- Quiz #1 -- Thursday

## Week3

**Sep 13, Thu**
- Questions about move semantics?
  - Well I have one?
- flex:
  - ambiguity:
  - codes
  - first
  - wc
  - states
  - line numbers: lineno
  - debug mode
- static varsux
- Singleton Pattern (单例设计模式)

理解为什么要使用 Singleton设计模式，已详细分析了为什么要使用singleton模式，以及Singleton设计模式的好处和如何来书写Singleton. 请参考博客:

- [C++软件设计模式之Singleton](/post/C++Singleton-pattern/)

## Week4

**Sep 20, Thu**
- The Bison Parser Generator: shift/reduce parsing LALR(1)
- Balanced Parens -- adding sets of them
- sum -- adding numbers

## Week 5

**Sep 25, Tue**
- conflicts -- the pointer model
  - Inserting semantic actions:
  - simple -- no actions but prec set
  - noPrec -- grammar refactored, no prec set
  - calc -- calculator example -- no variables
  - typedStack -- calculator w/ variables
- Project #3
- Exam #1 -- everything up to and incl today

**Sep 27. Thu**
- Exam #1 -- everything up to and incl today

## Week 6

**Oct 2. Tue**
- Containers
  - vectors
  - List
  - Map
- Review Exam
  - Singleton
  - Exponent
  - Radon
- Inheritance

**Oct 4. Thu**
- emplace_back -- When it help?

# 项目内容

## 项目