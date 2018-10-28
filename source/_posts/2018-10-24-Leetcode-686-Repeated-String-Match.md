---
title: Leetcode 686. Repeated String Match
date: 2018-10-22 19:09:31
updated: 2018-10-22 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

**Note:**  
The length of  `A`  and  `B`  will be between 1 and 10000.

<!--more-->

-------

# solution

```cpp
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
      int length_a = A.size(), length_b = B.size();
      string temp;
      int n = length_b/length_a;
      if(length_b % length_a != 0) n = n+1;

      for (int i = 0; i < n; ++i) temp += A;

      if (temp.find(B) != string::npos) return n;  
      temp += A;
      return (temp.find(B) != string::npos) ? n + 1 : -1;
    }
};
```