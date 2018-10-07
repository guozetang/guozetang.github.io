---
title: C++之Rule of Zero
date: 2018-09-05 10:14:31
updated: 2018-09-05 12:14:31
categories: C++
tags: C++
---

<!-- TODO:理解Rule of Zero的真正含义 -->

Classes that have custom destructors, copy/move constructors or copy/move assignment operators should deal exclusively with ownership (which follows from the  [Single Responsibility Principle](https://en.wikipedia.org/wiki/Single_responsibility_principle "enwiki:Single responsibility principle")). Other classes should not have custom destructors, copy/move constructors or copy/move assignment operators.[[1]](https://en.cppreference.com/w/cpp/language/rule_of_three#cite_note-1)

```cpp
class rule_of_zero {
  std::string cppstring;

 public:
  rule_of_zero(const std::string& arg) : cppstring(arg) {}
};
```

When a base class is intended for polymorphic use, its destructor may have to be declared public and virtual. This blocks implicit moves (and deprecates implicit copies), and so the special member functions have to be declared as defaulted[[2]](https://en.cppreference.com/w/cpp/language/rule_of_three#cite_note-2)

```cpp
class base_of_five_defaults {
 public:
  base_of_five_defaults(const base_of_five_defaults&) = default;
  base_of_five_defaults(base_of_five_defaults&&) = default;
  base_of_five_defaults& operator=(const base_of_five_defaults&) = default;
  base_of_five_defaults& operator=(base_of_five_defaults&&) = default;
  virtual ~base_of_five_defaults() = default;
};
```

however, this can be avoided if the objects of the derived class are not dynamically allocated, or are dynamically allocated only to be stored in a  [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr "cpp/memory/shared ptr")  (such as by  [std::make_shared](https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared "cpp/memory/shared ptr/make shared")): shared pointers invoke the derived class destructor even after casting to  `std::shared_ptr<Base>`.
