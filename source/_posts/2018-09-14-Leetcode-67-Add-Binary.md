---
title: Leetcode 67. Add Binary
date: 2018-09-14 14:09:31
updated: 2018-09-14 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given two binary strings, return their sum (also a binary string).
The input strings are both  **non-empty**  and contains only characters  `1`  or `0`.

**Example 1:**
> **Input:** a = "11", b = "1"
> **Output:** "100"

**Example 2:**
> **Input:** a = "1010", b = "1011"
> **Output:** "10101"

**Difficulty**:Easy
**Category**:  
<!--more-->
******

# Analyze

这道题目需要设置两个指针分别在指向两个`string`的最后一位，然后在设置一个标志位`carry`, 每次如果最低位的和大约`2`的话，就`carry = sum  / 2`得到需要进位的部分，继续指针左移，计算下一个，最后的时候，如果carry还没有为0, 那就在`string res`的前面加上`1`，就是`1 + res`。

******

# Solution

```cpp
class Solution {
public:
    string addBinary(string a, string b) {
        std::string res = "";
        int m = a.size() - 1, n = b.size() - 1;

        int carry = 0;
        while(m >= 0 || n >= 0) {
            int p = m >= 0 ? a[m--] - '0' : 0;
            int q = n >= 0 ? b[n--] - '0' : 0;

            int sum = p + q + carry;

            res = std::to_string(sum % 2) + res;
            carry = sum / 2;

            std::cout << res << std::endl;
        }
        return carry == 1 ? ('1' + res) : res;

    }
};
```