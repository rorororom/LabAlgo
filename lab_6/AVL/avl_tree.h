#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
    int height;
} node;

node* Insert(node* node, int value);
node* RemoveTree(node* root, int value);

#endif