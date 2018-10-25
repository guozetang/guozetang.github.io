---
title: C++ vector push_back() Vs emplace_back
date: 2018-10-23 02:09:31
updated: 2018-09-23 02:09:31
categories: C++
tags: C++
top:
---

# Introduce

## std::vector::push_back()

Appends the given element value to the end of the container.

- The new element is initialized as a copy of value.
- value is moved into the new element.

If the new `size()` is greater than `capacity()` then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated. (Cite from: [cppreference.com](https://en.cppreference.com/w/cpp/container/vector/push_back))

<!--more-->

-------

### Example

Firstly, if we have a class `String`, then we can use this class to test the `push_back()` functions.

```cpp
#include <iostream>
#include <cstring>
#include <vector>
class string {
 public:
  string() : buf(new char[1]) {
    std::cout << "default" << std::endl;
    buf[0] = '\0';
  }
  string(const char* s) : buf(new char[strlen(s) + 1]) {
    std::cout << "convert" << std::endl;
    strcpy(buf, s);
  }
  explicit string(const string& s) : buf(new char[strlen(s.buf) + 1]) {
    std::cout << "copy" << std::endl;
    strcpy(buf, s.buf);
  }
  ~string() {
    std::cout << "destructor" << std::endl;
    delete[] buf;
  }

  string& operator=(const string& rhs) {
    std::cout << "copy assign" << std::endl;
    if (this == &rhs) return *this;
    delete[] buf;
    buf = new char[strlen(rhs.buf) + 1];
    strcpy(buf, rhs.buf);
    return *this;
  }

  const char* getBuf() const { return buf; }

 private:
  char* buf;
};

std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}
```

**Understand:**

- The new element is initialized as a copy of value.
- value is moved into the new element.

```cpp
int main() {
  std::vector<string> vec;
  vec.push_back("test");
  vec.push_back("test2");
}
```

Output:

```bash
convert // Covert "test" to class string
copy    // Copy string(test) to vector
destructor
convert // Covert "test2" to class string
copy    // Size() > capacity(), then apply for a new memory, and copy "test" to new vector.
copy    // Copy string(test2) to vector
destructor
destructor
destructor
destructor
```

In the case, I used this example to test how to initialize a new element in the vector. Like this case, when we new an object, we copy this object into vector. After that, we can delete this object.

- Convert a new string object 1
- Copy the string object 1 to the string object 2, and move string object 2 into the new element.
- Delete the string object 1

-----------

## std::vector::emplace_back (Since C++ 11)

Appends a new element to the end of the container. The element is constructed through std::allocator_traits::construct, which typically uses placement-new to construct the element in-place at the location provided by the container. The arguments args... are forwarded to the constructor as std::forward<Args>(args)....

If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated.

### Example

```cpp
int main() {
  std::vector<string> vec;
  vec.emplace_back("TEST");
  vec.emplace_back("TES3");
}
```

**Output:**

```bash
convert
convert
copy  // Copy the first one from the old vector memory to the new memory
destructor
destructor
destructor
```
