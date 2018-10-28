---
title: Leetcode 859. Buddy Strings
date: 2018-10-24 19:09:31
updated: 2018-10-24 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given two strings  `A`  and  `B` of lowercase letters, return  `true`  if and only if we can swap two letters in  `A`  so that the result equals  `B`.

**Example 1:**

> **Input:** A = "ab", B = "ba"
> **Output:** true

**Example 2:**

> **Input:** A = "ab", B = "ab"
> **Output:** false

**Example 3:**

> **Input:** A = "aa", B = "aa"
> **Output:** true

**Example 4:**

> **Input:** A = "aaaaaaabc", B = "aaaaaaacb"
> **Output:** true

**Example 5:**

> **Input:** A = "", B = "aa"
> **Output:** false

**Note:**

1. `0 <= A.length <= 20000`
2. `0 <= B.length <= 20000`
3. `A`  and `B`  consist only of lowercase letters.

<!--more-->

----------

# Solution

```cpp
class Solution {
 public:
  bool buddyStrings(string A, string B) {
    int diff_num = 0;
    if (A.size() != B.size()) return false;
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] != B[i]) diff_num++;
      if (diff_num > 2) return false;
    }

    if (diff_num == 1)
      return false;

    else if (diff_num == 2) {
      sort(A.begin(), A.end());
      sort(B.begin(), B.end());
      if (A == B) return true;
    }

    else {
      if (A.size() > 256) return true;
      bool result[256] = {false};
      for (size_t i = 0; i < A.size(); ++i) {
        if (result[A[i]])
          return true;
        else
          result[A[i]] = true;
      }
    }
    return false;
  }
};
```