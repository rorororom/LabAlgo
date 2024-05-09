#ifndef SKIP_LIST_H
#define SKIP_LIST_H

typedef struct Node {
    int key;
    int value;
    struct Node **forward;
} Node;

typedef struct SkipList {
    int level;
    Node *header;
} SkipList;

SkipList *createSkipList();
void insert(SkipList *skipList, int key);
void erase (SkipList *skipList, int key);
void display(SkipList *skipList);
void destroySkipList(SkipList *skipList);

#endif
