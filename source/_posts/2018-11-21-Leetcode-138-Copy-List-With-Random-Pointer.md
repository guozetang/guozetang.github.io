---
title: Leetcode 138. Copy List with Random Pointer
date: 2018-11-21 06:09:31
updated: 2018-11-21 06:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

**Difficulty**:Medium
**Category**:HashTable, Linked List

<!-- more -->

------------

# Analyze

这道题目看上去是比较麻烦的，因为你不能够同时完成所有内容的`Deep copy`, 因为每个节点的`random`是不知道的，所以是不能够在第一次拷贝的时候就完全完成拷贝。可以分成下面几个步骤完成。

- 在当前节点中，拷贝一个节点包含了`Next`节点以及`int label`的数值，然后将这个节点添加到当前现在的list里面去，最后在将其分出来。
- 完成`rondom`节点内容的拷贝工作
- 分解两个List

------------

# Solution

```cpp
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
 public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    RandomListNode dummy(-1);
    RandomListNode *new_cur = &dummy;
    // Copy the Next node and label
    for (RandomListNode *cur = head; cur != nullptr;) {
      RandomListNode *node = new RandomListNode(cur->label);
      node->next = cur->next;
      cur->next = node;
      cur = node->next;
    }

    // Copy the random node
    for (RandomListNode *cur = head; cur != nullptr;) {
      // Copy the random node
      if (cur->random != nullptr) cur->next->random = cur->random->next;
      cur = cur->next->next;
    }

    for (RandomListNode *cur = head; cur != nullptr;) {
      new_cur->next = cur->next;
      new_cur = new_cur->next;
      cur->next = cur->next->next;
      cur = cur->next;
    }
    return dummy.next;
  }
};
```