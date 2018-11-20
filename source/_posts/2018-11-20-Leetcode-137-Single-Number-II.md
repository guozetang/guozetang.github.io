---
title: Leetcode 137. Single Number II
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a  **non-empty** array of integers, every element appears  _three_  times except for one, which appears exactly once. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

>**Input:** [2,2,3,2]
**Output:** 3

**Example 2:**

>**Input:** [0,1,0,1,0,1,99]
**Output:** 99

**Difficulty**:Medium
**Category**:Bit Manipulation  

<!-- more -->

------------

# Analyze

------------

# Solution

```cpp
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    const int len_int = sizeof(int) * 8;
    int count[len_int];
    fill_n(&count[0], len_int, 0);

    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < len_int; ++j) {
        count[j] += (nums[i] >> j) & 1;
      }
    }
    for (int i = 0; i < len_int; ++i) {
      res += ((count[i] % 3) << i);
    }
    return res;
  }
};
```
