#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MODULE 1000000000

typedef struct node {
    int time;
    struct node* left;
    struct node* right;
    int height;
} node;

void readAndProcessData(int n, FILE* input, FILE* output);


int main() {
    int n;
    scanf("%d", &n);

    FILE* output = stdout;
    FILE* input  = stdin;

    readAndProcessData(n, input, output);
    return 0;
}

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

node* newNode(int time) {
    node* n = (node*)malloc(sizeof(node));
    n->time = time;
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

node* smallRotateRight(node* node) {
    assert(node);
    struct node* node_r = node->right;
    node->right = node_r->left;
    node_r->left = node;

    redoneHeight(node);
    redoneHeight(node_r);

    return node_r;
}

node* smallRotateLeft(node* node) {
    struct node* node_l = node->left;
    node->left = node_l->right;
    node_l->right = node;

    redoneHeight(node);
    redoneHeight(node_l);

    return node_l;
}

int getBalance(node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

node* BalanceNode(node* node, int balance) {
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


node* Insert(node* node, int time) {
    if (node == NULL)
        return newNode(time);

    if (time < node->time)
        node->left = Insert(node->left, time);
    else
        node->right = Insert(node->right, time);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance == 2 || balance == - 2) {
        return BalanceNode(node, balance);
    }

    return node;
}



int nextTime(node* root, int time) {
    int result = -1;

    if (root == NULL)
        return result;

    if (root->time == time) {
        return root->time;
    } else if (time < root->time) {
        int flag = nextTime(root->left, time);
        if (flag != -1) {
            return flag;
        } else {
            return root->time;
        }
    } else {
        return nextTime(root->right, time);
    }
}

void deleteTree(node* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

void readAndProcessData(int n, FILE* input, FILE* output) {
    node* root = NULL;
    char last_op = ' ';
    int last_res = -1;
    for (int i = 0; i < n; i++) {
        char op;
        int time;
        scanf(" %c %d", &op, &time);
        if (op == '+' ) {
            if (last_op == '?') {
                time = (time + last_res) % MODULE;
            }
            root = Insert(root, time);
        }
        else if (op == '?') {
            int res = nextTime(root, time);
            last_res = res;
            printf("%d\n", res);
        }
        last_op = op;
    }
    deleteTree(root);
}


