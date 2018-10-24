---
title: Leetcode 537. Complex Number Multiplication
date: 2018-10-24 19:09:31
updated: 2018-10-24 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given two strings representing two  [complex numbers](https://en.wikipedia.org/wiki/Complex_number).

You need to return a string representing their multiplication. Note i2  = -1 according to the definition.

**Example 1:**  

> **Input:** "1+1i", "1+1i"
> **Output:** "0+2i"
> **Explanation:** (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.

**Example 2:**  

> **Input:** "1+-1i", "1+-1i"
> **Output:** "0+-2i"
> **Explanation:** (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.

**Note:**

1. The input strings will not have extra blank.
2. The input strings will be given in the form of  **a+bi**, where the integer  **a**  and  **b**  will both belong to the range of [-100, 100]. And  **the output should be also in this form**.

<!--more-->

-----------

# Solution

```cpp
class Solution {
 public:
  string complexNumberMultiply(string a, string b) {
    std::string res;
    int a1, a2, b1, b2, r1, r2;
    int len_a = a.size(), len_b = b.size();
    auto p1 = a.find_last_of("+"), p2 = b.find_last_of("+");
    a1 = stoi(a.substr(0, p1));
    b1 = stoi(b.substr(0, p2));

    a2 = stoi(a.substr(p1 + 1, len_a - p1 - 1));
    b2 = stoi(b.substr(p2 + 1, len_b - p2 - 1));

    r1 = a1 * b1 - a2 * b2;
    r2 = a1 * b2 + a2 * b1;
    res = to_string(r1) + "+" + to_string(r2) + "i";

    return res;
  }
};
```