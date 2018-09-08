---
title: Leetcode 14. Longest Common Prefix
date: 2018-06-18 11:50:32
categories: Leetcode
tags: Leetcode
---

﻿Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string  `""`.

**Example 1:**
>**Input:** ["flower","flow","flight"]
**Output:** "fl"

**Example 2:**
>**Input:** ["dog","racecar","car"]
**Output:** ""
**Explanation:** There is no common prefix among the input strings.

**Difficulty**:Easy
**Category**:  
<!--more-->
*****

## Analyze
这道题让我们求一系列字符串的共同前缀，没有什么特别的技巧，无脑查找即可，我们定义两个变量i和j，其中i是遍历搜索字符串中的字符，j是遍历字符串集中的每个字符串。这里将单词上下排好，则相当于一个各行长度有可能不相等的二维数组，我们遍历顺序和一般的横向逐行遍历不同，而是采用纵向逐列遍历，在遍历的过程中，如果某一行没有了，说明其为最短的单词，因为共同前缀的长度不能长于最短单词，所以此时返回已经找出的共同前缀。我们每次取出第一个字符串的某一个位置的单词，然后遍历其他所有字符串的对应位置看是否相等，如果有不满足的直接返回res，如果都相同，则将当前字符存入结果，继续检查下一个位置的字符，参见代码如下：
## Solution
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if( strs.empty() ) return "";
        string res = "";
        
        for (int i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];
            for ( int j = 1; j < strs.size(); ++j) {
                if (i >= strs[j].size() || strs[j][i] != c) return res;
            }
            res.push_back(c);
        }
        return res;
        
    }
};
```
