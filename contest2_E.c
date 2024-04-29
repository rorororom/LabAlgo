#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MODULE 1000000000

typedef struct node {
    void* value;
    struct node* left;
    struct node* right;
    int height;
} node;

void readAndProcessData(int n, FILE* input, FILE* output);

int main() {
    int n = 0;
    int res = scanf("%d", &n);
    if (res != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    FILE* output = stdout;
    FILE* input  = stdin;

    readAndProcessData(n, input, output);
    return 0;
}

int compareStrings(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
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

node* newNode(void* value) {
    node* n = (node*)malloc(sizeof(node));
    assert(n);

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
    assert(node);

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
        }

        return smallRotateLeft(node);
    }

    if (balance == -2) {
        if (getBalance(node->right) > 0) {
            node->right = smallRotateLeft(node->right);
            return smallRotateRight(node);
        }

        return smallRotateRight(node);

    }
    return node;
}


node* insert(node* node, void* value, size_t size) {
    if (node == NULL)
        return newNode(value);

    if (compareStrings(value, node->value) < 0)
        node->left = insert(node->left, value, size);
    else
        node->right = insert(node->right, value, size);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance == 2 || balance == -2) {
        return BalanceNode(node, balance);
    }

    return node;
}

void* findValue(node* root, void* value, size_t size) {
    if (root == NULL)
        return NULL;

    if (compareStrings(value, root->value) == 0) {
        return root->value;
    } else if (compareStrings(value, root->value) < 0) {
        void* flag = findValue(root->left, value, size);
        if (flag != NULL) {
            return flag;
        } else {
            return root->value;
        }
    } else {
        return findValue(root->right, value, size);
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
        char op = 0; int value = 0;
        int res = scanf(" %c %d", &op, &value);
        if (res != 2) {
            printf("Error: Failed to read input.\n");
            return;
        }

        if (op == '+') {
            if (last_op == '?') {
                value = (value + last_res) % MODULE;
            }
            root = insert(root, &value, sizeof(int));
        } else if (op == '?') {
            void* res = findValue(root, &value, sizeof(int));
            if (res != NULL) {
                int res_value = *(int*)res;
                last_res = res_value;
                printf("%d\n", res_value);
            } else {
                printf("Not found\n");
            }
        }
        last_op = op;
    }
    deleteTree(root);
}



