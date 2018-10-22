---
title: Leetcode 696. Count Binary Substrings
date: 2018-10-22 02:09:31
updated: 2018-10-22 02:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Give a string  `s`, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

**Example 1:**  

> **Input:** "00110011"
> **Output:** 6
> **Explanation:** There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
> Notice that some of these substrings repeat and are counted the number of times they occur.
> Also, "00110011" is not a valid substring because **all** the 0's (and 1's) are not grouped together.

**Example 2:**  

> **Input:** "10101"
> **Output:** 4
> **Explanation:** There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.

**Note:**

- `s.length`  will be between 1 and 50,000.
- `s`  will only consist of "0" or "1" characters.

<!--more-->

-------

# Analyze

<!-- TODO: Add the info for this question. -->

--------

# Solution

```cpp
class Solution {
public:
    int countBinarySubstrings(string s) {
      int res = 0; 
      int pre = 0, cur = 1;
      for (int i = 1; i < s.size(); ++i) {
        if(s[i] == s[i-1]) ++cur;
        else {
          pre = cur;
          cur = 1;
        }
        if(pre >= cur) ++res;
      }
      return res;
    }
};
```