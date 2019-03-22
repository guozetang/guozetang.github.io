---
title: 面试题：使用一个stack实现Queue
date: 2018-11-20 06:09:31
updated: 2018-11-20 06:09:31
categories: Interview
tags: Interview
notshow: 
top:
---

# Question

You are given a Stack data structure that supports standard push and pop operations.
You need to implement Queue data structure using one Stack instances.

![](/images/in-post/2018-11-21-Interview-Implement-Queue-By-Stack/2018-11-21-12-43-44.png)

Picture From:[Implement Queue using One Stack in Java (Recursive Implementation)](http://javabypatel.blogspot.com/2016/11/implement-queue-using-one-stack-in-java.html)

<!-- more -->

------------

# Analyze

实现队列，有这样两个函数操作：

enQueue() 压栈操作:

- Push the element to the Stack.

deQueue() 出栈操作: 

- Pop all the elements from Main Stack recursively until Stack item count is equal to 1.
- If Stack item count = 1, Pop item from Stack, Print it & Return.

Push all popped element back to Stack as shown below.
![](/images/in-post/2018-11-21-Interview-Implement-Queue-By-Stack/2018-11-21-13-02-51.png)

------------

# Solution

```cpp
// Implementing queue using a single stack

#include <stdio.h>
#define SIZE 10
int stack[10];
int top = -1;

int pop() {
  if (top != -1) return stack[top--];
}
void push(int data) {
  if (top < SIZE) stack[++top] = data;
}
void enqueue(int data) { push(data); }

// 使用递归实现出栈操作
int dequeue() {
  if (top == 0) return pop();
  int data = pop();
  int value = dequeue();
  push(data);
  return value;
}

int main(void) {
  int i;

  // Enqueue
  enqueue(1);
  enqueue(2);
  enqueue(3);
  enqueue(4);
  for (i = 0; i <= top; i++) printf("%d ", stack[i]);
  printf("\n");

  // Dequeue
  printf("Dequeue --> %d\n", dequeue());
  printf("Dequeue --> %d\n", dequeue());
  for (i = 0; i <= top; i++) printf("%d ", stack[i]);
  printf("\n");

  return 0;
}
```