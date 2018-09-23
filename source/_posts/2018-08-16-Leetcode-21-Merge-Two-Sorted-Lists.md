---
title: Leetcode 21. Merge Two Sorted Lists
date: 2018-08-16 13:42:10
updated: 2018-08-16 13:42:10
categories: Leetcode
tags: Leetcode
---

# Question

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:
> Input: 1->2->4, 1->3->4  
> Output: 1->1->2->3->4->4  

**Difficulty**:Easy
**Category**:  
<!--more-->
*****

# Solution

```c++
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* mergelist = new ListNode(-1), *cur = mergelist;
        while(l1 && l2){
            if (l1->val < l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return mergelist->next;
    }
};
```
