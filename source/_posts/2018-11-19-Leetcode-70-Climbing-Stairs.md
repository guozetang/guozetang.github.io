---
title: Leetcode 70. Climbing Stairs
date: 2018-11-19 17:09:31
updated: 2018-11-19 17:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

You are climbing a stair case. It takes  _n_  steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Note:**  Given  _n_  will be a positive integer.

**Example 1:**

> **Input:** 2
> **Output:** 2
> **Explanation:** There are two ways to climb to the top.
> 1. 1 step + 1 step
> 2. 2 steps

**Example 2:**

> **Input:** 3
> **Output:** 3
> **Explanation:** There are three ways to climb to the top.
> 1. 1 step + 1 step + 1 step
> 2. 1 step + 2 steps
> 3. 2 steps + 1 step

**Difficulty**:Easy
**Category**:Dynamic Programming

<!-- more -->

------------

# Analyze

假设`f(n)`表示爬到`n`阶阶梯，的不同方法数量，为了爬到第`n`阶阶梯，有两种情况：

- 从第`n-1`阶前进`1步`
- 从第`n-1`阶前进`2步`

所以这就可以得到：f(n) = f(n-1) + f(n-2)
这就是一个斐波那契数列，所以这一个题目相当于是求解第n个参数的数值。

方案二： 斐波那契数列的第`n`项计算公式为：

![](/images/in-post/2018-11-19-Leetcode-70-Climbing-Stairs/2018-11-19-18-19-42.png)

------------

# Solution

**Solution 1**

```cpp
class Solution {
 public:
  int climbStairs(int n) {
    int prev = 0;
    int cur = 1;
    for (int i = 1; i <= n; ++i) {
      int temp = cur;
      cur += prev;
      prev = temp;
    }
    return cur;
  }
};
```

**Solution 2**:使用公式直接计算

```cpp
class Solution {
 public:
  int climbStairs(int n) {
    const double s = sqrt(5);
    return floor((pow((1 + s) / 2, n + 1) + pow((1 - s) / 2, n + 1)) / s + 0.5);
  }
};
```
