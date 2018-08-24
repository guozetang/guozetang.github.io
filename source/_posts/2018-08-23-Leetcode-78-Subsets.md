---
title: Leetcode 78. Subsets
date: 2018-08-23 07:42:10
categories: Leetcode
tags: Leetcode
---
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

> Input: nums = [1,2,3]
> Output:
> [
>  [3],
>  [1],
>  [2],
>  [1,2,3],
>  [1,3],
>  [2,3],
>  [1,2],
>  []
> ]


<!--more-->

# Analyze
求子集集合的问题，我们可以每次处理一个元素，将当前的元素加到之前存在的所有子集里面，这样能够很方便的处理。

# Solution

```c++
// Non-recursion
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > res(1);
        sort(S.begin(), S.end());
        for (int i = 0; i < S.size(); ++i) {
            int len = res.size();
            for (int j = 0; j < len; ++j) {
                res.push_back(res[j]);
                res.back().push_back(S[i]);
            }
        }
        return res;
    }
};
```