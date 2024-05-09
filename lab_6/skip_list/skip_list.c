#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAX_LEVEL 100000

#include "skip_list.h"

static Node *createNode(int level, int key) {
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

static int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }

    return level;
}

void insert(SkipList *skipList, int key) {
    assert(skipList);

    static Node *update[MAX_LEVEL + 1];
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

    static Node *update[MAX_LEVEL + 1];
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

static Node *search(SkipList *skipList, int key) {
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
