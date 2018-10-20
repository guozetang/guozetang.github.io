---
title: Leetcode 709. To Lower Case
date: 2018-10-20 14:09:31
updated: 2018-10-20 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.

**Example 1:**

> **Input:** "Hello"
> **Output:** "hello"

**Example 2:**

> **Input:** "here"
> **Output:** "here"

**Example 3:**

> **Input:** "LOVELY"
> **Output:** "lovely"

<!--more-->

---

# Analyze

This question is so easy. There is a formula for converting the capital letter to the lowercase.

![](/images/in-post/2018-10-20-Leetcode-709-To-Lower-Case/2018-10-20-15-39-18.png)

The capital letter ASCII code is between `[65-90]`. And the lowercase is between `[97-122]`, and the `a = A + 32`. As a result, when we find a capital letter, then just `str[i] + 32`.

---

# Solution

```cpp
class Solution {
public:
    string toLowerCase(string str) {
      int len = str.size();
      for (int i = 0; i < len; ++i) {
        if (str[i] >=65 && str[i] <= 90) {
          str[i] += 32;
        }
      }
      return str;
    }
};
```