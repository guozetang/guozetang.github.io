---
title: Leetcode 10. Regular Expression Match
date: 2018-06-18 08:30:32
categories: Leetcode
tags: Leetcode
---

﻿Given an input string (`s`) and a pattern (`p`), implement regular expression matching with support for  `'.'`  and  `'*'`.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the  **entire**  input string (not partial).

**Note:**

-   `s` could be empty and contains only lowercase letters  `a-z`.
-   `p`  could be empty and contains only lowercase letters  `a-z`, and characters like `.` or `*`.
<!-- more -->
**Example 1:**

> **Input:**
> s = "aa"  
> p = "a"  
> **Output:** false  
> **Explanation:** "a" does not match the entire string "aa".  
<!--more-->

**Example 2:**  
>**Input:**  
s = "aa"  
p = "a*"  
**Output:** true  
**Explanation:** '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

**Example 3:**

>**Input:**  
s = "ab"  
p = ".*"  
**Output:** true  
**Explanation:** ".*" means "zero or more (*) of any character (.)".  

**Example 4:**
>**Input:**  
s = "aab"  
p = "c*a*b"  
**Output:** true  
**Explanation:** c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".  

**Example 5:**

>**Input:**  
s = "mississippi"  
p = "mis*is*p*."  
**Output:** false  

## Analyze
这道求正则表达式匹配的题和那道 [Wildcard Matching 通配符匹配](http://www.cnblogs.com/grandyang/p/4401196.html)的题很类似，不同点在于*的意义不同，在之前那道题中，*表示可以代替任意个数的字符，而这道题中的*表示之前那个字符可以有0个，1个或是多个，就是说，字符串a*b，可以表示b或是aaab，即a的个数任意，这道题的难度要相对之前那一道大一些，分的情况的要复杂一些，需要用递归Recursion来解，大概思路如下：

- 若p为空，若s也为空，返回true，反之返回false

- 若p的长度为1，若s长度也为1，且相同或是p为'.'则返回true，反之返回false

- 若p的第二个字符不为*，若此时s为空返回false，否则判断首字符是否匹配，且从各自的第二个字符开始调用递归函数匹配

- 若p的第二个字符为*，若s不为空且字符匹配，调用递归函数匹配s和去掉前两个字符的p，若匹配返回true，否则s去掉首字母

- 返回调用递归函数匹配s和去掉前两个字符的p的结果
## Solution
```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        if( p.empty() ) return s.empty();
        if( p.size() == 1) {
            return (s.size() == 1 && ((s[0] == p[0]) || p[0] == '.'));
        }
        if( p[1] != '*') {
            if( s.empty() ) return false;
            return ( s[0] == p[0]|| p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }
        while (!s.empty() && ( s[0] == p[0] || p[0] == '.')) {
            if ( isMatch(s, p.substr(2)) ) return true;
            s = s.substr(1);
        }
    
        
        return isMatch(s, p.substr(2));
    }
};
```

## Question
 if( p.empty() && s.empty() ) return true; 和 if (p.empty()) return s.empty();的差异
 如果要实现p为空，在s也为空的情况下，返回真值的情况的话，写成`p.empty() && s.empty()`, 那么在后面的if语句中必须有一个return false; 因为第一种书写方式，是没有处理`p.empty()&& !s.empty()`这种情况的，这就会出现问题。当出现这种情况的时候，没有返回值，或者返回值出错。
需要仔细理解的地方是：
```cpp
        while (!s.empty() && ( s[0] == p[0] || p[0] == '.')) {
            if ( isMatch(s, p.substr(2)) ) return true;
            s = s.substr(1);
        }
```
当这里出现`*`号的时候，可能前面的字母只有0个或者有很多个，先将其作为有`0`个的方式去处理，那就是`isMatch(s, p.substr(2))`,如果有很多个的处理方式就是` s = s.substr(1);`之后，在判断第一位是不是还和`p[0]`相同
