---
title: Leetcode 345. Reverse Vowels of a String
date: 2018-09-23 14:09:31
updated: 2018-09-23 14:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Write a function that takes a string as input and reverse only the vowels of a string.

**Example 1:**

>**Input:** "hello"
>**Output:** "holle"

**Example 2:**

>**Input:** "leetcode"
>**Output:** "leotcede"

**Note:**  
The vowels does not include the letter "y".

**Difficulty**:Easy
**Category**:  
<!--more-->
******

# Analyze

这道题目要求交换字符串左右的元音字母`a, e, i，o，u, A，E, I，O, U`, 我们只用在找到左右都是元音字母的时候进行交换，然后`左指针++`, '右指针--'就可以继续寻找下一个了。
整体代码结构：

```cpp
public:
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        while(left < right) {
            if(左右都是元音字母) {
                swap(s[left++], s[right--]);
            }
        }
```
主要需要实现的就是里面寻找到左右都是元音字母的过程。

# Solution

## Solution 1

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        while(left < right) {
            if(isVowel(s[left]) && isVowel(s[right])) {
                swap(s[left++], s[right--]);
            }
            else if(isVowel(s[left])) {
                right--;
            }
            else {
                left++;
            }
        }
        return s;
    }
    
    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' 
               || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};
```

## Solution 2

我们尝试使用C++中String类提供的函数来更简洁的完成这个查找的过程。

- [find_first_of](http://www.cplusplus.com/reference/string/string/find_first_of/)
Find character in string  (public member function )
- [find_last_of](http://www.cplusplus.com/reference/string/string/find_last_of/)
Find character in string from the end  (public member function )

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            left = s.find_first_of("aeiouAEIOU", left);
            right = s.find_last_of("aeiouAEIOU", right);
            if (left < right) {
                swap(s[left++], s[right--]);
            }
        }
        return s;
    }
};
```