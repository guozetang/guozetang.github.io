---
title: Leetcode 647. Palindromic Substrings
date: 2018-10-25 14:09:31
updated: 2018-10-25 14:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

**Example 1:**  

**Input:** "abc"
**Output:** 3
**Explanation:** Three palindromic strings: "a", "b", "c".

**Example 2:**  

**Input:** "aaa"
**Output:** 6
**Explanation:** Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

**Note:**  

1. The input string length won't exceed 1000.

<!-- more -->

------------

# Solution

```cpp
class Solution {
 public:
  int countSubstrings(string s) {
    int len = s.size(), cnt = len;
    for (int left = 0; left < len; left++) {
      for (int val = 2; val <= len - left; val++) {
        if (isPalindromic(s.substr(left, val))) cnt++;
      }
    }
    return cnt;
  }

  bool isPalindromic(string s) {
    for (int left = 0, right = s.size() - 1; left < right; ++left) {
      if (left >= right) return true;
      if (s[left] != s[right]) return false;
      right--;
    }
    return true;
  }
};

```
