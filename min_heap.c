// Min Heap - A binary heap where the smallest value is at the root.
// Supports insert and extract-min operations.

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct MinHeap {
    int size;
    int data[MAX];
} MinHeap;

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapifyUp(MinHeap *h, int i) {
    while (i > 0 && h->data[i] < h->data[(i-1)/2]) {
        swap(&h->data[i], &h->data[(i-1)/2]);
        i = (i-1)/2;
    }
}

void heapifyDown(MinHeap *h, int i) {
    int left = 2*i + 1, right = 2*i + 2, smallest = i;
    if (left < h->size && h->data[left] < h->data[smallest]) smallest = left;
    if (right < h->size && h->data[right] < h->data[smallest]) smallest = right;
    if (smallest != i) {
        swap(&h->data[i], &h->data[smallest]);
        heapifyDown(h, smallest);
    }
}

void insert(MinHeap *h, int val) {
    if (h->size == MAX) return;
    h->data[h->size] = val;
    heapifyUp(h, h->size);
    h->size++;
}

int extractMin(MinHeap *h) {
    if (h->size == 0) return -1;
    int min = h->data[0];
    h->data[0] = h->data[--h->size];
    heapifyDown(h, 0);
    return min;
}
