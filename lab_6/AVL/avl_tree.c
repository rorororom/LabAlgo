#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

#define MODULE 1000000000

int max(int a, int b) {
    if (a > b)
        return a;

    return b;
}

int height(node* n) {
    if (n == NULL)
        return -1;

    return n->height;
}

node* newNode(int value) {
    node* n = (node*)malloc(sizeof(node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

void redoneHeight(node* n) {
    if (n == NULL)
        return;

    n->height = 1 + max(height(n->left), height(n->right));
}

node* smallRotateRight(node* n) {
    node* nn = n->right;
    n->right = nn->left;
    nn->left = n;

    redoneHeight(n);
    redoneHeight(nn);

    return nn;
}

node* smallRotateLeft(node* n) {
    node* nn = n->left;
    n->left = nn->right;
    nn->right = n;

    redoneHeight(n);
    redoneHeight(nn);

    return nn;
}

int getBalance(node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

node* BalanceTree(node* node) {
    int balance = getBalance(node);

    if (balance == 2) {
        if (getBalance(node->left) < 0) {
            node->left = smallRotateRight(node->left);
            return smallRotateLeft(node);
        } else {
            return smallRotateLeft(node);
        }
    }

    if (balance == -2) {
        if (getBalance(node->right) > 0) {
            node->right = smallRotateLeft(node->right);
            return smallRotateRight(node);
        } else {
            return smallRotateRight(node);
        }
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

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    return BalanceTree(node);
}



int nextvalue(node* root, int value) {
    int result = -1;

    if (root == NULL)
        return result;

    if (root->value == value) {
        return root->value;
    } else if (value < root->value) {
        int flag = nextvalue(root->left, value);
        if (flag != -1) {
            return flag;
        } else {
            return root->value;
        }
    } else {
        return nextvalue(root->right, value);
    }
}

node* FindMinTree(node* root) {
	return root->left ? FindMinTree(root->left) : root;
}

node* RemoveMinTree(node* root)  {
	if(root->left == 0)
		return root->right;
	root->left = RemoveMinTree(root->left);
	return BalanceTree(root);
}

node* RemoveTree(node* root, int value) {
    if(!root)
        return NULL;
	if(value < root->value ) {
		root->left = RemoveTree(root->left, value);

    } else if(value > root->value) {
		root->right = RemoveTree(root->right, value);
    } else {
		node* q = root->left;
		node* r = root->right;
	    root = NULL;

		if(!r)
            return q;
		node* min = FindMinTree(r);

		min->right = RemoveMinTree(r);
		min->left = q;

        return BalanceTree(min);
	}

    return BalanceTree(root);
}

void deleteTree(node* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

