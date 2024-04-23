#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "naive_tree_func.h"

// NST - NAIVE SEARCH TREE

struct Node* NST_NewNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    assert(temp);

    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

struct Node* NST_Insert(struct Node* node, int key) {
    if (node == NULL)
        return NST_NewNode(key);

    if (key < node->key)
        node->left = NST_Insert(node->left, key);
    else if (key > node->key)
        node->right = NST_Insert(node->right, key);

    return node;
}

struct Node* NST_Search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key)
        return NST_Search(root->left, key);

    return NST_Search(root->right, key);
}

struct Node* NST_DeleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = NST_DeleteNode(root->left, key);
    else if (key > root->key)
        root->right = NST_DeleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->key = temp->key;

        root->right = NST_DeleteNode(root->right, temp->key);
    }
    return root;
}

void NST_Delete(struct Node* node) {
    if (node == NULL)
        return;

    NST_Delete(node->left);
    NST_Delete(node->right);

    free(node);
}
