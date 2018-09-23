---
title: Leetcode 125. Valid palindrome
date: 2018-06-23 15:09:31
updated: 2018-06-23 15:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

**Example 1:**
> Input: "A man, a plan, a canal: Panama"
> Output: true

**Example 2:**
> Input: "race a car"
> Output: false

**Difficulty**:Easy
**Category**:

<!--more-->
******

# Analyze

******

# Solution

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size()-1;
        while(left < right){
            if(!isAlphaNum(s[left])) ++left;
            else if(!isAlphaNum(s[right])) --right;
            else if( (s[left] + 32 - 'a')%32 != (s[right] + 32 - 'a')%32 ) return false;
            else {
                ++left;
                --right;
            }
        }
        return true;
    }

    bool isAlphaNum(char &ch) {
        if (ch >= 'a' && ch <= 'z') return true;
        if (ch >= 'A' && ch <= 'Z') return true;
        if (ch >= '0' && ch <= '9') return true;
        return false;
    }
};
```