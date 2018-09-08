---
title: Leetcode 16. 3Sum Closest
date: 2018-06-08 01:30:32
categories: Leetcode
tags: Leetcode
---

# 3Sum Closest

Given an array _S_ of _n_ integers, find three integers in _S_ such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

**Difficulty**:Medium
**Category**:  
*****


# Solution
```cpp
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3){
            return 0;
        }
        int closest = nums[0] + nums[1] + nums[2];
        int diff = abs(closest - target);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size() - 2; ++i){
            int left = i + 1, right = nums.size() - 1;
            while(left < right){
                int sum = nums[i] + nums[left] + nums[right];
                int newDiff = abs(sum - target);
                if(diff > newDiff){
                    diff = newDiff;
                    closest = sum;
                }
                if(sum < target) left++;
                else right--;
            }
        }
        return closest;
    }
};
```