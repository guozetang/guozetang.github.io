---
title: Leetcode 9. Palindrome Number
date: 2018-06-10 14:30:32
updated: 2018-06-10 14:30:32
categories: Leetcode
tags: Leetcode
---

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

**Example 1:**
> **Input:** 121
> **Output:** true

**Example 2:**
> **Input:** -121
> **Output:** false
> **Explanation:** From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

**Example 3:**
>**Input:** 10
>**Output:** false
>**Explanation:** Reads 01 from right to left. Therefore it is not a palindrome.

**Follow up:**
Could you solve it without converting the integer to a string?

**Difficulty**:Easy
**Category**:Math
<!--more-->
*****

# Analyze

验证回文数字, 直接对整数进行操作，我们可以利用取整和取余来获得我们想要的数字, 每计算一次, 去掉收尾各一个数字, 循环计算.

## Solution

```cpp
class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0) return false;

    int div = 1;
    while (x / div >= 10) div *= 10;

    while (x > 0) {
      int left = x / div;
      int right = x % 10;

      if (left != right) return false;
      x = (x % div) / 10;
      div /= 100;
    }
    return true;
  }
};
```

## Solution 2

```cpp
class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;

    int revertNum = 0;
    int cal_data = x;

    while (cal_data != 0) {
      revertNum = revertNum * 10 + cal_data % 10;
      cal_data /= 10;
    }

    return (revertNum == x) ? true : false;
  }
};
```
