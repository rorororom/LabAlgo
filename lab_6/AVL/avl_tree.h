#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
    int height;
} node;

const int NULL_HEIGHT = -1; // отсутствие высоты у узла

node* Insert(node* node, int value);
node* RemoveTree(node* root, int value);
void DeleteTree(node* root);

#endif
