---
title: Leetcode 44. Wildcard-Matching
date: 2018-06-18 11:50:32
updated: 2018-06-18 11:50:32
categories: Leetcode
tags: Leetcode
notshow: true
---

Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for  `'?'`  and  `'*'`.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the  **entire**  input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters  `a-z`.
- `p`  could be empty and contains only lowercase letters  `a-z`, and characters like  `?` or `*`.

<!--more-->

**Example 1:**

> **Input:**
> s = "aa"
> p = "a"
> **Output:** false
> **Explanation:** "a" does not match the entire string "aa".

**Example 2:**

> **Input:**
> s = "aa"
> p = "*"
> **Output:** true
> **Explanation:** '*' matches any sequence.

**Example 3:**

>**Input:**
s = "cb"
p = "?a"
**Output:** false
**Explanation:** '?' matches 'c', but the second letter is 'a', which does not match 'b'.

**Example 4:**

>**Input:**
s = "adceb"
p = "*a*b"
**Output:** true
**Explanation:** The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

**Example 5:**

>**Input:**
s = "acdcb"
p = "a*c?b"
**Output:** false

**Difficulty**:Hard
**Category**:
<!--more-->
*****

# Analyze

这道题通配符匹配问题还是小有难度的，这道里用了贪婪算法Greedy Alogrithm来解，由于有特殊字符*和？，其中？能代替任何字符，*能代替任何字符串，那么我们需要定义几个额外的指针，其中scur和pcur分别指向当前遍历到的字符，再定义pstar指向p中最后一个*的位置，sstar指向此时对应的s的位置，具体算法如下：

- 定义scur, pcur, sstar, pstar

- 如果*scur存在

- 如果*scur等于*pcur或者*pcur为 '?'，则scur和pcur都自增1

- 如果*pcur为'*'，则pstar指向pcur位置，pcur自增1，且sstar指向scur

- 如果pstar存在，则pcur指向pstar的下一个位置，scur指向sstar自增1后的位置

- 如果pcur为'*'，则pcur自增1

- 若*pcur存在，返回False，若不存在，返回True
## Solution
## Issues
