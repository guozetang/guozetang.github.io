---
title: Leetcode 1.Two Sum
date: 2018-05-12 00:38:02
updated: 2018-05-12 00:38:02
categories: Leetcode
tags: Leetcode
---

# Two Sum   
Given an array of integers, return indices of the two numbers such that they add up to a specific target.  
You may assume that each input would have exactly one solution, and you may not use the same element twice.  
Example:  
> Given nums = [2, 7, 11, 15], target = 9,  
> Because nums[0] + nums[1] = 2 + 7 = 9,  
> return [0, 1]. 

**Difficulty**:Easy
**Category**: 
****

## 思路：
### O(n 2 ) runtime, O(1) space – Brute force
如果使用暴力搜索，那么时间复杂度为O(n^2))，这会造成Time Limit Exceeded. 所以需要使用O(n)的算法来实现。  
### O(n) runtime, O(n) space – Hash table
> 1. 先遍历一遍数组，建立HashMap数据
> 2. 第二遍遍历，开始查找，如果找到，则记录下来
<!--more-->
## Solution
Java Solution 1:    

```java  
public class Solution {
    public int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> m = new HashMap<Integer, Integer>();
        int[] res = new int[2];
        for (int i = 0; i < nums.length; ++i) {
            m.put(nums[i], i);
        }
        for (int i = 0; i < nums.length; ++i) {
            int t = target - nums[i];
            if (m.containsKey(t) && m.get(t) != i) {
                res[0] = i;
                res[1] = m.get(t);
                break;
            }
        }
        return res;
    }
}
```
优化： 合并一下两个for循环 
> 思路：查找时，建立索引（Hash查找）或进行排序（二分查找）。本题缓存可在找的过程中建立索引，故一个循环可以求出解（总是使用未使用元素查找使用元素，可以保证每一对都被检索到）。Indexing/ordering is the first step to search questions.  
 
Java Solution 2：  
```java
public class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> m = new HashMap<Integer,Integer>();
        for(int i = 0;i < nums.length;++i) {
            int num = target - nums[i];
            if(m.containsKey(num))
                return new int[]{m.get(num), i };
            m.put(nums[i], i);
        }
        throw new RuntimeException("No two sum solution!");
    }
}
```


