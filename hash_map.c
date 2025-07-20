// Hash Map using Chaining - Uses linked lists to handle collisions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

Entry* table[TABLE_SIZE] = { NULL };

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) hash = (hash << 5) + *key++;
    return hash % TABLE_SIZE;
}

void insert(const char *key, int value) {
    unsigned int idx = hash(key);
    Entry *newEntry = malloc(sizeof(Entry));
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = table[idx];
    table[idx] = newEntry;
}

Entry* search(const char *key) {
    unsigned int idx = hash(key);
    Entry *e = table[idx];
    while (e && strcmp(e->key, key) != 0) e = e->next;
    return e;
}
