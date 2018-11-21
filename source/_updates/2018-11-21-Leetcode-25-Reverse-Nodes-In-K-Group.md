---
title: Leetcode 25. Reverse Nodes in k-Group
date: 2018-11-21 06:09:31
updated: 2018-11-21 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a linked list, reverse the nodes of a linked list  _k_  at a time and return its modified list.

_k_  is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of  _k_  then left-out nodes in the end should remain as it is.

**Example:**

Given this linked list:  `1->2->3->4->5`

For  _k_  = 2, you should return:  `2->1->4->3->5`

For  _k_  = 3, you should return:  `3->2->1->4->5`

**Note:**

- Only constant extra memory is allowed.
- You may not alter the values in the list's nodes, only nodes itself may be changed.

**Difficulty**:Medium
**Category**:Linked List

<!-- more -->

------------

# Analyze

------------

# Solution

**Soulution 1**：错误的解决方案，理解错误题目含义，以为是翻转前面n个节点

```cpp
class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *start = &dummy, *prev = start->next, *cur = prev->next;

    int count = 0;
    while (cur && count < k) {
      prev->next = cur->next;
      cur->next = start->next;
      start->next = cur;

      count++;
      cur = prev->next;
    }
    return dummy.next;
  }
};
```

**Soulution 2**：递归

```cpp
class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k <= 1) return head;
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *start = &dummy, *prev = start->next, *cur = prev->next;

    ListNode* p = prev;
    int len = 0;
    while (p) {
      len++;
      p = p->next;
    }
    if (k > len) return head;

    std::cout << len << std::endl;

    int count = 1;
    while (cur) {
      prev->next = cur->next;
      cur->next = start->next;
      start->next = cur;
      count++;

      cur = prev->next;
      if (count % k == 0) {
        count++;
        if (count + k > len + 1) return dummy.next;
        start = prev;
        if (prev->next != nullptr) {
          prev = prev->next;
          cur = prev->next;
        }
      }
    }
    return dummy.next;
  }
};
```

优化一下代码：

```cpp
class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k < 2) return head;
    int len = 0;
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *start = &dummy, *prev = start->next, *cur = prev->next;
    ListNode *p = prev;
    
    // Get the len of the List
    while (p) {
      len++;
      p = p->next;
    }
    if (k > len) return head;

    int count = 1;
    while (cur) {
      prev->next = cur->next;
      cur->next = start->next;
      start->next = cur;
      count++;

      cur = prev->next;
      if(count % k == 0) {
        count++;
        if (count + k > len+1) return dummy.next;
        start = prev;
        if (prev->next != nullptr) {
          prev = prev->next;
          cur = prev->next;
        }
      }
    }
    return dummy.next;
  }
};
```
