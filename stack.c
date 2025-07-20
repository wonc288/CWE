// Stack (Array-based) - A LIFO (Last-In-First-Out) data structure using an array.
// Supports push, pop, peek, and isEmpty.

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

int peek(Stack* s) {
    if (isEmpty(s)) return -1;
    return s->data[s->top];
}
