---
title: Leetcode 893. Groups of Special-Equivalent Strings
date: 2018-10-20 17:09:31
updated: 2018-10-20 17:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question


You are given an array  `A`  of strings.

Two strings  `S`  and  `T`  are _special-equivalent_ if after any number of  _moves_, S == T.

A  _move_  consists of choosing two indices  `i`  and  `j`  with  `i % 2 == j % 2`, and swapping  `S[i]`  with  `S[j]`.

Now, a  _group of special-equivalent strings from  `A`_ is a non-empty subset S of  `A` such that any string not in S is not special-equivalent with any string in S.

Return the number of groups of special-equivalent strings from  `A`.

**Example 1:**

> **Input:** ["a","b","c","a","c","c"]
> **Output:** 3
> **Explanation**: 3 groups ["a","a"], ["b"], ["c","c","c"]

**Example 2:**

> **Input:** ["aa","bb","ab","ba"]
> **Output:** 4
> **Explanation**: 4 groups ["aa"], ["bb"], ["ab"], ["ba"]

**Example 3:**

> **Input:** ["abc","acb","bac","bca","cab","cba"]
> **Output:** 3
> **Explanation**: 3 groups ["abc","cba"], ["acb","bca"], ["bac","cab"]

**Example 4:**

> **Input:** ["abcd","cdab","adcb","cbad"]
> **Output:** 1
> **Explanation**: 1 group ["abcd","cdab","adcb","cbad"]

**Note:**

- `1 <= A.length <= 1000`
- `1 <= A[i].length <= 20`
- All  `A[i]`  have the same length.
- All  `A[i]`  consist of only lowercase letters.

<!--more-->

----------

# Solution

```cpp
class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) { 
      std::unordered_set<std::string> myset;
      for (string x : A) {
          std::string odd, even;
          for(int i = 0; i < x.size(); ++i) {
              if(i%2 == 0) even += x[i];
              else odd += x[i];
          }
          sort(odd.begin(),odd.end());
          sort(even.begin(), even.end());
          myset.insert(odd+even);
      }
      return myset.size();
    }
};
```