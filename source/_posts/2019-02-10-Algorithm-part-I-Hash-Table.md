---
title: Algorithm part I Hash Table
date: 2019-02-10 12:07:23
updated: 2019-02-10 12:07:23
categories: 
- [Notes]
tags: Node
notshow: true
mathjax: true
top:
---

# Hash Table

There are four part we need to talk about the Hash-Table: `Hash Function`, `Separate Chaining`, `Linear Probing` and `Context`

> Hash tables, a data structure that achieves constant-time performance for core symbol table operations, provided that search keys are standard data types or simply defined. Then we consider several fundamental (and useful) examples of symbol-table clients.

**Basic Plan For Hash-Table**

Save items in a `key-indexed table` (index is a function of the key).

Hash function. Method for computing array index from key.

`Hash("it") = 3`

The issues for this part:

* We need to computing the hash function.
* Equality test: Method for checking whether tow keys are equal.
* Collision resolution: Algorithm and data structure to handle tow keys that hash to the same array index.

Classic space-time tradeoff.
* No space limitation: Travial hash function with key as index.
* No time limitation: Travial collision resolution with sequential search.
* Space and time limitations: Hashing(The real world.)

# Hash function

- Efficiently computable