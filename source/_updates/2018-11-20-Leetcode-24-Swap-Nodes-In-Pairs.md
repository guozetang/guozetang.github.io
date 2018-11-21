---
title: Leetcode 24. Swap Nodes in Pairs
date: 2018-11-20 21:09:31
updated: 2018-11-20 21:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a linked list, swap every two adjacent nodes and return its head.

**Example:**

Given `1->2->3->4`, you should return the list as `2->1->4->3`.

**Note:**

- Your algorithm should use only constant extra space.
- You may  **not**  modify the values in the list's nodes, only nodes itself may be changed.

**Difficulty**:Medium
**Category**:Linked List

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
  ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *left = &dummy, *cur = left->next, *right = cur->next;
    while (right) {
      left->next = right;
      cur->next = right->next;
      right->next = cur;

      left = cur;
      cur = cur->next;
      if (cur != nullptr && cur->next != nullptr)
        right = cur->next;
      else
        right = nullptr;
    }

    return dummy.next;
  }
};
```