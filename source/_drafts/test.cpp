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