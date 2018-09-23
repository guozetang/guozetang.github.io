---
title: Leetcode 344. Reverse-String
date: 2018-06-22 15:09:31
updated: 2018-06-22 15:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Write a function that takes a string as input and returns the string reversed.

**Example 1:**

> Input: "hello"
> Output: "olleh"

**Example 2:**
> Input: "A man, a plan, a canal: Panama"
> Output: "amanaP :lanac a ,nalp a ,nam A"

**Difficulty**:Easy
**Category**:

<!--more-->
******

# Analyze

这道题目是关于`String`操作，很简单的一道题目，只需要两个找到字母，然后交换就好了。
******

# Solution

```cpp
class Solution {
public:
    string reverseString(string s) {
        for(int left = 0, right = s.size() - 1; left < right; ++left) {
            swap(s[left], s[right]);
            right--;
        }
        return s;
    }
};
```

# Similar Question

[Leetcode-345-Reverse-Vowels-of-a-String](../Leetcode-345-Reverse-Vowels-of-a-String/)