#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cartesian_tree.h"

int Rand() {
    return rand() % 1000000007;
}

pnode createNode(int key) {
    pnode newNode = (pnode)malloc(sizeof(struct node));
    if (newNode) {
        newNode->key = key;
        newNode->prior = Rand();
        newNode->size = 1;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

static void update_size(pnode node) {
    if (node)
        node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

static void split(pnode node, int key, pnode left, pnode right) {
    if (!node)
        left = right = NULL;
    else if (key < node->key)
        split(node->left, key, left, node->left), right = node;
    else
        split(node->right, key, node->right, right), left = node;
    update_size(node);
}

void insert(pnode root, pnode newNode) {
    if (!root)
        root = newNode;
    else if (newNode->prior > root->prior)
        split(root, newNode->key, newNode->left, newNode->right), root = newNode;
    else
        insert(newNode->key < root->key ? root->left : root->right, newNode);

    update_size(root);
}


static void merge(pnode node, pnode left, pnode right) {
    if (!left || !right)
        node = left ? left : right;
    else if (left->prior > right->prior)
        merge(left->right, left->right, right), node = left;
    else
        merge(right->left, left, right->left), node = right;
    update_size(node);
}


void erase(pnode node, int key) {
    if (!node)
        return;
    if (node->key == key) {
        pnode temp = node;
        merge(node, node->left, node->right);
        free(temp);
    } else {
        erase(key < node->key ? node->left : node->right, key);
    }
    update_size(node);
}


bool exists(pnode node, int key) {
    if (!node)
        return false;
    if (key == node->key)
        return true;
    else if (key < node->key)
        return exists(node->left, key);
    else
        return exists(node->right, key);
}

void deleteTree(pnode node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        free(node);
    }
}


