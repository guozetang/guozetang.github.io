---
title: Leetcode 121. Best Time to Buy and Sell Stock
date: 2018-10-28 21:09:31
updated: 2018-10-28 21:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Say you have an array for which the  _i_th  element is the price of a given stock on day  _i_.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

**Example 1:**
> **Input:** [7,1,5,3,6,4]
> **Output:** 5
> **Explanation:** Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than buying price.

**Example 2:**

> **Input:** [7,6,4,3,1]
> **Output:** 0
> **Explanation:** In this case, no transaction is done, i.e. max profit = 0.

<!-- more -->

------------

# Solution

```cpp
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;
    int preMin = prices[0], curMax = 0, maxPrice = 0;
    for (int i = 0; i < prices.size(); ++i) {
      if (prices[i] > curMax) {
        curMax = prices[i];
        maxPrice = max(maxPrice, curMax - preMin);
      }

      if (prices[i] < preMin) {
        curMax = 0;
        preMin = prices[i];
      }
    }
    return maxPrice;
  }
};
```