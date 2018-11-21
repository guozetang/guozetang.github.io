---
title: Leetcode 82. Remove Duplicates from Sorted List II
date: 2018-11-20 21:09:31
updated: 2018-11-20 21:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only  _distinct_  numbers from the original list.

**Example 1:**

> **Input:** 1->2->3->3->4->4->5
> **Output:** 1->2->5

**Example 2:**

> **Input:** 1->1->1->2->3
> **Output:** 2->3

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
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *prev = &dummy, *cur = head;

    while (cur) {
      bool dupl = false;
      while (cur->next != NULL && cur->val == cur->next->val) {
        dupl = true;
        ListNode* temp = cur;
        cur = cur->next;
        delete temp;
      }

      if (dupl) {
        ListNode* temp = cur;
        cur = cur->next;
        delete temp;
        continue;
      }

      prev->next = cur;
      prev = prev->next;
      cur = cur->next;
    }
    prev->next = cur;
    return dummy.next;
  }
};
```
