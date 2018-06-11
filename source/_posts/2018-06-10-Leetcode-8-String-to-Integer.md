---
title: Leetcode 8. String to Integer (atoi)
date: 2018-06-10 10:30:32
categories: Leetcode
tags: Leetcode
---

Implement  `atoi`  which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

**Note:**

-   Only the space character  `' '`  is considered as whitespace character.
-   Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

**Example 1:**
>**Input:** "42"
>**Output:** 42

**Example 2:**
> **Input:** "   -42"
> **Output:** -42
> **Explanation:** The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

**Example 3:**
> **Input:** "4193 with words"
> **Output:** 4193
> **Explanation:** Conversion stops at digit '3' as the next character is not a numerical digit.

**Example 4:**
> **Input:** "words and 987"
> **Output:** 0
> **Explanation:** The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.

**Example 5:**
> **Input:** "-91283472332"
> **Output:** -2147483648
> **Explanation:** The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
 <!--more-->
## Analyze
由于输入的是字符串，所以需要题目中给出的情况:
1. 若字符串开头是空格，则跳过所有空格，到第一个非空格字符，如果没有，则返回0.
 `while(i < len && str[i] == ' ') ++i;`

2. 若第一个字符不是符号`+/-和数字`，则返回0.

3. 若第一个非空格字符是符号+/-，则标记sign的正负.

4. 在第一个字符是数字或者符号+/-的情况下, 如果下一个字符是数字，则转为整形存下来，若接下来再有非数字出现，则返回目前的结果。

5. 还需要考虑边界问题，如果超过了整形数的范围，则用边界值替代当前值。
```cpp
if (base > INT_MAX / 10 || (base == INT_MAX / 10 && (str[i] - '0') > 7)) {
      return (symbol == 1) ? INT_MAX : INT_MIN;
}
base = base * 10 + (str[i++] - '0');
```
注意, 这里判断的时候, 是判断的base*10之前的数据情况, 所以判断`base > INT_MAX / 10 || (base == INT_MAX / 10 && (str[i] - '0') > 7)`
如果 `base > INT_MAX/10` 那么说明数据完全溢出了, 如果当前的`base == INT_MAX/10 `那么说明有超出的风险, 需要检查最后一位数是否太大. 因为最后一位数INT的正数最大为7, 负数最小值的最小位最多为8, 所以当最小位 > 7的时候, 就可以将其判断为异常的数据, 因为异常的话, 如果为负数,  给它赋值之后, 也是负数的最小值. 是正确的.

## Solution
```cpp
class Solution {
public:
    int myAtoi(string str) {
        if (str.size() == 0) return 0;
        
        int symbol = 1, base = 0, i = 0, len = str.size();
        
        //Find the first letter: +/-
        while(i < len && str[i] == ' ') ++i;
        
        if(str[i] == '+' || str[i] == '-') {
            symbol = (str[i++] == '+')? 1 : -1;
        }
        
        //Find all the data
        while(i < len && str[i] >= '0' && str[i] <= '9') {
            // Check the base data not overflow
            if (base > INT_MAX / 10 || (base == INT_MAX / 10 && (str[i] - '0') > 7)) {
                return (symbol == 1) ? INT_MAX : INT_MIN;
            }
            
            base = base * 10 + (str[i++] - '0');
        
        }
        return base * symbol;
    }
    
};
```
