---
title: Leetcode 541. Reverse String II
date: 2018-07-20 11:50:32
updated: 2018-06-18 11:50:32
categories: Leetcode
tags: Leetcode
---

## Reverse String II
Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.

> **Example:**  
> **Input:** s = "abcdefg", k = 2
> **Output:** "bacdfeg"
> **Restrictions:**
> 1. The string consists of lower English letters only.
> 2. Length of the given string and k will in the range [1, 10000]

**Difficulty**:Easy
**Category**:String
<!--more-->
*****

## Solution

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size(), count = n/2;
        for (int i = 0; i < count; ++i) {
            if(i % 2 == 0) {
                if (i*k + k < n) 
                    reverse(s.begin()+i*k, s.begin()+(i+1)*k);
                else
                    reverse(s.begin()+i*k, s.begin()+n);
            }
        }
        return s;
    }
};
```