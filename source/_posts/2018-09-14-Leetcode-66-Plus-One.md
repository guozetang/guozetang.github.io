---
title: Leetcode 66. Plus One
date: 2018-09-14 15:09:31
updated: 2018-09-14 15:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a  **non-empty**  array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

**Example 1:**
>**Input:** [1,2,3]
**Output:** [1,2,4]
**Explanation:** The array represents the integer 123.

**Example 2:**
>**Input:** [4,3,2,1]
**Output:** [4,3,2,2]
**Explanation:** The array represents the integer 4321.

**Difficulty**:Easy
**Category**:

<!--more-->
******

# Analyze

这道题目是给一个`数字的容器`，每个位置放了一个数字，然后让你将这个容器的`最小位 + 1`之后，处理进位操作之后，输出出来，我们只需要判断`最低位是否为9`，如果为9，那么就处理进位操作，如果不为9，那么就加1之后直接输出出来即可。
******

# Solution

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size();

        for(int i = len - 1; i >= 0; i--) {
            if (digits[i] == 9) digits[i] = 0;
            else {
                digits[i] += 1;
                return digits;
            }
        }

        if (digits.front() == 0 ) digits.insert(digits.begin(), 1);
        return digits;

    }
};
```