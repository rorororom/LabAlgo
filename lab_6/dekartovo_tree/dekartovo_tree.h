#ifndef DEKARTOVO_TREE_H
#define DEKARTOVO_TREE_H

#include "stdbool.h"

typedef struct node {
    int key;
    int prior;
    int size;
    struct node* l;
    struct node* r;
} node;

typedef struct node *pnode;

void insert(pnode *t, pnode it);
void erase (pnode *t, int key);
pnode createNode(int key);
bool exists(pnode t, int key);
void deleteTree(pnode t);

#endif
