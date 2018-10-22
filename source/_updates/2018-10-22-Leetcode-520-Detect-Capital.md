---
title: Leetcode 520. Detect Capital
date: 2018-10-22 02:09:31
updated: 2018-10-22 02:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

1. All letters in this word are capitals, like "USA".
2. All letters in this word are not capitals, like "leetcode".
3. Only the first letter in this word is capital if it has more than one letter, like "Google".

Otherwise, we define that this word doesn't use capitals in a right way.

**Example 1:**  

> **Input:** "USA"
> **Output:** True

**Example 2:**  

> **Input:** "FlaG"
> **Output:** False

**Note:**  The input will be a non-empty word consisting of uppercase and lowercase latin letters.


# Solution

```cpp
class Solution {
public:
    bool detectCapitalUse(string word) {
      int length = word.size();
      int capital_letter = 0, low_letter = 0;
      for (int i = 0; i < length; ++i) {
        if(word[i] >= 'A' && word[i] <= 'Z') capital_letter++;
        else low_letter++;
      }
      if(capital_letter > 0 && low_letter==0) return true;
      if(capital_letter == 0 && low_letter>0) return true;
      if(capital_letter == 1 && word[0] <= 'Z') return true;
      return false;
    }
};
```