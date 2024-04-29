#ifndef DEKARTOVO_TREE_H
#define DEKARTOVO_TREE_H

struct node {
    int key;
    int prior;
    int size;
    struct node* l;
    struct node* r;
};

typedef struct node *pnode;

void insert(pnode *t, pnode it);
void erase (pnode *t, int key);

#endif
