---
title: Leetcode 5. Longest Palindromic Substring
date: 2018-06-10 02:44:02
categories: Leetcode
tags: Leetcode
---
## Leetcode 5.Longest Palindromic Substring  
Given a string  **s**, find the longest palindromic substring in  **s**. You may assume that the maximum length of  **s**  is 1000.

**Example 1:**
> **Input:** "babad"  
> **Output:** "bab"  
> **Note:** "aba" is also a valid answer. 

**Example 2:**
> **Input:** "cbbd"  
> **Output:** "bb"


**Difficulty**:Medium
**Category**:  
<!--more-->
*****

## Analyze
这道题让我们求的是最长回文串，那么什么是回文串呢？
> “回文串”是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。  

那么这道题，我们要求解最长的回文串的话，可以使用对称验证的方式进行判断，对称验证有两种情况，回文串长度为奇数或者为偶数。如果回文串长度为奇数，那么是以一个字符作为中心的，如果回文串的长度为偶数，那么是以两个相同的字符来作为中心的。分为这两种情况分别进行遍历查找。

## Solution 1
> C++实现  

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, left = 0, right = 0, len = 0;
        
        for (int i = 0; i < s.size() - 1; ++i) {
            if (s[i] == s[i + 1]) {
                left = i;
                right = i + 1;
                searchPalindromicSubstring(s, left, right, start, len); 
            }
            left = right = i;
            searchPalindromicSubstring(s, left, right, start, len); 
        }
        

        if (len == 0) len = s.size();
        return s.substr(start, len);
    }
    
    void searchPalindromicSubstring(string s, int left, int right, int &start, int &len) {
        int diff = 1;
        
        while((left - diff) >= 0 && (right + diff) < s.size()) {
            if (s[left - diff] != s[right + diff]) break;
            ++diff;
        }
        
        int wide = right - left + 2*diff - 1;
        if(len < wide) {
            len = wide;
            start = left - diff + 1;
        }  
    }
};

```