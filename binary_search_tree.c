// Binary Search Tree - A binary tree where each left child is smaller and each right child is larger than the root.
// Supports insert, search, delete, and traversal.

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insert(TreeNode* root, int data) {
    if (!root) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

TreeNode* search(TreeNode* root, int key) {
    if (!root || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

TreeNode* findMin(TreeNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

TreeNode* delete(TreeNode* root, int key) {
    if (!root) return NULL;
    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
        if (!root->left) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
