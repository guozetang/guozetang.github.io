---
title: Leetcode 42. Trapping Rain Water
date: 2018-06-18 11:50:32
categories: Leetcode
tags: Leetcode
---

﻿Given  _n_  non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

![](http://www.leetcode.com/static/images/problemset/rainwatertrap.png)  
The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.  **Thanks Marcos**  for contributing this image!
<!--more-->
**Example:**

>**Input:** [0,1,0,2,1,0,1,3,2,1,2,1]
**Output:** 6

**Difficulty**:Hard
**Category**:  
<!--more-->
*****

## Analyze
这道收集雨水的题跟之前的那道 [Largest Rectangle in Histogram 直方图中最大的矩形](http://www.cnblogs.com/grandyang/p/4322653.html) 有些类似，但是又不太一样，我们先来看一种方法，这种方法是基于动态规划Dynamic Programming的，我们维护一个一维的dp数组，这个DP算法需要遍历两遍数组，第一遍遍历dp[i]中存入i位置左边的最大值，然后开始第二遍遍历数组，第二次遍历时找右边最大值，然后和左边最大值比较取其中的较小值，然后跟当前值A[i]相比，如果大于当前值，则将差值存入结果，代码如下：

## Solution

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, left_max = 0, right_max = 0;
        vector<int> diff(height.size(), 0);
        
        for(int i = 0; i < height.size(); ++i) {
            diff[i] = left_max;
            left_max = max(left_max, height[i]);
        }
        
        for(int i = height.size() - 1; i >= 0; --i) {
            diff[i] = min(right_max, diff[i]);
            right_max = max(right_max, height[i]);
            if (diff[i] > height[i]) res += diff[i] - height[i];
        }
        return res;
    }
};
```
