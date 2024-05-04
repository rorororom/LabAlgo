#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAX_LEVEL 100000

#include "skip_list.h"

Node *createNode(int level, int key) {
    assert(level >= 0);

    Node *newNode    = (Node *)malloc(sizeof(Node));
    assert(newNode);

    newNode->key     = key;

    newNode->forward = (Node **)calloc(level + 1, sizeof(Node *));
    assert(newNode->forward);

    return newNode;
}

SkipList *createSkipList() {
    SkipList *skipList = (SkipList *)malloc(sizeof(SkipList));
    assert(skipList);

    skipList->level    = 0;
    skipList->header   = createNode(MAX_LEVEL, INT_MIN);

    return skipList;
}

int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }

    return level;
}

void insert(SkipList *skipList, int key) {
    assert(skipList);

    Node *update[MAX_LEVEL + 1];
    Node *current = skipList->header;

    for (int i = skipList->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->key == key) {
        return;
    }

    int level = randomLevel();

    if (level > skipList->level) {
        for (int i = skipList->level + 1; i <= level; i++) {
            update[i] = skipList->header;
        }
        skipList->level = level;
    }

    Node *newNode = createNode(level, key);

    for (int i = 0; i <= level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}


void erase(SkipList *skipList, int key) {
    assert(skipList);

    Node *update[MAX_LEVEL + 1];
    Node *current = skipList->header;

    for (int i = skipList->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->key == key) {
        for (int i = 0; i <= skipList->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }

        free(current->forward);
        free(current);

        while (skipList->level > 0 && skipList->header->forward[skipList->level] == NULL) {
            skipList->level--;
        }
    }
}

Node *search(SkipList *skipList, int key) {
    assert(skipList);

    Node *current = skipList->header;

    for (int i = skipList->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    if (current != NULL && current->key == key) {
        return current;
    } else {
        return NULL;
    }
}

void display(SkipList *skipList) {
    printf("Skip List:\n");
    for (int i = 0; i <= skipList->level; i++) {
        Node *node = skipList->header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("(%d) ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
}

void destroySkipList(SkipList *skipList) {
    assert(skipList);

    Node *current = skipList->header->forward[0];
    while (current != NULL) {
        Node *next = current->forward[0];

        free(current->forward);
        free(current);

        current = next;
    }

    free(skipList->header);
    free(skipList);
}

// int main() {
//     SkipList *skipList = createSkipList();
//
//     insert(skipList, 3);
//     display(skipList);
//     insert(skipList, 6);
//     display(skipList);
//     insert(skipList, 7);
//     display(skipList);
//     insert(skipList, 9);
//     display(skipList);
//     insert(skipList, 1);
//     display(skipList);
//     insert(skipList, 11);
//     display(skipList);
//     insert(skipList, 12);
//     display(skipList);
//     insert(skipList, 13);
//     display(skipList);
//     insert(skipList, 14);
//     display(skipList);
//     insert(skipList, 15);
//     display(skipList);
//     insert(skipList, 16);
//     display(skipList);
//     insert(skipList, 17);
//     display(skipList);
//     insert(skipList, 18);
//     display(skipList);
//     insert(skipList, 19);
//     display(skipList);
//     insert(skipList, 20);
//     display(skipList);
//     insert(skipList, 21);
//     display(skipList);
//     insert(skipList, 22);
//     display(skipList);
//     insert(skipList, 23);
//     display(skipList);
//     insert(skipList, 24);
//     display(skipList);
//
//
//     display(skipList);
//
//     erase(skipList, 7);
//
//     display(skipList);
//     erase(skipList, 15);
//
//     display(skipList);
//
//     Node *searchResult = search(skipList, 6);
//     if (searchResult != NULL) {
//         printf("\nElement with key 6 found, value: %d\n", searchResult->value);
//     } else {
//         printf("\nElement with key 6 not found\n");
//     }
//
//     destroySkipList(skipList);
//
//     return 0;
// }
