---
title: Leetcode 73. Set Matrix Zeroes
date: 2018-11-19 20:09:31
updated: 2018-11-19 20:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a  _m_  x  _n_  matrix, if an element is 0, set its entire row and column to 0. Do it  [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm).

![](/images/in-post/2018-11-19-Leetcode-73-Set-Matrix-Zeroes/2018-11-19-20-40-14.png)

**Follow up:**

- A straight forward solution using O(_m__n_) space is probably a bad idea.
- A simple improvement uses O(_m_  +  _n_) space, but still not the best solution.
- Could you devise a constant space solution?

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
  void setZeroes(vector<vector<int>>& matrix) {
    const unsigned int len_r = matrix.size();
    const unsigned int len_c = matrix[0].size();

    bool done_r[len_r] = {false};
    bool done_c[len_c] = {false};

    // Check each row
    for (int i = 0; i < len_r; ++i) {
      for (int j = 0; j < len_c; ++j) {
        if (matrix[i][j] == 0) {
          done_c[j] = true;
          done_r[i] = true;
        }
      }
    }

    for (int i = 0; i < len_r; ++i) {
      if (done_r[i]) {
        for (int j = 0; j < len_c; ++j) {
          matrix[i][j] = 0;
        }
      }
    }

    for (int i = 0; i < len_c; ++i) {
      if (done_c[i]) {
        for (int j = 0; j < len_r; ++j) {
          matrix[j][i] = 0;
        }
      }
    }
    // Check each column
  }
};
```

------------

# Leetcode Question Summary


------------
