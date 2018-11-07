---
title: Leetcode 4. Median of Two Sorted Arrays
date: 2018-05-11 16:26:46
updated: 2018-05-11 16:26:46
categories: Leetcode
tags: Leetcode
---

# Question

There are two sorted arrays nums1 and nums2 of size m and n respectively.  

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:  
> nums1 = [1, 3]    
> nums2 = [2]  
> The median is 2.0  

Example 2:  
> nums1 = [1, 2]  
> nums2 = [3, 4]  
> The median is (2 + 3)/2 = 2.5 

**Difficulty**:Hard
**Category**:
****
<!--more-->

----------

# Analyze

-----------

# Solution

**Java Solution:**

```java
public class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        int l = (m + n + 1) >> 1;
        int r = (m + n + 2) >> 1;
        return (getkth(nums1, 0, nums2, 0, l) + getkth(nums1, 0, nums2, 0, r)) / 2.0;
    }

    public double getkth(int[] A, int aStart, int[] B, int bStart, int k) {
        if (aStart == A.length) return B[bStart + k - 1];
        if (bStart == B.length) return A[aStart + k - 1];
        if (k == 1) return Math.min(A[aStart], B[bStart]);
        int aMid = Integer.MAX_VALUE, bMid = Integer.MAX_VALUE;
        if (aStart + k/2 - 1 < A.length) aMid = A[aStart + k/2 - 1];
        if (bStart + k/2 - 1 < B.length) bMid = B[bStart + k/2 - 1];
        if (aMid < bMid) 
            return getkth(A, aStart + k/2, B, bStart,       k - k/2);
        else 
            return getkth(A, aStart,       B, bStart + k/2, k - k/2);
    }
}
```

**C++ Solution 1**

```cpp
class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int total = nums1.size() + nums2.size();

    if (total % 2 == 1) {
      return findMedianth(nums1, 0, nums2, 0, total / 2 + 1);
    } else {
      return (findMedianth(nums1, 0, nums2, 0, total / 2) +
              findMedianth(nums1, 0, nums2, 0, total / 2 + 1)) /
             2;
    }
  }

  double findMedianth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
    if (nums1.size() - i > nums2.size() - j)
      return findMedianth(nums2, j, nums1, i, k);
    if (nums1.size() == i) return nums2[j + k - 1];

    if (k == 1) return min(nums1[i], nums2[j]);

    int point_1 = min(int(nums1.size()), i + k / 2);
    int point_2 = j + k - point_1 + i;

    if (nums1[point_1 - 1] < nums2[point_2 - 1])
      return findMedianth(nums1, point_1, nums2, j, k - (point_1 - i));
    else if (nums1[point_1 - 1] > nums2[point_2 - 1])
      return findMedianth(nums1, i, nums2, point_2, k - (point_2 - j));
    else
      return nums1[point_1 - 1];
  }
};
```