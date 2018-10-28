---
title: Leetcode 119. Pascal's Triangle II
date: 2018-10-27 06:09:31
updated: 2018-10-27 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a non-negative index  _k_ where  _k_  ≤ 33, return the  _k_th index row of the Pascal's triangle.

Note that the row index starts from 0.

![](/images/in-post/2018-10-27-Leetcode-119-Pascal-Triangle-II/2018-10-27-23-01-55.gif)

In Pascal's triangle, each number is the sum of the two numbers directly above it.

**Example:**

> **Input:** 3
> **Output:** [1,3,3,1]
> **Follow up:**
> Could you optimize your algorithm to use only  _O_(_k_) extra space?

<!-- more -->

---------

# Solution

```cpp
// a[i][j] = a[i][0] * (i/1) * ((i-1)/2)) * ((i-2)/3) * ... * (1/i)。
class Solution {
 public:
  vector<int> getRow(int rowIndex) {
    vector<int> res;
    res.reserve(33);
    if (rowIndex < 0) return res;

    for (int i = 0; i <= rowIndex; ++i) {
      if (i == 0 || i == rowIndex)
        res.emplace_back(1);
      else {
        res.emplace_back(combine(rowIndex, i));
      }
    }
    return res;
  }

  long combine(int n, int c) {
    int i;
    long p = 1;
    for (i = 1; i <= c; i++) {
      p = p * (n - i + 1) / i;
    }
    return p;
  }
};
```