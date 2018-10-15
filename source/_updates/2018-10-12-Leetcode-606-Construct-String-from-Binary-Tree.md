---
title: Leetcode 606. Construct String from Binary Tree
date: 2018-10-12 14:09:31
updated: 2018-10-12 14:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

![](/images/in-post/2018-10-12-Leetcode-606-Construct-String-from-Binary-Tree/2018-10-14-02-17-11.png)

<!--more-->

---

# Analyze

这道题目输入是一个二叉树，输出要求是一个字符串，这个字符串要表示出一些二叉树的属性。使用递归的处理方式，有以下几种情况。

- 如果根节点为空，那么return一个空值
- 如果有根节点，然后左右孩子都为空的话，那么就返回这一个根节点的值
- 如果有根节点，左孩子为空， 右孩子不为空的话，那么就返回 `()(右孩子)`
- 如果有根节点，左孩子不为空， 右孩子为空的话，那么就返回 `(左孩子)`

只要能够在不引起歧义的情况下能够表示出来二叉树的属性就好了。

---

# Solution

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    string tree2str(TreeNode* t) {
      if (!t) return "";
      string res = to_string(t->val);
      string left = tree2str(t->left), right = tree2str(t->right);
      if (left == "" && right == "") { return res;}
      if (left == "") {return res+"()"+"("+ right +")";}
      if (right == "") {return res+"(" + left + ")";}
      return res+"(" + left + ")" + "(" + right+")";
    }
};
```