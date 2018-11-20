---
title: Leetcode 2.Add Two Numbers
date: 2018-05-12 00:41:38
updated: 2018-05-12 00:41:38
categories: Leetcode 
tags: Leetcode
---

# Question

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

> Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
> Output: 7 -> 0 -> 8

**Difficulty**:Medium
**Category**:Linked List, Math

<!-- more -->

*****

# Solution

**Solution 1:Java**

```java
public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        int carry = 0;
        ListNode lResult = new ListNode(0);
        ListNode lPointer = lResult;
        while (l1 != null || l2 != null) {
            int n1 = 0, n2 = 0;
            if (l1 != null) {
                n1 = l1.val;
                l1 = l1.next;
            }
            if (l2 != null) {
                n2 = l2.val;
                l2 = l2.next;
            }
            int temp = n1 + n2 + carry;
            carry = temp / 10;
            temp %= 10;
            lPointer.next = new ListNode(temp);
            lPointer = lPointer.next;
        }
        if (carry > 0) {
            lPointer.next = new ListNode(carry);
        }
        return lResult.next;
    }
}
```

思路：数字进位问题，该位有效值为值%10，进位值为值/10。可以使用一个变量记录进位值。

**Solution 2: C++**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* res = new ListNode(0);
    ListNode* res_point = res;
    int carry = 0;

    while (l1 != NULL || l2 != NULL) {
      int n1 = 0, n2 = 0;
      if (l1) {
        n1 = l1->val;
        l1 = l1->next;
      }
      if (l2) {
        n2 = l2->val;
        l2 = l2->next;
      }
      int temp = n1 + n2 + carry;
      carry = temp / 10;
      temp %= 10;
      res_point->next = new ListNode(temp);
      res_point = res_point->next;
    }
    if (carry > 0) {
      res_point->next = new ListNode(carry);
    }
    return res->next;
  }
};
```
