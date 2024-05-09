#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl_tree.h"

#define MODULE 1000000000

static int max(int a, int b) {
    if (a > b)
        return a;

    return b;
}

static int height(node* n) {
    if (n == NULL)
        return VAL_NULL;

    return n->height;
}

static node* newNode(int value) {
    node* newNode = (node*)malloc(sizeof(node));
    assert(newNode);

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

static void redoneHeight(node* node) {
    if (node == NULL)
        return;

    node->height = 1 + max(height(node->left), height(node->right));
}

static node* smallRotateLeft(node* root) {
    node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    redoneHeight(root);
    redoneHeight(newRoot);

    return newRoot;
}

static node* smallRotateRight(node* root) {
    node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    redoneHeight(root);
    redoneHeight(newRoot);

    return newRoot;
}

static int getBalance(node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

static node* BalanceTree(node* node) {
    int balance = getBalance(node);

    redoneHeight(node);

    if (balance == 2) {
        if (getBalance(node->left) < 0) {
            node->left = smallRotateLeft(node->left);
        }
        return smallRotateRight(node);
    }

    if (balance == -2) {
        if (getBalance(node->right) > 0) {
            node->right = smallRotateRight(node->right);
        }
        return smallRotateLeft(node);
    }

    return node;
}

node* Insert(node* node, int value) {
    if (node == NULL)
        return newNode(value);

    if (value < node->value)
        node->left = Insert(node->left, value);
    else
        node->right = Insert(node->right, value);

    return BalanceTree(node);
}

static node* FindMinTree(node* root) {
	return root->left ? FindMinTree(root->left) : root;
}

static node* RemoveMinTree(node* root)  {
	if (root->left == NULL)
		return root->right;

	root->left = RemoveMinTree(root->left);

	return BalanceTree(root);
}

node* RemoveTree(node* root, int value) {
    if (!root) {
        return NULL;
    }

    if (value < root->value) {
        root->left = RemoveTree(root->left, value);
    } else if (value > root->value) {
        root->right = RemoveTree(root->right, value);
    } else {
        node* leftSubtree = root->left;
        node* rightSubtree = root->right;
        free(root);

        if (!rightSubtree) {
            return leftSubtree;
        }

        node* minRight = FindMinTree(rightSubtree);
        minRight->right = RemoveMinTree(rightSubtree);
        minRight->left = leftSubtree;

        return BalanceTree(minRight);
    }

    return BalanceTree(root);
}

void DeleteTree(node* root) {
    if (root == NULL)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    free(root);
}
