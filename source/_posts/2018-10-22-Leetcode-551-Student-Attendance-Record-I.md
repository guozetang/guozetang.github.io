---
title: Leetcode 551. Student Attendance Record I
date: 2018-10-22 15:09:31
updated: 2018-10-22 15:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

You are given a string representing an attendance record for a student. The record only contains the following three characters:

1. **'A'**  : Absent.
2. **'L'**  : Late.
3. **'P'**  : Present.

A student could be rewarded if his attendance record doesn't contain  **more than one 'A' (absent)**  or  **more than two continuous 'L' (late)**.

You need to return whether the student could be rewarded according to his attendance record.

**Example 1:**  

> **Input:** "PPALLP"
> **Output:** True

**Example 2:**  

> **Input:** "PPALLL"
> **Output:** False

<!--more--->

------------

# Solution

```cpp
class Solution {
public:
    bool checkRecord(string s) {
      int absent_nums = 0, late_con = 0;
      for(int i = 0; i < s.size(); ++i) {
        if (s[i] == 'A') {
          if(++absent_nums > 1) return false; 
          late_con = 0;
        }else if (s[i] == 'L'){
          if (++late_con > 2) return false;
        } else late_con = 0;
      }
      return true;
    }
};
```