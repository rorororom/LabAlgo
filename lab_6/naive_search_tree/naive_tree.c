#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "naive_tree.h"

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    assert(node);

    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

void insert(Node* root, int key) {
    assert(root);

    Node* new_node = newNode(key);
    Node* parent = NULL;
    Node* current = root;

    while (current != NULL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    new_node->parent = parent;
    if (parent == NULL) {
        root = new_node;
    } else if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

static Node* findNode(Node* root, int key) {
    while (root != NULL && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

static Node* minValueNode(Node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

void deleteNode(Node* root, int key) {
    Node* node_to_delete = findNode(root, key);

    if (node_to_delete == NULL) return;

    Node* successor = NULL;
    Node* replacement = NULL;
    if (node_to_delete->left == NULL || node_to_delete->right == NULL) {
        successor = node_to_delete;
    } else {
        successor = minValueNode(node_to_delete->right);
    }

    if (successor->left != NULL) {
        replacement = successor->left;
    } else {
        replacement = successor->right;
    }

    if (replacement != NULL) {
        replacement->parent = successor->parent;
    }

    if (successor->parent == NULL) {
        root = replacement;
    } else if (successor == successor->parent->left) {
        successor->parent->left = replacement;
    } else {
        successor->parent->right = replacement;
    }

    if (successor != node_to_delete) {
        node_to_delete->key = successor->key;
    }

    free(successor);
}

void deleteTree(Node* node) {
    while (node != NULL) {
        if (node->left != NULL) {
            struct Node* temp = node->left;
            node->left = temp->right;
            temp->right = node;
            node = temp;
        } else {
            struct Node* temp = node->right;
            free(node);
            node = temp;
        }
    }
}
