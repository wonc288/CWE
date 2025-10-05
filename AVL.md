This write up is for the AVLanch programming challenge

I had heard of an AVL tree before, a tree data structure that auto-balances itself, but I had never made one before, only a basic binary search tree. Unlike the other programming challenges, this one used a .txt file, which makes parsing the file a bit simpler. I used a guide from GeeksforGeeks to code the majority of the actual AVL tree logic. In order to help parse the data I used chatGPT to create a parser function, then rewrote it to make sense to me.

```C
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    unsigned char data;
    struct Node *left, *right;
    int height;
} Node;

int getHeight(Node *n) { return n ? n->height : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

Node *createNode(int key, unsigned char data) {
    Node *node = malloc(sizeof(Node));
    if (!node) exit(1);
    node->key = key;
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(Node *n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node *insert(Node *node, int key, unsigned char data, char *out, size_t *out_len, int *rotations, int *appended) {
    if (!node)
        return createNode(key, data);

    if (key < node->key)
        node->left = insert(node->left, key, data, out, out_len, rotations, appended);
    else if (key > node->key)
        node->right = insert(node->right, key, data, out, out_len, rotations, appended);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Rotation logic
    if (balance > 1 && key < node->left->key) { // LL
        (*rotations)++;
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) { // RR
        (*rotations)++;
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) { // LR
        (*rotations) += 2;
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) { // RL
        (*rotations) += 2;
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }

    // Append char once if double rotation occurred
    if ((*rotations) >= 2 && !*appended) {
        out[*out_len] = data;
        (*out_len)++;
        out[*out_len] = '\0';
        *appended = 1;
    }

    return node;
}

int main(void) {
    FILE *f = fopen("nodes.txt", "r");
    if (!f) {
        printf("Error: could not open nodes.txt\n");
        return 1;
    }

    Node *root = NULL;
    char out[1024] = {0};
    size_t out_len = 0;
    int key;
    char ch;

    while (fscanf(f, "%d,%c", &key, &ch) == 2) {
        int rotations = 0;
        int appended = 0;
        root = insert(root, key, ch, out, &out_len, &rotations, &appended);
    }
    fclose(f);

    printf("CWE{%s}\n", out);
    return 0;
}

```

After running the code I was able to print the flag

CWE{Z;/ER6M3t~;4_6'`lSC,9%%Cx24jQ*~]L~,r\I1N72+mQ*z=+lox}
