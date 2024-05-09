#ifndef NAIVE_TREE_H
#define NAIVE_TREE_H

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// NST - NAIVE SEARCH TREE

void insert(Node* root, int key);
void deleteNode(Node* root, int key);
void deleteTree(Node* node);
Node* newNode(int key);

#endif
