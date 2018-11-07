---
title: Leetcode 81. Search in Rotated Sorted Array II
date: 2018-11-07 06:09:31
updated: 2018-11-07 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  `[0,0,1,2,2,5,6]`  might become  `[2,5,6,0,0,1,2]`).

You are given a target value to search. If found in the array return  `true`, otherwise return  `false`.

**Example 1:**

> **Input:** nums = [2`,5,6,0,0,1,2]`, target = 0
> **Output:** true

**Example 2:**

> **Input:** nums = [2`,5,6,0,0,1,2]`, target = 3
> **Output:** false

**Follow up:**

- This is a follow up problem to [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), where  `nums`  may contain duplicates.
- Would this affect the run-time complexity? How and why?

<!-- more -->

----------

# Solution

```cpp
class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left != right) {
      const int mid = left + (right - left) / 2;
      if (nums[mid] == target) return true;
      if (nums[left] < nums[mid]) {
        if (nums[left] <= target && nums[mid] > target) {
          right = mid;
        } else {
          left = mid + 1;
        }
      } else if (nums[left] == nums[mid]) {
        left++;
      } else {
        if (nums[mid] < target && nums[right - 1] >= target) {
          left = mid + 1;
        } else {
          right = mid;
        }
      }
    }
    return false;
  }
};
```
