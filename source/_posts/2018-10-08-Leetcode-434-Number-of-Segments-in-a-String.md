---
title: Leetcode 434. Number of Segments in a String
date: 2018-10-08 14:09:31
updated: 2018-10-08 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any  **non-printable**  characters.

**Example:**
> **Input:** "Hello, my name is John"
> **Output:** 5

<!--more-->

----

# Analyze

在给定的一段字符串中，判断出来里面的单词个数，我们只需要设置一个`word`开始的标志位`word_flag`，刚刚单词开始的时候将其设置为1，当出现空格的时候，将其变成0，这样我们就可以记录单词的格式，如果到最后一个字母的话，那就将其作为单词的结尾，给单词数量加1.

----

# Solution

```cpp
class Solution {
public:
    int countSegments(string s) {
      int len = s.length(), count = 0, word_flag = 0;

      for(int i = 0; i < len; ++i) {
        if(s[i] != ' ' && word_flag == 0) word_flag = 1;
        if( (s[i] == ' ' || i == len-1 ) && word_flag == 1) {
          word_flag = 0;
          ++count;
        }
      }
      return count;
    }
};
```