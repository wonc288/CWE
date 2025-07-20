// Doubly Linked List - A linear list where each node points to both previous and next nodes.
// Supports insertion, deletion, search, and bidirectional traversal.

#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* createDNode(int data) {
    DNode* newNode = malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

DNode* insertAtHead(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (head)
        head->prev = newNode;
    newNode->next = head;
    return newNode;
}

DNode* insertAtTail(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (!head) return newNode;
    DNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

DNode* deleteNode(DNode* head, int key) {
    DNode* temp = head;
    while (temp && temp->data != key)
        temp = temp->next;
    if (!temp) return head;
    if (temp->prev)
        temp->prev->next = temp->next;
    else
        head = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    free(temp);
    return head;
}

void printForward(DNode* head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
