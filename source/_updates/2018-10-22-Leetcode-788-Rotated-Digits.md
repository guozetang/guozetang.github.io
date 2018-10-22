---
title: Leetcode 788. Rotated Digits
date: 2018-10-22 02:09:31
updated: 2018-10-22 02:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number  `N`, how many numbers X from  `1`  to  `N`  are good?

**Example:**
**Input:** 10
**Output:** 4
**Explanation:** 
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.

**Note:**

- N will be in range  `[1, 10000]`.

<!--more-->

-------

# Analyze

<!-- TODO: Add the info for this question. -->

--------

# Solution

```cpp
class Solution {
public:
    int rotatedDigits(int N) {
      int res = 0;
      for (int i = 0; i <= N; ++i) {
        if( isRotatedDigits(i) ) ++res;
      }
      return res;
    }
    bool isRotatedDigits(int number) {
      int digit = 0;
      bool good_flag = false;
      while(number) {
        digit = number % 10;
        if(number) number = number / 10; 
        if (digit == 3 || digit == 4 || digit == 7) return false;
        else if (digit == 0 || digit == 1 || digit == 8 ) continue;
        else {
          good_flag = true;
        }
      }
      return good_flag;
    }
};
```