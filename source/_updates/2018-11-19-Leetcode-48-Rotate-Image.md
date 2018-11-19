---
title: Leetcode 48. Rotate Image
date: 2018-11-19 19:09:31
updated: 2018-11-19 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

You are given an  _n_  x  _n_  2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

**Note:**

You have to rotate the image  [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm), which means you have to modify the input 2D matrix directly.  **DO NOT**  allocate another 2D matrix and do the rotation.

![](/images/in-post/2018-11-19-Leetcode-48-Rotate-Image/2018-11-19-17-05-13.png)

**Difficulty**:Medium
**Category**:Array  

<!-- more -->

------------

# Analyze

------------

# Solution

```cpp
class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    const unsigned int n = matrix.size();

    // 1. 沿着对角线翻转一次
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n - i; ++j) {
        swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
      }
    }

    // 2. 沿着水平中间线翻转一次
    for (int i = 0; i < n / 2; ++i) {
      for (int j = 0; j < n; ++j) {
        swap(matrix[i][j], matrix[n - 1 - i][j]);
      }
    }
  }
};
```