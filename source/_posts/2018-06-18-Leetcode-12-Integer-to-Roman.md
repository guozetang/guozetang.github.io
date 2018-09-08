---
title: Leetcode 12. Integer to Roman
date: 2018-06-18 10:30:32
updated: 2018-06-18 10:30:32
categories: Leetcode
tags: Leetcode
---

﻿Roman numerals are represented by seven different symbols: `I`,  `V`,  `X`,  `L`,  `C`,  `D`  and  `M`.

**Symbol**       **Value**
>I             1
V             5
X             10
L             50
C             100
D             500
M             1000
<!--more-->
For example, two is written as  `II` in Roman numeral, just two one's added together. Twelve is written as,  `XII`, which is simply  `X`  +  `II`. The number twenty seven is written as  `XXVII`, which is  `XX`  +  `V`  +  `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not  `IIII`. Instead, the number four is written as  `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as  `IX`. There are six instances where subtraction is used:

-   `I`  can be placed before  `V`  (5) and  `X`  (10) to make 4 and 9.
-   `X`  can be placed before  `L`  (50) and  `C`  (100) to make 40 and 90.
-   `C`  can be placed before  `D`  (500) and  `M`  (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

**Example 1:**
>**Input:** 3
**Output:** "III"

**Example 2:**
>**Input:** 4
**Output:** "IV"

**Example 3:**
>**Input:** 9
**Output:** "IX"

**Example 4:**
>**Input:** 58
**Output:** "LVIII"
**Explanation:** C = 100, L = 50, XXX = 30 and III = 3.

**Example 5:**

>**Input:** 1994
**Output:** "MCMXCIV"
**Explanation:** M = 1000, CM = 900, XC = 90 and IV = 4.

**Difficulty**:Medium
**Category**:  
<!--more-->
*****

## Analyze
之前那篇文章写的是罗马数字转化成整数([http://www.cnblogs.com/grandyang/p/4120857.html](http://www.cnblogs.com/grandyang/p/4120857.html))， 这次变成了整数转化成罗马数字，基本算法还是一样。由于题目中限定了输入数字的范围(1 - 3999), 使得题目变得简单了不少。

例如整数 1437 的罗马数字为 MCDXXXVII， 我们不难发现，千位，百位，十位和个位上的数分别用罗马数字表示了。 1000 - M, 400 - CD, 30 - XXX, 7 - VII。所以我们要做的就是用取商法分别提取各个位上的数字，然后分别表示出来：

100 - C

200 - CC

300 - CCC

400 - CD

500 - D

600 - DC

700 - DCC

800 - DCCC

900 - CM

我们可以分为四类，100到300一类，400一类，500到800一类，900最后一类。每一位上的情况都是类似的，代码如下：
## Solution
```cpp
class Solution {
public:
    string intToRoman(int num) {
        string res = "";
        char roman[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
        int integer[] = {1000, 500, 100, 50, 10, 5, 1};

        for(int i = 0; i < 7; i += 2){
            int val = num / integer[i]; 
            if(val < 4) {
                for (int j = 1; j <= val; ++j ) res += roman[i];
            } else if (val == 4) {
                res = res + roman[i] + roman[i-1];
            } else if (val > 4 && val < 9) {
                res += roman[i - 1];
                for(int j = 6; j <= val; ++j) res += roman[i];
            } else if (val == 9) { 
                res = res + roman[i] + roman[i-2];
            }
            num = num % integer[i];
        }
        return res;
        
    }
};
```
