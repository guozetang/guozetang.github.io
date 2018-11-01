---
title: Leetcode 39. Combination Sum
date: 2018-10-31 20:09:31
updated: 2018-10-31 20:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a  **set**  of candidate numbers (`candidates`)  **(without duplicates)**  and a target number (`target`), find all unique combinations in  `candidates` where the candidate numbers sums to  `target`.

The  **same**  repeated number may be chosen from  `candidates` unlimited number of times.

**Note:**

- All numbers (including  `target`) will be positive integers.
- The solution set must not contain duplicate combinations.

**Example 1:**

**Input:** candidates = `[2,3,6,7],` target = `7`,
**A solution set is:**
[
  [7],
  [2,2,3]
]

**Example 2:**

**Input:** candidates = [2,3,5]`,` target = 8,
**A solution set is:**
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

<!-- moret -->

---------------

# Solution 

```cpp
class Solution {
 public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    findcombinationSum(candidates, target, 0, temp, res);
    return res;
  }

  void findcombinationSum(vector<int>& candidates, int target, int index,
                          vector<int>& temp, vector<vector<int>>& res) {
    if (target < 0) return;
    if (target == 0) res.emplace_back(temp);
    for (int i = index; i < candidates.size(); ++i) {
      temp.emplace_back(candidates[i]);
      findcombinationSum(candidates, target - candidates[i], i, temp, res);
      temp.pop_back();
    }
  }
};
```