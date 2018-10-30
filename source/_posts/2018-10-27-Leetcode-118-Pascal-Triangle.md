---
title: Leetcode 118. Pascal's Triangle
date: 2018-10-27 06:09:31
updated: 2018-10-27 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a non-negative integer _numRows_, generate the first  _numRows_  of Pascal's triangle.

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

In Pascal's triangle, each number is the sum of the two numbers directly above it.

![](/images/in-post/2018-10-27-Leetcode-118-Pascal-Triangle/2018-10-27-23-25-15.png)

<!-- more -->

----------

# Solution

```cpp
class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res;
    res.reserve(numRows);
    if (numRows < 0) return res;
    for (int n = 0; n < numRows; ++n) {
      vector<int> row;
      row.reserve(n);
      for (int i = 0; i <= n; ++i) row.emplace_back(combine(n, i));
      res.emplace_back(row);
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