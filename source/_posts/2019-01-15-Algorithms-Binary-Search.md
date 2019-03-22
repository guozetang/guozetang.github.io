---
title: Leetcode Algorithms. Binary Search
date: 2019-01-15 21:52:04
updated: 2019-01-15 21:52:04
categories: 
- [Leetcode]
tags: Leetcode
notshow: true
top:
---

> All the pictures in this post are coming from the video: 
> [花花酱 LeetCode Binary Search - 刷题找工作 SP5](https://www.youtube.com/watch?v=v57lNF2mb_s) 

# Summary

The feature for the Binary Search is: **Fast, Fast, Fast**. O(log(n))

# What is Binary Search?

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-21-57-59.png)

The requirment for the Binary Search is the **sorted input data**.

Each node needs to make decision go to left or right. For the Binary Search method, the input data will include three partition: **Mid, left array, right array**.

- If the mid number is less than the target number, then go to right array to find the target number.
- If the mid number is larger than the target number, then go to left array to find the target number.
  
When you go to the left or right way, you can choose the recursive function or not recursive function to solve it.

The answer for this question is that the last mid point is the target number which you want to find if there is a target number in the array. If there is no target number in the array, when you find the last mid number and then you can return false or use this number to do something.

<!-- more -->

-----------

# Why we need Binary Search.

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-22-06-06.png)

There are some states for the above picture:

- The O(eval) is the time to compare the mid number with the target number and the search space need to move to left part or right part. It may be: O(1), O(n), or O(logn).

**SO, you can use the input dataset range to choose which mothod you can use to solve this problem.** There are two tips which you can use to think which method is good for you to solve this problem.

<!-- TODO: Wathc the video to add the note for how we can choose a method to solve the problem. -->

-----------

# Template

## Template 1: Unique and sorted elements

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-22-15-33.png)

Include the left data, but not include the right side.

```python
def binary_search(1,r):
  while l < r:
    m = 1 + (r-1) // 2
    if f(m): return m #optional
    if g(m):
      r = m
    else:
      l + m + 1
  return l #or not find, return the min number
```

As the above picture, if the input element is unique and sorted, then we can easily use this template to deal with these similar problems. Like the example 1.

**If the Input data's element is not unique. And it have repetitive numbers.**

## Template 2: Repetitive and sorted elements

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-22-34-55.png)

The lower_bound function will return the first index of i, such that A[i] >= x, So, when you find it, you need to check out if this A[i] may not = x. If the index > len, then there is no number > this. 

**Example**

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-22-44-18.png)

**Leetcode 69**

It is not way to find the real number to fit the requrtment. So, we can find the number the first time bigger than the input.

![](/images/in-post/2019-01-15-Algorithms-Binary-Search/2019-01-15-22-47-51.png)
