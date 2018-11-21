---
title: Leetcode 28. Implement strStr()
date: 2018-11-20 21:09:31
updated: 2018-11-20 21:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Implement  [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or  **-1**  if needle is not part of haystack.

**Example 1:**

> **Input:** haystack = "hello", needle = "ll"
> **Output:** 2

**Example 2:**

> **Input:** haystack = "aaaaa", needle = "bba"
> **Output:** -1

**Clarification:**

What should we return when  `needle`  is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when  `needle`  is an empty string. This is consistent to C's [strstr()](http://www.cplusplus.com/reference/cstring/strstr/)  and Java's [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)).

**Difficulty**:Easy
**Category**:String, Two Points

<!-- more -->

------------

# Analyze

------------

# Solution

```cpp
class Solution {
 public:
  int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    int len_m = haystack.size(), len_n = needle.size();
    if (len_m < len_n) return -1;
    for (int i = 0; i <= len_m - len_n; ++i) {
      int j = 0;
      for (j = 0; j < len_n; ++j) {
        if (haystack[i + j] != needle[j]) break;
      }
      if (j == len_n) return i;
    }
    return -1;
  }
};
```

------------

# Leetcode Question Summary


------------
