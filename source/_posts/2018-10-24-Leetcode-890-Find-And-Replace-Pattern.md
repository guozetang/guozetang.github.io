---
title: Leetcode 890. Find and Replace Pattern
date: 2018-10-24 19:09:31
updated: 2018-10-24 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

You have a list of `words`  and a  `pattern`, and you want to know which words in  `words`  matches the pattern.

A word matches the pattern if there exists a permutation of letters  `p`  so that after replacing every letter  `x`  in the pattern with  `p(x)`, we get the desired word.

(_Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter._)

Return a list of the words in  `words` that match the given pattern.

You may return the answer in any order.

**Example 1:**

**Input:** words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
**Output:** ["mee","aqq"]
**Explanation:** "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
since a and b map to the same letter.

**Note:**

- `1 <= words.length <= 50`
- `1 <= pattern.length = words[i].length <= 20`

<!--more-->

----------

# Solution

```cpp
class Solution {
 public:
  vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> res;

    for (auto w : words) {
      string s = w;
      vector<int> vec(127), vec_p(127);
      for (char c : pattern) vec_p[c] = 1;
      for (int i = 0; i < s.size(); ++i) {
        if (vec[s[i]] == 0 && vec_p[pattern[i]] == 1) {
          vec[s[i]] = pattern[i];
          vec_p[pattern[i]] = 0;
        }
      }

      for (int i = 0; i < s.size(); ++i) {
        if (vec[s[i]]) s[i] = vec[s[i]];
      }

      if (s == pattern) res.push_back(w);
    }

    return res;
  }
};
```