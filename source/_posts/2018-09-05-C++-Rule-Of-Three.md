---
title: C++之Rule of Three
date: 2018-09-05 10:14:31
updated: 2018-09-05 12:14:31
categories: C++
tags: C++
---

If a class requires a user-defined  [destructor](https://en.cppreference.com/w/cpp/language/destructor "cpp/language/destructor"), a user-defined  [copy constructor](https://en.cppreference.com/w/cpp/language/copy_constructor "cpp/language/copy constructor"), or a user-defined  [copy assignment operator](https://en.cppreference.com/w/cpp/language/as_operator "cpp/language/as operator"), it almost certainly requires all three.

![](/images/in-post/2018-09-05-C++-Rule-Of-Three/2018-10-07-18-47-46.png)

<!--more-->

### Rule of three

C++中的Rule of Three指的是`析构函数`、`拷贝构造函数`和`重载赋值函数`三者之间的关系，具体指的是**在一个类当中当你需要显式地定义这三个函数中的任意一个时，你应该同时显式地定义其它两个**，也就是说这三个函数要么都不定义，要么都要定义。这一规则在C++标准中不是强制性的，但作为优秀的程序员，应谨记这一规则。因为你如果不定义其余两个的话，编i译器是会自动帮你生成的，但生成出来的很可能并不和你预期的是一致的。

> The implicitly-defined special member functions are typically incorrect if the class is managing a resource whose handle is an object of non-class type (raw pointer, POSIX file descriptor, etc), whose destructor does nothing and copy constructor/assignment operator performs a "shallow copy" (copy the value of the handle, without duplicating the underlying resource).

#### 如果不遵守这个规则

使用程序进行说明：

```cpp
class Rectangle {
  int m_width, m_height;

 public:
  Rectangle(int w = 0, int h = 0) : m_width(w), m_height(h) {}
};

void trectangle() {
  Rectangle first;
  Rectangle second(4, 3);
  Rectangle third(second);
  first = third;
}
```

这段代码写了一个简单的类，测试函数trectangle中演示了几种对象的构造方法，对象third的构造调用了拷贝构造函数，最后对first对象的赋值则调用了`重载赋值函数`。这里的情况是我们的类Rectangle既没有定义`析构函数，也没有定义拷贝构造和重载赋值函数`，编译器会为我们自动生成，自动生成的代码可能是这样子的：

```cpp
~Rectangle() {}
Rectangle(const Rectangle &other) {
  m_width = other.m_width;
  m_height = other.m_height;
}
Rectangle &operator=(const Rectangle &other) {
  m_width = other.m_width;
  m_height = other.m_height;
  return *this;
}

```

在这一个例子中，编译器自动生成的代码可以满足要求，所以这里我们不必显式地定义。下面我们继续看一个申请了内存的情况。我们定义了析构函数对内存资源进行释放，但是并没有定义`拷贝构造函数`以及`重载赋值函数`。

```cpp
class ByteArray {
  char *m_data;

 public:
  ByteArray() { m_data = new char[32]; }
  ByteArray(const char *data, int size) {
    m_data = new char[size];
    strncpy(m_data, data, size);
  }
  ~ByteArray() { delete[] m_data; }
  char *data() { return m_data; }
};

void tbytearray() {
  ByteArray first;
  ByteArray second("hello, world", 8);
  ByteArray third(second);
  first = third;
}

```

因为这个例子中申请了内存，所以我们需要显式地定义析构函数。这不是关键，关键在于此时测试函数tbytearray中third对象的构造和对first对象的赋值，它们分别调用拷贝构造函数和重载赋值函数，因为没有显式地定义，编译器将帮我们生成，而生成的代码将会是这样子的：

```cpp
ByteArray(const ByteArray &other) { m_data = other.m_data; }
ByteArray &operator=(const ByteArray &other) {
  m_data = other.m_data;
  return *this;
}
```

这里很明显将出现问题，编译器生成的代码只是简单的做值的拷贝，而对于指针，不能这样简单的赋值，这种简单赋值也称为浅拷贝，我们要做的是深拷贝，即要将指针所指的内容拷过去，并且新的对象要重新申请内存，不然将有两个对象引用同一块内存区，在析构时同一块内存区将被释放两次，这是不允许的，所以我们要自己实现拷贝构造和重载赋值函数。这就是我们需要遵守rule of three的原因。不能在该使用深拷贝的时候不小心使用到了浅拷贝。

#### 遵守规则3的完整例子

下面给出来一个老师上课时候给的完整的`Rule of three`的实现例子。

```cpp
#include <cstring>
#include <iostream>

class string {
 public:
  string() : buf(new char[1]) { buf[0] = '\0'; }
  string(const char* s) : buf(new char[strlen(s) + 1]) { strcpy(buf, s); }
  string(const string& s) : buf(new char[strlen(s.buf) + 1]) {
    strcpy(buf, s.buf);
  }
  ~string() { delete[] buf; }

  const char* getBuf() const { return buf; }

  string& operator=(const string& rhs) {
    if (this == &rhs) return *this;
    delete[] buf;
    buf = new char[strlen(rhs.buf) + 1];
    strcpy(buf, rhs.buf);
    return *this;
  }

 private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

int main() {
  string cat("cat"), dog(cat);
  dog = cat;
  std::cout << cat << std::endl;
}
```

以及来自于[cppreference网站](https://en.cppreference.com/w/cpp/language/rule_of_three)的例子：

```cpp
class rule_of_three {
  char* cstring;  // raw pointer used as a handle to a dynamically-allocated
                  // memory block
  rule_of_three(const char* s, std::size_t n)  // to avoid counting twice
      : cstring(new char[n])                   // allocate
  {
    std::memcpy(cstring, s, n);  // populate
  }

 public:
  rule_of_three(const char* s = "") : rule_of_three(s, std::strlen(s) + 1) {}
  ~rule_of_three() {
    delete[] cstring;  // deallocate
  }
  rule_of_three(const rule_of_three& other)  // copy constructor
      : rule_of_three(other.cstring) {}
  rule_of_three& operator=(rule_of_three other)  // copy assignment
  {
    std::swap(cstring, other.cstring);
    return *this;
  }
};
```