---
title: Leetcode 20. Valid Parentheses
date: 2018-09-14 14:09:31
updated: 2018-09-14 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a string containing just the characters  `'('`,  `')'`,  `'{'`,  `'}'`,  `'['`  and  `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

**Example 1:**
> **Input:** "()"
> **Output:** true

**Example 2:**
> **Input:** "()[]{}"
> **Output:** true

**Example 3:**
> **Input:** "(]"
> **Output:** false

**Example 4:**
> **Input:** "([)]"
> **Output:** false

**Example 5:**
> **Input:** "{[]}"
> **Output:** true

<!--more-->

----

# Analyze

验证输入的字符串是否为括号字符串，包括大括号，中括号和小括号。在这里使用一个栈来实现, 如果扫描到的是左边的括号`(,{,[`, 那么就把其压入到栈中，之后如果扫描到的不是左边的符号的话，那么就把堆栈最上面的数据出栈，然后如果出栈的数据是对应的右括号的话，那么就`pop` 出栈这个数据，如果不是对应的有括号，那么就返回`false`.

----

# Solution

```cpp
class Solution {
public:
    bool isValid(string s) {
      std::stack<char> parentheses;
      for(int i = 0; i < s.size(); ++i){
        if( s[i] == '(' || s[i] == '{' || s[i] == '[') parentheses.push(s[i]);
        else {
          if(s[i] == ')' && parentheses.top() != '(') return false;
          if(s[i] == '}' && parentheses.top() != '{') return false;
          if(s[i] == ']' && parentheses.top() != '[') return false;
          parentheses.pop();
        }
      }
      return parentheses.empty();
    }
};
```
