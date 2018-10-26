---
title: Leetcode 856. Score of Parentheses
date: 2018-09-11 02:09:31
updated: 2018-09-11 02:09:31
categories: C++
tags: C++
notshow: true
top:
---

# Question

Given a balanced parentheses string  `S`, compute the score of the string based on the following rule:

- `()`  has score 1
- `AB`  has score  `A + B`, where A and B are balanced parentheses strings.
- `(A)`  has score  `2 * A`, where A is a balanced parentheses string.

**Example 1:**
> **Input:** "()"
> **Output:** 1

**Example 2:**
> **Input:** "(())"
> **Output:** 2

**Example 3:**
> **Input:** "()()"
> **Output:** 2

**Example 4:**
> **Input:** "(()(()))"
> **Output:** 6

**Note:**

1. `S`  is a balanced parentheses string, containing only  `(`  and  `)`.
2. `2 <= S.length <= 50`

<!-- more -->

-------

# Solution

```cpp
class Solution {
 public:
  int scoreOfParentheses(string S) {
    int res = 0;
    std::stack<char> par_stack;
    bool flag = false;
    for (int i = 0; i < S.size(); ++i) {
      if (S[i] == '(') {
        par_stack.push(S[i]);
        flag = true;
      } else if (flag == true) {
        flag = false;
        if (par_stack.size() == 1)
          res++;
        else
          res += 1 * pow(2, par_stack.size() - 1);
        par_stack.pop();
      } else
        par_stack.pop();
    }

    return res;
  }
};
```
