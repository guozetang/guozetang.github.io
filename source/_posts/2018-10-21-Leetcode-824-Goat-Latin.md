---
title: Leetcode 824. Goat Latin
date: 2018-10-21 22:09:31
updated: 2018-10-21 22:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

A sentence  `S`  is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "_Goat Latin"_ (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

- If a word begins with a vowel (a, e, i, o, or u), append  `"ma"` to the end of the word.  
    For example, the word 'apple' becomes 'applema'.  
- If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add  `"ma"`.  
    For example, the word  `"goat"` becomes  `"oatgma"`.  
- Add one letter  `'a'` to the end of each word per its word index in the sentence, starting with 1.  
    For example, the first word gets  `"a"`  added to the end, the second word gets  `"aa"`  added to the end and so on.

Return the final sentence representing the conversion from  `S` to Goat Latin.

**Example 1:**

> **Input:** "I speak Goat Latin"
> **Output:** "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"

**Example 2:**

> **Input:** "The quick brown fox jumped over the lazy dog"
> **Output:** "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"

<!--more-->

---------

# Analyze

The input are a lots of strings. As a result, we need to convert thesr string to `Goat Latin`. So, we need to deal with each one string in the input.

- If the first letter is not vowel(aeiouAEIOU), then we need to move the first letter to the last one.
- We need add `ma` after the string.
- We need add the index number of `a` for the word in the string at the end of the word.

---------

# Solution

```cpp
class Solution {
public:
    string toGoatLatin(string S) {
      const string vowel = "aeiouAEIOU";
      string res, word;
      istringstream stream(S);
      int index = 0;
        while(stream >> word){
            if( vowel.find(word[0]) == std::string::npos ){
            word = word.substr(1) + word[0];
        }
        index ++;
        res += " "+ word + "ma" + string (index, 'a');
      }
      return res.substr(1);
    }
};
```