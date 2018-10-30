---
title: Leetcode 59. Spiral Matrix II
date: 2018-10-27 16:09:31
updated: 2018-10-27 16:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question


Given a positive integer  _n_, generate a square matrix filled with elements from 1 to  _n_2  in spiral order.

**Example:**

> **Input:** 3
> **Output:**
> [
>  [ 1, 2, 3 ],
>  [ 8, 9, 4 ],
>  [ 7, 6, 5 ]
>]

<!-- more -->

----------

# Solution

```cpp
class Solution {
 public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    int val = 1, c = (n + 1) / 2, p = n;

    for (int i = 0; i < c; ++i, p -= 2) {
      // Convert Up side
      for (int row_up = i; row_up <= i + p - 1; ++row_up) {
        res[i][row_up] = val++;
      }

      // Right side
      for (int row_right = i + 1; row_right <= i + p - 1; ++row_right) {
        res[row_right][i + p - 1] = val++;
      }

      // Bottom side
      for (int row_bottom = n - i - 2; row_bottom >= i; --row_bottom) {
        res[i + p - 1][row_bottom] = val++;
      }

      // Left side
      for (int row_left = n - i - 2; row_left > i; --row_left) {
        res[row_left][i] = val++;
      }
    }
    return res;
  }
};
```