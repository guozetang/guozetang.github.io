---
title: Leetcode 47. Multiply Strings
date: 2018-09-14 17:09:31
updated: 2018-09-14 17:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question
Given two non-negative integers  `num1`  and  `num2`  represented as strings, return the product of  `num1`  and  `num2`, also represented as a string.

**Example 1:**
>**Input:** num1 = "2", num2 = "3"
**Output:** "6"

**Example 2:**
>**Input:** num1 = "123", num2 = "456"
**Output:** "56088"

**Note:**

1. The length of both  `num1`  and  `num2`  is < 110.
2. Both  `num1`  and  `num2`  contain only digits  `0-9`.
3. Both  `num1`  and  `num2` do not contain any leading zero, except the number 0 itself.
4. You  **must not use any built-in BigInteger library**  or  **convert the inputs to integer**  directly.

**Difficulty**:Medium
**Category**:

<!--more-->
******

# Analyze

引自[博客](http://www.cnblogs.com/TenosDoIt/p/3735309.html)的图形，方便进行说明：

![](/images/in-post/2018-09-14-Leetcode-43-Multiply-String/2018-09-14-18-36-44.png)

287*785来作为例子，首先我们需要一个中间的值来保存我们得到的中间值`14 66 119 109 72`, 使用双重循环，当外循环为`2`的时候，分别生成`14 10 16`，当外循环为`8`的时候，我们同时要变化存放没一项相乘的数值。


参考博文：
- [LeetCode Multiply Strings 字符串相乘](https://www.cnblogs.com/grandyang/p/4395356.html)
- [LeetCode:Multiply Strings](http://www.cnblogs.com/TenosDoIt/p/3735309.html)  博文中有非常形象的图像可以说明怎么计算的

******

# Solution

```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        std::string res;
        int len_num1 = num1.size(), len_num2 = num2.size(), carry = 0;
        int res_len = (len_num1-1) + (len_num2-1);
        std::vector<int> temp(len_num1+len_num2,0);
        
        for(int i = 0; i < len_num1; i++) {
            for(int j = 0; j < len_num2; j++) {
                temp[res_len-i-j] += (num1[i]-'0') * (num2[j] - '0');
                std::cout << temp[res_len-i-j] << std::endl;
            } 
        }

        for(int i = 0; i < len_num1+len_num2; i++) {
            temp[i] += carry;
            carry = temp[i] / 10;
            temp[i] = temp[i] % 10; 
        }
        
        int i = res_len+1;
        while(temp[i]==0) i--;
        if(i < 0) return "0";
        
        
        while(i >= 0) {
            std::cout<< temp[i] << std::endl;
            res.push_back(temp[i--]+'0');
        }
        return res;
        
        
    }
};
```

******

# Errors

## Error 1

```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        std::string r
LeetCode:Multiply Stringses;
        int len_num1 = num1.size(), len_num2 = num2.size(), carry = 0;
        int res_len = (len_num1-1) + (len_num2-1);
        std::vector<int> temp(len_num1+len_num2,0);
        
        for(int i = 0; i < len_num1; i++) {
            for(int j = 0; j < len_num2; j++) {
                temp[res_len-i-j] += (num1[i]-'0') * (num2[i] - '0');
                std::cout << temp[res_len-i-j] << std::endl;
            } 
        }
        
        for(int i = 0; i < len_num1+len_num2; i++) {
            temp[i] += carry;
            carry = temp[i] / 10;
            temp[i] = temp[i] % 10; 
        }
        
        int i = res_len+1;
        while(temp[i]==0) i--;
        if(i < 0) return "0";
        
        
        while(i >= 0) {
            std::cout<< temp[i] << std::endl;
            res.push_back(temp[i--]+"0");
        }
        return res;
        
        
    }
};
```

**Error:** Line 55: invalid conversion from 'const char*' to 'char' [-fpermissive]

这里错误的原因是在`res.push_back(temp[i--]+"0");`这个位置，这里是双引 号`“”`对应的是字符串，类型是`char*`的指针类型。我们这里需要的是`char`类型的字符。修改为：

```cpp
res.push_back(temp[i--]+"0");
```

> 单引号 ‘  ’ 里的值，是char型常量  
双引号 " " 里的值，是char[]型指针常量