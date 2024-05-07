#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *left, *right, *parent;
} Node;

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

void insert(Node** root, int key) {
    Node* z = newNode(key);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL) {
        *root = z;  // Дерево было пустым
    } else if (key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

Node* findNode(Node* root, int key) {
    while (root != NULL && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

Node* minValueNode(Node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

void deleteNode(Node** root, int key) {
    Node* z = findNode(*root, key);

    if (z == NULL) return;  // Узел не найден

    Node* y = NULL;
    Node* x = NULL;
    if (z->left == NULL || z->right == NULL) {
        y = z;
    } else {
        y = minValueNode(z->right);
    }

    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != NULL) {
        x->parent = y->parent;
    }

    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != z) {
        z->key = y->key;
    }

    free(y);
}

void deleteTree(Node* node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

int main() {
    const int numInsertions = 10000;
    const int numDeletions = 500;

    FILE* file = fopen("../array/tetsA.txt", "r");
    if (file == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    int* arr = (int*)malloc(numInsertions * sizeof(int));

    for (int i = 0; i < numInsertions; i++) {
        int res = fscanf(file, "%d", &arr[i]);
        if (res != 1) {
            printf("не считалось\n");
            return 1;
        }
    }
    fclose(file);

    clock_t start, end;
    double cpu_time_used_insert = 0, cpu_time_used_delete = 0;

    Node* root = NULL;
    for (size_t k = 0; k < 1; k++) {
    root = NULL;
        start = clock();
        for (int i = 0; i < numInsertions; i++) {
            // printf("%d ", i);
            insert(&root, arr[i]);
        }
        end = clock();
        cpu_time_used_insert += ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < numDeletions; i++) {
            deleteNode(&root, arr[i]);
        }
        end = clock();
        cpu_time_used_delete += ((double)(end - start)) / CLOCKS_PER_SEC;

        deleteTree(root);
    }

    printf("Время выполнения вставки: %f секунд\n", cpu_time_used_insert / 1);
    printf("Время выполнения удаления: %f секунд\n", cpu_time_used_delete / 1);

    free(arr);

    return 0;
}
