---
title: Leetcode 19. Remove Nth Node From End of List
date: 2018-11-20 21:09:31
updated: 2018-11-20 21:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a linked list, remove the  _n_-th node from the end of list and return its head.

**Example:**

> Given linked list: **1->2->3->4->5**, and **_n_ = 2**.
> After removing the second node from the end, the linked list becomes **1->2->3->5**.

**Note:**

Given  _n_  will always be valid.

**Follow up:**

Could you do this in one pass?

**Difficulty**:Medium
**Category**:Two Points

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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head->next == NULL) return NULL;
    ListNode *left = head, *right = head;
    for (int i = 0; i < n; ++i) right = right->next;
    if (right == NULL) return head->next;
    while (right->next) {
      right = right->next;
      left = left->next;
    }
    left->next = left->next->next;
    return head;
  }
};
```

**Solution 2**

```cpp
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *left = &dummy, *right = &dummy;

    for (int i = 0; i < n; i++) {
      right = right->next;
    }

    while (right->next) {
      right = right->next;
      left = left->next;
    }
    ListNode* tmp = left->next;
    left->next = left->next->next;
    delete tmp;
    return dummy.next;
  }
};
```