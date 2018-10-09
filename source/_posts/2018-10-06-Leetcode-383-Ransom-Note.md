---
title: Leetcode 383. Ransom Note
date: 2018-10-06 14:09:31
updated: 2018-10-06 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given an arbitrary ransom(任意的赎金) note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

**Note:**  
You may assume that both strings contain only lowercase letters.
> canConstruct("a", "b") -> false
> canConstruct("aa", "ab") -> false
> canConstruct("aa", "aab") -> true

<!--more-->

----------

# Analyze

这道题目使用`两个string`(string ransomNote, string magazine)作为输入，如果`第二个string`里面包含`第一个string`，那么就返回`true`, 如果不是那么就返回来`false`.

- 使用hashmap存入所有的`string magazine`里面的每一个`char`
- 然后再扫描`string ransomNote`里面的每一个`char`，在存在的`hashmap`里面去查找是否有这一个字符，如果有，那么就把这个字符自减一，如果没有，那么放回`false`

----------

# Solution

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
      std::unordered_map<char,int> data_set;
      for(char c : magazine) ++data_set[c];
      for(char c : ransomNote) {
        if( data_set.count(c) ) --data_set[c];
        else {
          return false;
        }
        if(data_set[c] < 0) return false;
      }
      return true;
    }
};
```