---
title: Leetcode 40. Combination Sum II
date: 2018-10-30 06:09:31
updated: 2018-10-30 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a collection of candidate numbers (`candidates`) and a target number (`target`), find all unique combinations in  `candidates` where the candidate numbers sums to  `target`.

Each number in  `candidates` may only be used  **once**  in the combination.

**Note:**

- All numbers (including  `target`) will be positive integers.
- The solution set must not contain duplicate combinations.

**Example 1:**

**Input:** candidates = `[10,1,2,7,6,1,5]`, target = `8`,
**A solution set is:**
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

**Example 2:**

**Input:** candidates = [2,5,2,1,2], target = 5,
**A solution set is:**
[
  [1,2,2],
  [5]
]

<!-- more -->

-----------

# Solution

···cpp
class Solution {
 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    sort(candidates.begin(), candidates.end());
    findcombinationSum(candidates, target, 0, temp, res);
    return res;
  }

  void findcombinationSum(vector<int>& candidates, int target, int index,
                          vector<int>& temp, vector<vector<int>>& res) {
    if (target < 0) return;
    if (target == 0) res.emplace_back(temp);
    for (int i = index; i < candidates.size(); ++i) {
      if (i > index && candidates[i] == candidates[i - 1]) continue;
      temp.emplace_back(candidates[i]);
      findcombinationSum(candidates, target - candidates[i], i + 1, temp, res);
      temp.pop_back();
    }
  }
};
```