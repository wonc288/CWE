# How to Reverse a Linked List

```C
#include<stdio.h>
#include<sidlib.h>
/*Linked List structure
  typedef struct Node* {
    int val;
    struct Node* next;
  }
*/
Node* ReverseList(Node* head) {
  struct Node* next;
  struct Node* cur = head;
  struct Node* prev = head;

  while(cur != NULL) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  return prev;
}
```
