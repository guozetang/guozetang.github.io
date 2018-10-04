---
title: Algorithm Introduce 2 - Abstract Data types and Hash Tables
date: 2018-10-05 02:09:31
updated: 2018-09-18 02:09:31
categories: Algorithm
tags: Algorithm
top:
---

# Abstract Data Type

What is the abstract data type? **Specification** of a data structure in terms of the operations it needs to support.

> Just a concrete(具体化) approach for **implementation** of a data structure that fulfills these requiremnts.

# Queues (FIFO behavior)

Sometimes, we need a structure which can do these two things.

- **Insert** a new key k into the structure
- **Remove** the least-recently-inserted key from the structure.

![](/images/in-post/2018-10-05-CPSC2120-Algorithm-Abstract-Data-TypeHashtable/2018-10-04-09-55-05.png)

But, how can we use the bacis structure `arrays, list, stacks` to implement the queues. Firstly, we can't use the `stacks` to implement it. So, we try to implement the queues by `arrays` and `list`.

1. Circular array
![](/images/in-post/2018-10-05-CPSC2120-Algorithm-Abstract-Data-TypeHashtable/2018-10-04-10-17-06.png)

```cpp
class Queue{
 public:
  Queue();
  ~Queue();
  void insert(int key);
  int remove(void);
 private:
  int *A;
  int front, back, N;
}

int Queue::remove(void) {
  int result = A[back];
  back = (back+1) % N;
  return result;
}

int Queue::insert(int x) {
  A[front] = x;
  front = (front+1) % N;
}

```

2. Linked list
![](/images/in-post/2018-10-05-CPSC2120-Algorithm-Abstract-Data-TypeHashtable/2018-10-04-10-41-41.png)

```c
// A C program to demonstrate linked list based implementation of queue 
#include <stdlib.h> 
#include <stdio.h> 
// A linked list (LL) node to store a queue entry
struct QNode {
  int key;
  struct QNode *next;
};

// The queue, front stores the front node of LL and rear stores ths
// last node of LL
struct Queue {
  struct QNode *front, *rear;
};

// A utility function to create a new linked list node.
struct QNode *newNode(int k) {
  struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
  temp->key = k;
  temp->next = NULL;
  return temp;
}

// A utility function to create an empty queue
struct Queue *createQueue() {
  struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
  q->front = q->rear = NULL;
  return q;
}

// The function to add a key k to q
void enQueue(struct Queue *q, int k) {
  // Create a new LL node
  struct QNode *temp = newNode(k);

  // If queue is empty, then new node is front and rear both
  if (q->rear == NULL) {
    q->front = q->rear = temp;
    return;
  }

  // Add the new node at the end of queue and change rear
  q->rear->next = temp;
  q->rear = temp;
}

// Function to remove a key from given queue q
struct QNode *deQueue(struct Queue *q) {
  // If queue is empty, return NULL.
  if (q->front == NULL) return NULL;

  // Store previous front and move front one node ahead
  struct QNode *temp = q->front;
  q->front = q->front->next;

  // If front becomes NULL, then change rear also as NULL
  if (q->front == NULL) q->rear = NULL;
  return temp;
}
// Driver Program to test anove functions
int main() {
  struct Queue *q = createQueue();
  enQueue(q, 10);
  enQueue(q, 20);
  deQueue(q);
  deQueue(q);
  enQueue(q, 30);
  enQueue(q, 40);
  enQueue(q, 50);
  struct QNode *n = deQueue(q);
  if (n != NULL) printf("Dequeued item is %d", n->key);
  return 0;
}

```

---

## Queues Example

### Question: Given N numbers, do two of them sum to 42

We can find the number which is equal to `42-X` for each number X. There are two steps for this question.
- **Sort** the numbers. )
- **For each number** X in the array, use `Binary search` to see if `42-X` is also present in the array.

<<-------------TODO:--Not Finshed--------------->>