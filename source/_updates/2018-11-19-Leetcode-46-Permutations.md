---
title: Leetcode 46. Permutations
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a collection of  **distinct**  integers, return all possible permutations.

**Example:**

> **Input:** [1,2,3]
> **Output:**
> [
>  [1,2,3],
>  [1,3,2],
>  [2,1,3],
>  [2,3,1],
>  [3,1,2],
>  [3,2,1]
> ]

**Difficulty**:Medium
**Category**:Backtracking  

<!-- more -->

------------

# Analyze

这到题是找到数字的所有排列，按照顺序排序，我们在`Leetcode 31. Next Permutation` 这个题目是已经完成了求解给定排列的下一个排列的情况，所以这道题目，我们直接使用那道题目的函数来循环`n!`次求解就好。

------------

# Solution

```cpp
class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    unsigned len = nums.size(), res_size = 1;
    for (int i = 1; i <= len; ++i) {
      res_size *= i;
    }
    res.push_back(nums);
    for (int i = 1; i < res_size; ++i) {
      nextPermutation(nums, res);
    }
    return res;
  }
  void nextPermutation(vector<int>& nums, vector<vector<int>>& res) {
    unsigned len = nums.size() - 1;

    // Find an element from the right to left.
    for (int i = len - 1; i >= 0; --i) {
      if (nums[i + 1] > nums[i]) {
        for (int j = len; j > i; --j) {
          if (nums[j] > nums[i]) {
            swap(nums[j], nums[i]);
            reverse(nums.begin() + i + 1, nums.end());
            res.push_back(nums);
            return;
          }
        }
      }
    }

    // If there are increate order from left to right.
    reverse(nums.begin(), nums.end());
    res.push_back(nums);
    return;
  }
};
```