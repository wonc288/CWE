// Queue (Array-based) - A FIFO (First-In-First-Out) structure using a circular array.
// Supports enqueue, dequeue, isEmpty, and isFull.

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Queue {
    int data[MAX];
    int front, rear, size;
} Queue;

void init(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

int isFull(Queue* q) {
    return q->size == MAX;
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
    q->size++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue empty\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}
