---
title: Leetcode 522. Longest Uncommon Subsequence II
date: 2018-10-20 22:09:31
updated: 2018-10-20 22:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a list of strings, you need to find the longest uncommon subsequence among them. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be  **any**  subsequence of the other strings.

A  **subsequence**  is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

**Example 1:**  

> **Input:** "aba", "cdc", "eae"
> **Output:** 3

**Note:**

1. All the given strings' lengths will not exceed 10.
2. The length of the given list will be in the range of [2, 50].

<!--more-->

------------

# Analyze

<!-- TODO:Write some information about how to analyze this quesiton. -->

------------

# Solution

```cpp
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
      int res = -1, len = strs.size();
      int j = 0;
      // 1. Choose each one from the res
      for(int i =0; i < len; ++i) {
        for(j = 0; j < len; ++j) {
          if( i == j ) continue;
          if( isSubsequence(strs[i], strs[j]) ) break;
        }
        if (j == len) res = max(res, (int)strs[i].size());
      }
      return res;
    }
    bool isSubsequence(string s1, string s2) {
      int i = 0;
      for(char c : s2) {
        if ( c == s1[i] ) ++i;
        if ( i == s1.size() ) return true;
      } 
      return false;
    }
};
```