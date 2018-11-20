---
title: Leetcode 92. Reverse Linked List II
date: 2018-11-20 06:09:31
updated: 2018-11-20 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Reverse a linked list from position  _m_  to  _n_. Do it in one-pass.

**Note:** 1 ≤  _m_  ≤  _n_  ≤ length of list.

**Example:**

> **Input:** 1->2->3->4->5->NULL, _m_ = 2, _n_ = 4
> **Output:** 1->4->3->2->5->NULL

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
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode dummy(-1);
    dummy.next = head;

    ListNode* prev = &dummy;
    for (int i = 0; i < m - 1; ++i) {
      prev = prev->next;
    }

    ListNode* const start = prev;

    prev = start->next;
    ListNode* cur = prev->next;
    for (int i = m; i < n; ++i) {
      prev->next = cur->next;
      cur->next = start->next;
      start->next = cur;
      cur = prev->next;
    }
    return dummy.next;
  }
};
```

------------

# Leetcode Question Summary


------------
