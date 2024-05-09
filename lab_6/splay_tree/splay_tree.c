#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

#include "splay_tree.h"

static void* calloc_with_check(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    assert(ptr != NULL);
    return ptr;
}

static struct node* NewNode(int key) {
    struct node* new_node = (struct node*)calloc_with_check(1, sizeof(struct node));
    new_node->left = new_node->right = NULL;
    new_node->key = key;
    return new_node;
}

static struct node* RightRotate(struct node* node) {
    assert(node);
    struct node* newRoot = node->left;

    node->left = newRoot->right;
    newRoot->right = node;

    return newRoot;
}

static struct node* LeftRotate(struct node* node) {
    assert(node);
    struct node* newRoot = node->right;

    node->right = newRoot->left;
    newRoot->left = node;

    return newRoot;
}

static struct node* Splay(struct node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    static struct node* header = NULL;
    if (header == NULL)
        header = NewNode(key);
    struct node* leftMax = header;
    struct node* rightMin = header;
    struct node* leftTail = header;
    struct node* rightTail = header;

    while (root->key != key) {
        if (root->key > key) {
            if (root->left == NULL)
                break;

            if (root->left->key > key) {
                root = RightRotate(root);
                if (root->left == NULL)
                    break;
            }

            rightTail->left = root;
            rightTail = root;
            root = root->left;
        } else {
            if (root->right == NULL)
                break;

            if (root->right->key < key) {
                root = LeftRotate(root);
                if (root->right == NULL)
                    break;
            }

            leftTail->right = root;
            leftTail = root;
            root = root->right;
        }
    }

    leftTail->right = root->left;
    rightTail->left = root->right;
    root->left = header->right;
    root->right = header->left;
    free(header);

    return root;
}

static struct node* InsertRight(struct node* root, struct node* newNode) {
    newNode->right = root;
    newNode->left = root->left;
    root->left = NULL;
    return newNode;
}

static struct node* InsertLeft(struct node* root, struct node* newNode) {
    newNode->left = root;
    newNode->right = root->right;
    root->right = NULL;
    return newNode;
}

struct node* Insert(struct node* root, int key) {
    if (root == NULL)
        return NewNode(key);

    root = Splay(root, key);

    if (root->key == key)
        return root;

    struct node* newNode = NewNode(key);

    if (root->key < key) {
        return InsertLeft(root, newNode);
    } else {
        return InsertRight(root, newNode);
    }
}

struct node* Delete(struct node* root, int key) {
    if (root == NULL)
        return NULL;

    root = Splay(root, key);

    if (root->key != key)
        return root;

    if (root->left == NULL) {
        struct node* newRoot = root->right;
        free(root);
        return newRoot;
    }

    if (root->right == NULL) {
        struct node* newRoot = root->left;
        free(root);
        return newRoot;
    }

    struct node* maxLeft = root->left;
    while (maxLeft->right != NULL)
        maxLeft = maxLeft->right;

    root->left = Splay(root->left, maxLeft->key);

    root->left->right = root->right;

    struct node* newRoot = root->left;
    free(root);
    return newRoot;
}


static void Search(struct node** root, int key) {
    assert(root);

    if (*root == NULL)
        return;

    *root = Splay(*root, key);
}


void Free(struct node* root) {
    while (root != NULL) {
        struct node* temp = root;

        if (root->left != NULL) {
            root = root->left;
            temp->left = NULL;
        } else {
            root = root->right;
            temp->right = NULL;
        }
        free(temp);
    }
}

