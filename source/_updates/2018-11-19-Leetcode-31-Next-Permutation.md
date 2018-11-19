---
title: Leetcode 31. Next Permutation
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Implement  **next permutation**, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be  **[in-place](http://en.wikipedia.org/wiki/In-place_algorithm)**  and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

`1,2,3`  →  `1,3,2`  
`3,2,1`  →  `1,2,3`  
`1,1,5`  →  `1,5,1`

**Difficulty**:Medium
**Category**:Array  

<!-- more -->

------------

# Analyze

这一道题目，需要找到排列中的下一个顺序（从小到大），如果当前已经是最大的一个排列方式的话，那么下一个就跳转到最小的排列方式。两种情况：

- 如果这不是最大的一个排列，那么找到需要交换元素的两个值，交换元素之后，再进行反转，算法如下图所示：
- 如果这已经是最大的排列的话，那么直接反所有的元素就可以了。

**下一个排列算法流程**
![](/images/in-post/2018-11-19-Leetcode-31-Next-Permutation/2018-11-19-14-22-46.png)

图片来自有：[《Leetcode 题解》](https://github.com/soulmachine/leetcode) 第19页

------------

# Solution

**Solution 1**

```cpp
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    unsigned len = nums.size() - 1;

    // Find an element from the right to left.
    for (int i = len - 1; i >= 0; --i) {
      if (nums[i + 1] > nums[i]) {
        for (int j = len; j > i; --j) {
          if (nums[j] > nums[i]) {
            swap(nums[j], nums[i]);
            reverse(nums.begin() + i + 1, nums.end());
            return;
          }
        }
      }
    }

    // If there are increate order from left to right.
    reverse(nums.begin(), nums.end());
    return;
  }
};
```

**Solution 1**： 稍微更加简洁的代码，来自有 [[LeetCode] Next Permutation 下一个排列](http://www.cnblogs.com/grandyang/p/4428207.html)

```cpp
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2, j = n - 1;
    while (i >= 0 && nums[i] >= nums[i + 1]) --i;
    if (i >= 0) {
      while (nums[j] <= nums[i]) --j;
      swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
  }
};
```