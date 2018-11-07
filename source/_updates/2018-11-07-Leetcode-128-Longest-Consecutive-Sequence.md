---
title: Leetcode 128. Longest Consecutive Sequence
date: 2018-11-07 06:09:31
updated: 2018-11-07 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Your algorithm should run in O(_n_) complexity.

**Example:**

> **Input:** [100, 4, 200, 1, 3, 2]
> **Output:** 4
> **Explanation:** The longest consecutive elements sequence is `[1, 2, 3, 4]`. Therefore its length is 4.

<!-- more -->

------------

# Solution

```cpp
// Use unordered_map to record which element have been used in the arrary.
class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_map<int, bool> used;
    for (int i : nums) used[i] = false;

    int longest = 0;
    for (auto n : nums) {
      // If this element have been used, then pass this element.
      if (used[n]) continue;
      int length = 1;

      used[n] = true;

      // Find the consecutive element at the right side of used[n]
      for (int i = n + 1; used.find(i) != used.end(); ++i) {
        used[i] = true;
        ++length;
      }

      // Find the consecutive element at the left side of used[n]
      for (int i = n - 1; used.find(i) != used.end(); --i) {
        used[i] = true;
        ++length;
      }

      longest = max(longest, length);
    }
    return longest;
  }
};
```