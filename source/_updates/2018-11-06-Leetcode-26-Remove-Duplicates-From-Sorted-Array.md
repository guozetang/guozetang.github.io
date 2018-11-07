---
title: Leetcode 26. Remove Duplicates from Sorted Array
date: 2018-11-06 06:09:31
updated: 2018-11-06 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a sorted array  _nums_, remove the duplicates  [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm)  such that each element appear only  _once_  and return the new length.

Do not allocate extra space for another array, you must do this by  **modifying the input array  [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)**  with O(1) extra memory.

**Example 1:**

> Given _nums_ = **[1,1,2]**,
> Your function should return length = **`2`**, with the first two elements of _`nums`_ being **`1`** and **`2`** respectively.
> It doesn't matter what you leave beyond the returned length.

**Example 2:**
> Given _nums_ = **[0,0,1,1,1,2,2,3,3,4]**,
> Your function should return length = **`5`**, with the first five elements of _`nums`_ being modified to **`0`**, **`1`**, **`2`**, **`3`**, and **`4`** respectively.
> It doesn't matter what values are set beyond the returned length.

**Clarification:**

Confused why the returned value is an integer but your answer is an array?
Note that the input array is passed in by  **reference**, which means modification to the input array will be known to the caller as well.
Internally you can think of this:

> // **nums** is passed in by reference. (i.e., without making a copy)
> int len = removeDuplicates(nums);
> // any modification to **nums** in your function would be known by the caller.
> // using the length returned by your function, it prints the first **len** elements.
> for (int i = 0; i < len; i++) {
>     print(nums[i]);
> }

<!-- more -->

---------

# Solution

```cpp
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    if (nums.size() <= 1) return nums.size();
    int pre = 0, cur = 1, ctr = 1;
    while (cur < nums.size()) {
      if (nums[pre] == nums[cur] && ctr == 0)
        cur++;
      else {
        if (nums[pre] == nums[cur])
          ctr = 0;
        else {
          nums[++pre] = nums[cur++];
          ctr = 1;
        }
      }
    }
    return pre + 1;
  }
};
```

![](/images/in-post/2018-11-06-Leetcode-26-Remove-Duplicates-From-Sorted-Array/2018-11-06-21-30-12.png)

上面的解决方案有这样几个问题：

- nums.size() <= 1 不应该将长度为1的情况归入和0一样的处理方式，这样不够清晰明了。


对上面的解答思路进行优化：

**Solution 2**

```cpp
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int index = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[index] != nums[i]) {
        nums[++index] = nums[i];
      }
    }
    return index + 1;
  }
};
```

**Solution 3**

使用了STL里面的函数来快速的完成：

```cpp
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) { return distance(nums.begin(), unique(nums.begin(), nums.end())); }
};
```