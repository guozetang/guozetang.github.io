---
title: Leetcode 83. Remove Duplicates from Sorted List
date: 2018-11-20 20:09:31
updated: 2018-11-20 20:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a sorted linked list, delete all duplicates such that each element appear only  _once_.

**Example 1:**

> **Input:** 1->1->2
> **Output:** 1->2

**Example 2:**

> **Input:** 1->1->2->3->3
> **Output:** 1->2->3

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
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head) return head;
    ListNode* prev = head;
    ListNode* cur = head->next;

    while (cur) {
      if (prev->val == cur->val) {
        prev->next = cur->next;
      } else {
        prev = cur;
      }
      cur = cur->next;
    }
    return head;
  }
};
```