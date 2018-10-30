---
title: Leetcode 539. Minimum Time Difference
date: 2018-10-26 19:09:31
updated: 2018-10-26 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum  **minutes**  difference between any two time points in the list.

**Example 1:**  

**Input:** ["23:59","00:00"]
**Output:** 1

**Note:**  

1. The number of time points in the given list is at least 2 and won't exceed 20000.
2. The input time is legal and ranges from 00:00 to 23:59.

<!-- more -->

----------

# Solution

```cpp
class Solution {
 public:
  int findMinDifference(vector<string>& timePoints) {
    int min;
    vector<int> times;
    for (string t : timePoints) {
      int idx = t.find_last_of(':');
      string hour = t.substr(0, idx);
      string minutes = t.substr(idx + 1, t.size() - idx - 1);
      int time = std::stoi(hour) * 60 + std::stoi(minutes);
      times.emplace_back(time);
    }
    std::sort(times.begin(), times.end());
    for (auto i : times) std::cout << "TIME:" << i << std::endl;
    min = (1440 - times[times.size() - 1]) + times[0];
    for (int i = 1; i < times.size(); ++i) {
      int tmp = abs(times[i - 1] - times[i]);
      if (!tmp) return 0;
      min = tmp < min ? tmp : min;
    }

    return min;
  }
};
```