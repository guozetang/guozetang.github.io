---
title: Leetcode 387. First Unique Character in a String
date: 2018-10-22 14:09:31
updated: 2018-10-22 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

**Examples:**

> s = "leetcode"
> return 0.
> s = "loveleetcode",
> return 2.

**Note:**  You may assume the string contain only lowercase letters.

<!--more-->

-------

# Solution

```cpp
class Solution {
public:
    int firstUniqChar(string s) {
      std::vector<int> string_set(128);
      for(int i = 0; i < s.size(); ++i) string_set[s[i]]++;
      for(int i = 0; i < s.size(); ++i) {
        if(string_set[s[i]] == 1) return i;
      }
      return -1;
    }
};
```