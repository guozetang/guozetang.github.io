---
title: Leetcode 60. Permutation Sequence
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

The set  `[1,2,3,...,_n_]`  contains a total of  _n_! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for  _n_  = 3:

1. `"123"`
2. `"132"`
3. `"213"`
4. `"231"`
5. `"312"`
6. `"321"`

Given  _n_  and  _k_, return the  _k_th  permutation sequence.

**Note:**

- Given  _n_  will be between 1 and 9 inclusive.
- Given _k_ will be between 1 and  _n_! inclusive.

**Example 1:**

> **Input:** n = 3, k = 3
> **Output:** "213"

**Example 2:**

> **Input:** n = 4, k = 9
> **Output:** "2314"

**Difficulty**:Medium
**Category**:Math, Backtracking  

<!-- more -->

------------

# Analyze

这到题是找到数字的排列中的第`k`个，我们在`Leetcode 31. Next Permutation` 这个题目是已经完成了求解给定排列的下一个排列的情况，所以这道题目，我们直接使用那道题目的函数来循环`k`次求解第k个排列就好了。

```cpp
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    unsigned len = nums.size() - 1;

    // Find an element from the right to left.
    for (int i = len - 1; i >= 0; --i) {
      if (nums[i + 1] > nums[i]) {
        for (int j = len; j > i; --j) {
          if (nums[j] > nums[i]) {
            swap(nums[j], nums[i]);
            reverse(nums.begin() + i + 1, nums.end());
            return;
          }
        }
      }
    }

    // If there are increate order from left to right.
    reverse(nums.begin(), nums.end());
    return;
  }
};
```

只需要在最后将结果转换为`string`返回即可。

------------

# Solution

```cpp
class Solution {
 public:
  string getPermutation(int n, int k) {
    vector<int> nums;
    for (int i = 0; i < n; ++i) nums.emplace_back(i + 1);
    for (int i = 1; i < k; ++i) {
      nextPermutation(nums);
    }
    string s(n, '0');
    for (int i = 0; i < n; ++i) s[i] += nums[i];
    return s;
  }

  void nextPermutation(vector<int>& nums) {
    unsigned len = nums.size() - 1;

    // Find an element from the right to left.
    for (int i = len - 1; i >= 0; --i) {
      if (nums[i + 1] > nums[i]) {
        for (int j = len; j > i; --j) {
          if (nums[j] > nums[i]) {
            swap(nums[j], nums[i]);
            reverse(nums.begin() + i + 1, nums.end());
            return;
          }
        }
      }
    }

    // If there are increate order from left to right.
    reverse(nums.begin(), nums.end());
    return;
  }
};
```

------------

# Leetcode Question Summary


------------
