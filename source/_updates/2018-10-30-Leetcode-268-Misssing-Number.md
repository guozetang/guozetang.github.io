---
title: Leetcode 268. Missing Number
date: 2018-10-29 06:09:31
updated: 2018-10-29 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Quesiton

Given an array containing  _n_  distinct numbers taken from  `0, 1, 2, ..., n`, find the one that is missing from the array.

**Example 1:**

> **Input:** [3,0,1]
> **Output:** 2

**Example 2:**

> **Input:** [9,6,4,2,3,5,7,0,1]
> **Output:** 8

> **Note**:  Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

<!-- more -->

------------

# Solution

```cpp
class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    int sum = 0, len = nums.size();
    for (int i : nums) sum += i;
    return len * (len + 1) / 2 - sum;
  }
};
```