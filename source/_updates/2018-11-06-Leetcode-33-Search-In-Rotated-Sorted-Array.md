---
title: Leetcode 33. Search in Rotated Sorted Array
date: 2018-11-06 06:09:31
updated: 2018-11-06 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  `[0,1,2,4,5,6,7]`  might become  `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return  `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of _O_(log _n_).

**Example 1:**

> **Input:** nums = [`4,5,6,7,0,1,2]`, target = 0
> **Output:** 4

**Example 2:**

> **Input:** nums = [`4,5,6,7,0,1,2]`, target = 3
> **Output:** -1

<!-- more -->

----------

# Solution

```cpp
class Solution {
 public:
  // Binary Search
  int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left != right) {
      const int mid = left + (right - left) / 2;
      // Find the Target at the mid index.
      if (nums[mid] == target) return mid;
      if (nums[left] <= nums[mid]) {  // At the bigger part
        if (nums[left] <= target && nums[mid] >= target) {
          right = mid;
        } else
          left = mid + 1;
      } else {  // Include some smaller number.
        if (nums[mid] < target && nums[right - 1] >= target) {
          left = mid + 1;
        } else
          right = mid;
      }
    }
    return -1;
  }
};
```