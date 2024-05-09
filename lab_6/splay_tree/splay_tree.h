#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} node;

struct node* Insert(struct node* root, int key);
struct node* Delete(struct node* root, int key);
void Free(struct node* root);

#endif
