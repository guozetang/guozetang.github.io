---
title: Leetcode 61. Rotate List
date: 2018-11-20 20:09:31
updated: 2018-11-20 20:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a linked list, rotate the list to the right by  _k_  places, where  _k_  is non-negative.

**Example 1:**

> **Input:** 1->2->3->4->5->NULL, k = 2
> **Output:** 4->5->1->2->3->NULL
> **Explanation:**
> rotate 1 steps to the right: 5->1->2->3->4->NULL
> rotate 2 steps to the right: 4->5->1->2->3->NULL

**Example 2:**

> **Input:** 0->1->2->NULL, k = 4
> **Output:** `2->0->1->NULL`
> **Explanation:**
> rotate 1 steps to the right: 2->0->1->NULL
> rotate 2 steps to the right: 1->2->0->NULL
> rotate 3 steps to the right: `0->1->2->NULL`
> rotate 4 steps to the right: `2->0->1->NULL`

**Difficulty**:Medium
**Category**:Linked List, Two Points

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
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) return head;

    int len_list = 1;
    ListNode* p = head;
    while (p->next) {
      p = p->next;
      len_list++;
    }

    k = len_list - k % len_list;

    p->next = head;

    for (int step = 0; step < k; ++step) {
      p = p->next;
    }

    head = p->next;
    p->next = NULL;
    return head;
  }
};
```