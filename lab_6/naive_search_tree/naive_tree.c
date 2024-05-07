#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "naive_tree.h"

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

void insert(Node** root, int key) {
    Node* z = newNode(key);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL) {
        *root = z;  
    } else if (key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

Node* findNode(Node* root, int key) {
    while (root != NULL && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

Node* minValueNode(Node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

void deleteNode(Node** root, int key) {
    Node* z = findNode(*root, key);

    if (z == NULL) return;

    Node* y = NULL;
    Node* x = NULL;
    if (z->left == NULL || z->right == NULL) {
        y = z;
    } else {
        y = minValueNode(z->right);
    }

    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != NULL) {
        x->parent = y->parent;
    }

    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != z) {
        z->key = y->key;
    }

    free(y);
}

void deleteTree(Node* node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}
