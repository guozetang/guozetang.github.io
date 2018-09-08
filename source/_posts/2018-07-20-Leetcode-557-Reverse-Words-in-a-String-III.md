---
title: Leetcode 557. Reverse String II
date: 2018-07-20 09:50:32
updated: 2018-09-08 09:50:32
categories: Leetcode
tags: Leetcode
---

## Reverse Words in a String III

Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

**Example 1:**  

**Input:** "Let's take LeetCode contest"
**Output:** "s'teL ekat edoCteeL tsetnoc"

**Note:**  In the string, each word is separated by single space and there will not be any extra space in the string.


<!--more-->
****

## Solution

```cpp
class Solution {
public:
    string reverseWords(string s) {
        if (s.size() == 0) return s;
        for (int left = 0, right = 0; right <= s.size()-1; right++){
            if(right == s.size() - 1) reverse(s.begin()+left, s.end());
            if(s[right] == ' ') {
                reverse(s.begin()+left, s.begin()+right);
                left = right + 1;
            }
        }
        return s;
    }
};
```