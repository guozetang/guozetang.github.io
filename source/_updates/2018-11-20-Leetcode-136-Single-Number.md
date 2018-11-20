---
title: Leetcode 136. Single Number
date: 2018-11-20 06:09:31
updated: 2018-11-20 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a  **non-empty** array of integers, every element appears  _twice_  except for one. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

>**Input:** [2,2,1]
**Output:** 1

**Example 2:**

>**Input:** [4,1,2,1,2]
**Output:** 4

**Difficulty**:Medium
**Category**:HashTable, BitManipulation

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

    for (auto i : nums) res ^= i;
    return res;
  }
};
```

------------

# Leetcode Question Summary


------------
