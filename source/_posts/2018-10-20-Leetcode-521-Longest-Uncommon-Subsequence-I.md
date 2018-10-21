---
title: Leetcode 521. Longest Uncommon Subsequence I
date: 2018-10-20 20:09:31
updated: 2018-10-20 20:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be  **any**  subsequence of the other strings.

A  **subsequence**  is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be two strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

**Example 1:**  

> **Input:** "aba", "cdc"
> **Output:** 3
> **Explanation:** The longest uncommon subsequence is "aba" (or "cdc"), because "aba" is a subsequence of "aba", but not a subsequence of any other strings in the group of two strings.

**Note:**

1. Both strings' lengths will not exceed 100.
2. Only letters from a ~ z will appear in input strings.

<!--more-->

----------

# Analyze

There question is so easy. We just choose the longgest one as longest uncommon subsequence of  other strings in the group of two strings.

----------

# Solution

```cpp
class Solution {
public:
    int findLUSlength(string a, string b) {
      return a == b ? -1 : max(a.size(), b.size());
    }
};
```