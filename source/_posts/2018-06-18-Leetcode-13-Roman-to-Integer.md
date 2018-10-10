---
title: Leetcode 13. Roman to Integer
date: 2018-06-18 10:50:32
updated: 2018-06-18 10:50:32
categories: Leetcode
tags: Leetcode
notshow: true
---

﻿Roman numerals are represented by seven different symbols: `I`,  `V`,  `X`,  `L`,  `C`,  `D`  and  `M`.

>**Symbol**       **Value**
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as  `II` in Roman numeral, just two one's added together. Twelve is written as,  `XII`, which is simply  `X`  +  `II`. The number twenty seven is written as  `XXVII`, which is  `XX`  +  `V`  +  `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not  `IIII`. Instead, the number four is written as  `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as  `IX`. There are six instances where subtraction is used:

- `I`  can be placed before  `V`  (5) and  `X`  (10) to make 4 and 9.
- `X`  can be placed before  `L`  (50) and  `C`  (100) to make 40 and 90.
- `C`  can be placed before  `D`  (500) and  `M`  (1000) to make 400 and 900.

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

**Difficulty**:Easy
**Category**:  
<!--more-->
*****

# Analyze
  
我们需要用到map数据结构，来将罗马数字的字母转化为对应的整数值，因为输入的一定是罗马数字，那么我们只要考虑两种情况即可：
第一，如果当前数字是最后一个数字，或者之后的数字比它小的话，则加上当前数字
第二，其他情况则减去这个数字

*****

# Solution

```cpp
class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        unordered_map<char, int> value{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        for (int i = 0; i < s.size(); ++i) {
            int val = value[s[i]];
            if (i == s.size() - 1 || value[s[i+1]] <= value[s[i]]) res += val;
            else res -= val;
        }
        return res;
    }
};
```

我们也可以每次跟前面的数字比较，如果小于等于前面的数字，我们先加上当前的数字，如果大于的前面的数字，我们加上当前的数字减去二倍前面的数字，这样可以把在上一个循环多加数减掉，参见代码如下:

```cpp
class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        unordered_map<char, int> m{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || m[s[i]] <= m[s[i - 1]]) res += m[s[i]];
            else res += m[s[i]] - 2 * m[s[i - 1]];
        }
        return res;
    }
};
```
