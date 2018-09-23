---
title: Leetcode 524. Longest Word in Dictionary through Deleting
date: 2018-09-23 15:09:31
updated: 2018-09-23 15:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

**Example 1:**  
> **Input:** s = "abpcplea", d = ["ale","apple","monkey","plea"]
> **Output:** "apple"

**Example 2:**  
> **Input:** s = "abpcplea", d = ["a","b","c"]
> **Output:** "a"

**Note:**  

1. All the strings in the input will only contain lower-case letters.
2. The size of the dictionary won't exceed 1,000.
3. The length of all the strings in the input won't exceed 1,000.

**Difficulty**:Medium
**Category**:

<!--more-->
******

# Analyze

这道题的输入是一个字符串以及一个包含了很多字符串的字典，要求在字典中找出最长的单词，对这个最长的单词的要求是: 这个单词中的每一的字母都在前面的字符串里面出现过，并且出现的顺序不能颠倒）如果找到几个字符串的长度是一样的，那么就选择最小的字符串。

代码结构：

```cpp
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string res= ""; 返回值
        for (string d_str : d) {   //1.遍历字典中每个字符串
            2。验证这个字符串在不再s中依次出现
            if(d_str在s中依次出现过 && d_str的长度大于或者等于返回值) {
                if(d_str.size() > res.size() || d_str < res) {
                    res=d_str;
                }
            }
        }
    }
}
```

步骤：

1. 遍历字典中的单词，验证当前单词是否能由字符串s通过删除字符来得到
2. 如果能得到，而且单词长度大于等于结果res的长度，我们再看是否需要更新结果res
3. 两种情况是必须要更新结果res的
    - 一个是当前单词长度大于结果res的长度
    - 另一种是当前单词长度和res相同，但是字母顺序小于结果res，这两种情况下更新结果res即可.

******

# Solution

```cpp
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string res = "";
        for (string d_str : d) {
            int m = 0;
            for (int i = 0; i < s.size(); ++i) {
                if(m < d_str.size() && s[i] == d_str[m]) m++;
            }

            if( m == d_str.size() && d_str.size() >= res.size() ) {
                if( d_str.size() > res.size() || d_str < res) { res = d_str; }
            }
        }
        return res;

    }
};
```