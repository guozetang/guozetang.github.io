---
title: Leetcode 11. Container With Most Water
date: 2018-06-18 09:30:32
updated: 2018-06-18 09:30:32
categories: Leetcode
tags: Leetcode
---
## Container with the Most Water
Given  _n_  non-negative integers  _a1_,  _a2_, ...,  _an_, where each represents a point at coordinate (_i_,  _ai_).  _n_  vertical lines are drawn such that the two endpoints of line  _i_  is at (_i_,  _ai_) and (_i_, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and  _n_  is at least 2.

**Difficulty**:Medium
**Category**:Math

<!--more-->
*****

## Analyze

只需要定义`i`和`j`两个指针分别指向数组的左右两端，然后两个指针向中间搜索，每移动一次算一个值并和之前的结果比较取较大值. (ps.容器装水量: 是找出左右两个边缘中较小的那个乘以两边缘的距离)

*****

## Solution

```cpp
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int res = 0, i = 0, j = height.size() - 1;
    while (i < j) {
      res = max(res, (min(height[i], height[j])) * (j - i));
      height[i] > height[j] ? --j : ++i;
    }
    return res;
  }
};
```
