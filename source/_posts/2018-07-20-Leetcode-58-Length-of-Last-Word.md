---
title: Leetcode 58. Length of Last Word
date: 2018-07-20 11:50:32
updated: 2018-09-07 11:50:32
categories: Leetcode
tags: Leetcode
notshow: true
---

# Question

Given a string  _s_  consists of upper/lower-case alphabets and empty space characters  `' '`, return the length of last word in the string.

If the last word does not exist, return 0.

> **Note:**  A word is defined as a character sequence consists of non-space characters only.
> **Example:**
> **Input:** "Hello World"
> **Output:** 5

<!--more-->
*****

# Solution

```cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
        int right = 0, flag_right =0;
        if (s.size() == 0) return 0;
        for (int i = s.size() -1; i >= 0; --i) {
            if (flag_right == 1 && s[i] == ' ') {
                return right - i;
            }
            else {
                if (s[i] != ' ' && flag_right == 0) {
                    flag_right = 1;
                    right = i;
                }
            }
        }
        if (flag_right == 0)
            return 0;
        else
            return right+1;
    }
};
```