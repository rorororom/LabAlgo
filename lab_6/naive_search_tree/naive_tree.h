#ifndef NAIVE_TREE_H
#define NAIVE_TREE_H

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// NST - NAIVE SEARCH TREE

Node* createNode(int key) ;
Node* insert(Node* root, int key);
Node* search(Node* root, int key);
Node* deleteNode(Node* root, int key);
void deleteTree(Node* root);

#endif
