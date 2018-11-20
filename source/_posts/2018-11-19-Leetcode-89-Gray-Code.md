---
title: Leetcode 89. Gray Code
date: 2018-11-19 19:09:31
updated: 2018-11-19 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer  _n_  representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

**Example 1:**

> **Input:** 2
**Output:** `[0,1,3,2]`
**Explanation:**
00 - 0
01 - 1
11 - 3
10 - 2
>
> For a given _n_, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.
>
>00 - 0
10 - 2
11 - 3
01 - 1

**Example 2:**

> **Input:** 0
> **Output:** `[0]
> **Explanation:** We define the gray code sequence to begin with 0.A gray code sequence of _n_ has size = 2n, which for _n_ = 0 the size is 20 = 1. Therefore, for _n_ = 0 the gray code sequence is [0].`

**Difficulty**:Medium
**Category**:Backtracking

<!-- more -->

------------

# Analyze

这到题目是关于格雷码的，难点也就是理解格雷码的转换过程。格雷码的转换过程可以如下图所示：

![](/images/in-post/2018-11-19-Leetcode-89-Gray-Code/2018-11-19-20-34-15.png)

图片来自于：[[LeetCode] Gray Code 格雷码](http://www.cnblogs.com/grandyang/p/4315649.html)

这个图片清晰的说明了格雷码的生成规律，随着`n`的变化，前面`n-1`之前就存在的项目都是在前面加上0,这些项目的数值是不会变化的，而后面的是和前面的对称相反的，所以在这里进行处理就可以得到完整的格雷码转换之后的vector了。

------------

# Solution

```cpp
class Solution {
 public:
  vector<int> grayCode(int n) {
    vector<int> res;
    res.emplace_back(0);
    for (int i = 0; i < n; ++i) {
      int n = res.size();
      for (int j = n - 1; j >= 0; --j) {
        res.emplace_back(res[j] | 1 << i);
      }
    }
    return res;
  }
};
```