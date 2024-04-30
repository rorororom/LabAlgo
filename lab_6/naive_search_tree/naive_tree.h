#ifndef NAIVE_TREE_H
#define NAIVE_TREE_H

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// NST - NAIVE SEARCH TREE

struct Node* NST_Insert    (struct Node* node, int key);
struct Node* NST_Search    (struct Node* root, int key);
struct Node* NST_DeleteNode(struct Node* root, int key);
void         NST_Delete    (struct Node* node);

#endif
