// Singly Linked List - A linear collection of nodes where each node points to the next.
// Supports insertion, deletion, search, and traversal.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertHead(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

Node* insertTail(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head) return newNode;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

int search(Node* head, int key) {
    while (head) {
        if (head->data == key) return 1;
        head = head->next;
    }
    return 0;
}

Node* deleteNode(Node* head, int key) {
    if (!head) return NULL;
    if (head->data == key) {
        Node* temp = head->next;
        free(head);
        return temp;
    }
    Node* curr = head;
    while (curr->next && curr->next->data != key)
        curr = curr->next;
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = temp->next;
        free(temp);
    }
    return head;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
