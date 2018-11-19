---
title: Leetcode 47. Permutations II
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

**Example:**

> **Input:** [1,1,2]
> **Output:**
> [
>  [1,1,2],
>  [1,2,1],
>  [2,1,1]
> ]

**Difficulty**:Medium
**Category**:Backtracking  

<!-- more -->

------------

# Analyze

这到题是找到数字的所有不重复排列，按照顺序排序，我们在`Leetcode 31. Next Permutation` 这个题目是已经完成了求解给定排列的下一个排列的情况，所以这道题目，我们直接使用那道题目的函数来循环求解就好,当出现要循环到最开始的时候，就停止。

------------

# Solution

```cpp
class Solution {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    bool done = false;
    unsigned res_size = 1;
    for (int i = 1; i <= nums.size(); ++i) {
      res_size *= i;
    }
    res.push_back(nums);
    for (int i = 1; i < res_size; ++i) {
      nextPermutation(nums, res, done);
      if (done) return res;
    }
    return res;
  }
  void nextPermutation(vector<int>& nums, vector<vector<int>>& res, bool& done) {
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
    done = true;
    return;
  }
};
```