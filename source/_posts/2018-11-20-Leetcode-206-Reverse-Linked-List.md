---
title: Leetcode 206. Reverse Linked List
date: 2018-11-19 06:09:31
updated: 2018-11-19 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Reverse a singly linked list.

**Example:**

> **Input:** 1->2->3->4->5->NULL
> **Output:** 5->4->3->2->1->NULL

**Difficulty**:Easy
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
  ListNode* reverseList(ListNode* head) {
    if (!head) return head;
    ListNode dummy(-1);
    dummy.next = head;

    ListNode* const start = &dummy;
    ListNode* prev = head;
    ListNode* cur = head->next;
    while (cur) {
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
