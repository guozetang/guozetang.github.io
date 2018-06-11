---
title: Leetcode 7. Reverse Integer
date: 2018-06-10 08:30:32
categories: Leetcode
tags: Leetcode
---

Given a 32-bit signed integer, reverse digits of an integer.

> **Example 1:**
**Input:** 123
**Output:** 321

> **Example 2:**
**Input:** -123
**Output:** -321

> **Example 3:**
**Input:** 120
**Output:** 21

**Note:**  
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows
<!--more--->

## Analyze
数据翻转的问题, 只需要将`int`数据类型除以10的余数作为第一个数, 然后商继续除以10得到第二个数据. 处理过程为:
```cpp
            res = res * 10 + (x % 10);
            x = x / 10;
```
但是在本题目中, 需要考虑正负数, 然后数据是否超出范围(溢出)的情况. 此外, 需要考虑正负号的影响. 
- 溢出:　Int型的数值范围是 -2147483648～2147483647，那么如果我们要翻转 1000000009 这个在范围内的数得到 9000000001，而翻转后的数就超过了范围．

## Solution
```cpp
class Solution {
public:
    int reverse(int x) {
        long long res = 0;
        
        while(x != 0) {   
            res = res * 10 + (x % 10);
            x = x / 10;
        }
        if (res > INT_MAX || res < INT_MIN) return 0;
        return res;
    }
};
```
### Optimaze
最后两条语句可以合并之后书写:
`return (res > INT_MAX || res < INT_MIN)? 0 : res;`

判断是否溢出的时候, (参考Leetcode官方答案)可以简化为:
  `if (abs(res) > INT_MAX / 10) return 0;`
为什么可以不用检查INT_MIN, 解释过程可以参考[博客](http://www.cnblogs.com/grandyang/p/4125588.html)
> 在贴出答案的同时，OJ还提了一个问题 To check for overflow/underflow, we could check if ret > 214748364 or ret < –214748364 before multiplying by 10. On the other hand, we do not need to check if ret == 214748364, why? （214748364 即为 INT_MAX /  10）
>
>为什么不用check是否等于214748364呢，因为输入的x也是一个整型数，所以x的范围也应该在 -2147483648～2147483647 之间，那么x的第一位只能是1或者2，翻转之后res的最后一位只能是1或2，所以res只能是 2147483641 或 2147483642 都在int的范围内。但是它们对应的x为 1463847412 和 2463847412，后者超出了数值范围。所以当过程中res等于 214748364 时， 输入的x只能为 1463847412， 翻转后的结果为 2147483641，都在正确的范围内，所以不用check。

最后贴出官方给出的解答方法:
```cpp
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX / 10) return 0;
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};
```


