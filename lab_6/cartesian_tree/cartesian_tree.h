#ifndef DEKARTOVO_TREE_H
#define DEKARTOVO_TREE_H

#include "stdbool.h"

typedef struct node {
    int key;
    int prior;
    int size;
    struct node* left;
    struct node* right;
} node;

typedef struct node* pnode;

void insert(pnode root, pnode newNode);
void erase(pnode node, int key);
pnode createNode(int key);
bool exists(pnode node, int key);
void deleteTree(pnode node);

#endif
