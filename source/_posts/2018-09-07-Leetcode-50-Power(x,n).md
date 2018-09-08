---
title: Leetcode 50. Power(x,n)
date: 2018-09-07 09:50:32
updated: 2018-09-08 09:50:32
categories: Leetcode
tags: Leetcode
---

## Pow(x, n)
Implement  [pow(_x_,  _n_)](http://www.cplusplus.com/reference/valarray/pow/), which calculates _x_  raised to the power  _n_  (xn).

> **Example 1:**
> **Input:** 2.00000, 10
> **Output:** 1024.00000
> 
> **Example 2:**
> **Input:** 2.10000, 3
> **Output:** 9.26100
>
> **Example 3:**
> **Input:** 2.00000, -2
> **Output:** 0.25000
> **Explanation:** 2-2 = 1/22 = 1/4 = 0.25

**Note:**
- -100.0 <  _x_  < 100.0
- _n_  is a 32-bit signed integer, within the range [−231, 231 − 1]


**Difficulty**:Medium
**Category**:String
<!--more-->
****

# Solution

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if (n < 0) 
            return 1 / power(x, -n);
        return power(x, n);
    }

    double power(double x, int n) {
        if (n == 0)
            return 1;
        double half = power( x,  n/2);
        if (n%2 == 0)
            return half * half;
        else
            return x*half*half;       
    }
};
```