---
title: Leetcode 459. Repeated Substring Pattern
date: 2018-10-06 14:09:31
updated: 2018-10-06 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

**Example 1:**
> **Input:** "abab"
> **Output:** True
> **Explanation:** It's the substring "ab" twice.

**Example 2:**
> **Input:** "aba"
> **Output:** False

**Example 3:**
> **Input:** "abcabcabcabc"
> **Output:** True
> **Explanation:** It's the substring "abc" four times. (And the substring "abcabc" twice.)

<!--more-->

---

# Analyze

给定一个字符串，问其是否有`n个重复的子串组成`。如果字符串的长度是`len`，那么我们在`0-n/2`之间进行判断，是否是字符串。

- 如果子字符串的长度不能被len整除，那么这肯定不是可以重复N次组建成给定字符串的子字符串
- 如果能够被字符串长度len整除，那么就使用整除得到的数值n，进行n次子字符串重复，重复完成之后，判断是否和输入的字符串相等， 如果相等，那就返回true，如果不相等，那就是false

---

# Solution

```cpp
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
      int len = s.size();
      for(int i = 0; i < len/2; ++i) {
        if(len % (i+1) == 0) {
          int count = len / (i+1);
          string res = "";
          for(int j = 0; j < count; ++j) {
            res += s.substr(0, i+1);
          }
          if(res == s) return true;
        }
      }
      return false;
    }
};
```