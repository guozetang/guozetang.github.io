---
title: Leetcode 86. Partition List
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a linked list and a value  _x_, partition it such that all nodes less than  _x_  come before nodes greater than or equal to  _x_.

You should preserve the original relative order of the nodes in each of the two partitions.

**Example:**

> **Input:** head = 1->4->3->2->5->2, _x_ = 3
> **Output:** 1->2->2->4->3->5

**Difficulty**:Medium
**Category**:Linked List, Two Pointers

<!-- more -->

------------

# Analyze

------------

# Solution

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
  ListNode* partition(ListNode* head, int x) {
    ListNode left_dummy(-1);
    ListNode right_dummy(-1);

    auto left_cur = &left_dummy;
    auto right_cur = &right_dummy;

    for (ListNode* cur = head; cur; cur = cur->next) {
      if (cur->val < x) {
        left_cur->next = cur;
        left_cur = left_cur->next;
      } else {
        right_cur->next = cur;
        right_cur = right_cur->next;
      }
    }

    left_cur->next = right_dummy.next;
    right_cur->next = NULL;
    return left_dummy.next;
  }
};
```