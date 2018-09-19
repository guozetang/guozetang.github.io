---
title: Algorithm Introduce
date: 2018-09-18 02:09:31
updated: 2018-09-18 02:09:31
categories: Algorithm
tags: Algorithm
top:
---

# Algorithm Introduce

**What is a good Algorithm?** (Cite from: Brian C. Dean )

- Always terminates and produces **correct** output.
- Make **efficient**  use of computational resources. 
 Minimizes running time, memory usage, processors, bandwidth, power consumed, heat produced.
- Is **simple** to describe, understand, analyze, implement, and debug

<!--more-->

**For example:**
Linear search:

```cpp
for (int i = 0; i<N; i++) {
	if (target == A[i]) {found it!}
}
```

Binary search:

```cpp
low = 0; high = N-1;
while (low <= high) {
	mid = (low + high) / 2;
	if (target == A[mid]) { found it! }
	if (target > A[mid]) low = mid+1;
	else high = mid-1;
}

```

> Linear search: O(N) time.
> Binary search: O(log N) time.

******

## Running time

What is the  `Linear search: O(N) time.` meaning in the above? We usually use `asymptotic notation` to describe how running  time scales with input size.

> O(f(N)) means “upper-bounded by a constant times f(N) as N grows large”. Just like, if the input of size is N, then the take about nN machine instructions, then we can say it runs in O(N) time.

There are other two symbol which are used for discribe the running time scales with input size.

- Ω() provides an asymptotic lower bound.
- Θ() means both a lower and upper bound.

### Arrays, Listed lists

#### Arrays

After you define the size of the arrays, you can change the size of the array at the running time. You just can allocate for a new arrays at the running time and copy the old one to the new one.


```cpp
/* Statically defined (size known at compile time) */
int A[100];
int B[100] = {1, 2, 3};
/* Dynamically allocated at run time */
int *C = (int *)malloc(100 * sizeof(int));
int *D = new int[100];
/* A[], C[], and D[] filled with garbage until initialized */
/* Remember pointers can be used as arrays -- e.g., C[7] */
/* Don’t forget to free memory for C and D... */
free (C);
delete [] D;
```

Analyze:

- Retrieve or modify any element in O(1) time.
- Insert or delete in middle of list: O(N) time.
- Insert or delete from ends: O(1) time

#### Linked Lists


```cpp
/* In C, typically
use “typedef struct...” */
struct Node {
    int payload;
    Node *next;
}
int list_length(Node *n)
{
    int count = 0;
    while (n != NULL) {
    count++;
    n = n->next;
}
    return count;
}
```

TODO:  
- [ ] Task1:Write the doubly linked lists.
- [ ] Write a list which maintain a pointer to the first and last element.

Analyze:

- Seek to any position in list: O(N) time.
- Then insert or delete element: O(1) time.
- Insert or delete from ends: O(1) time.

#### Circular Arrays, Queues

![](/images/in-post/2018-09-18-CPSC2120-Algorithm-Introduce/2018-09-19-10-05-38.png)

```cpp
void enqueue(int x)
{
  A[front] = x;
  front = (front+1) % N;
}
int dequeue(void)
{
  int result = A[back];
  back = (back+1) % N;
  return result;
}
```

#### Stacks

![](/images/in-post/2018-09-18-CPSC2120-Algorithm-Introduce/2018-09-19-10-07-33.png)

```cpp
void push(int x)
{
  A[top++] = x;
}
int pop(void)
{
  return A[--top];
}

void what_does_this_do(int n)
{
  if (n==0) return;
  printf (“%d\n”, n);
  what_does_this_do(n-1);
  printf (“%d\n”, n);
}
```

### Arrays Vs Lists Example

We can use a example(From Brian. Dean) to introduce the running time abou the Arrays and Lists.

In the file `studens.txt` have a lot of students information about their name. Like this follow:

```
Sebastian Valentin
Jeffrey Wang
Jacob William
***
```

**Question:**

Write for me a program in C++ that takes as input a list of names, and prints out each name that appears in the list multiple times.

**Arrays Solution:**

```cpp
#include <iostream>
#include <fstream>
using namespace std;

string *name;
int N; // how many elements we've actually read from the file
int allocated; // how much memory we've allocated

int num_occurences(string s)
{
  int count = 0;
  for (int i=0; i<N; i++) if (name[i] == s) count++;
  return count;
}

int main (void)
{
  string fname, lname;
  ifstream fin("students.txt");

  name = new string[4];
  allocated = 4;  // start with array of size 4
  // (this is somewhat arbitrary; any small constant would be fine)
  
  while (fin >> fname >> lname) {

    if (num_occurences(fname) == 1)  // O(n) time
      cout << fname << "\n";

    // Check if we need to transfer our array into a new larger array
    if (N == allocated) {
      string *newarray = new string[allocated * 2];
      for (int i=0; i<N; i++) newarray[i] = name[i];
      delete [] name; // old array not needed any more; free it...
      name = newarray;
      allocated = allocated * 2;
      // now name points to the new array, which is twice as big and
      // contains all the N elements we've read so far...
    }
    name[N++] = fname;
  }
  return 0;
}

```



**List Solution**

```cpp
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
  string name;
  Node *next;
  Node (string s, Node *n) { name = s; next = n; }
};

int num_occurences(Node *head, string s)
{
  int count = 0;
  Node *n = head;
  while (n != NULL) {
    if (n->name == s) count++;
    n = n->next;
  }
  return count;
}

int main (void)
{
  string fname, lname;
  ifstream fin("students.txt");
  Node *head = NULL;
  
  while (fin >> fname >> lname) {
    if (num_occurences(head, fname) == 1)  // O(n)
      cout << fname << "\n";
    head = new Node(fname, head);
  }
  return 0;
}
```

