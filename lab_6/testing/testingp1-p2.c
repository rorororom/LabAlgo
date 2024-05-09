#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// #define NAIVE
#define AVL

#define STEP     100000
#define MAX_TEST 1000000

#ifdef NAIVE
#include "../naive_search_tree/naive_tree.h"
#else
#include "../AVL/avl_tree.h"
#endif

int main() {
    const int numInsertions = 1000000;
    const int numDeletions = 500000;

    int* arr = (int*)malloc(numInsertions * sizeof(int));
    assert(arr);

    srand(time(NULL));
    for (int i = 0; i < numInsertions; i++) {
        arr[i] = rand();
    }

    clock_t start, end;
    double cpu_time_used_insert = 0, cpu_time_used_delete = 0;

#ifdef NAIVE
    Node* root = NULL;
#else
    node* root = NULL;
#endif
    for (size_t k = 0; k < 5; k++) {
    root = NULL;
        start = clock();
        for (int i = 0; i < numInsertions; i++) {
#ifdef NAIVE
            insert(root, arr[i]);
#else
            root = Insert(root, arr[i]);
#endif
        }
        end = clock();
        cpu_time_used_insert += ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < numDeletions; i++) {
#ifdef NAIVE
            deleteNode(root, arr[i]);
#else
        root = RemoveTree(root, arr[i]);
#endif
        }
        end = clock();
        cpu_time_used_delete += ((double)(end - start)) / CLOCKS_PER_SEC;

#ifdef NAIVE
        deleteTree(root);
#else
        DeleteTree(root);
#endif
    }

    printf("Время выполнения вставки: %f секунд\n", cpu_time_used_insert / 5);
    printf("Время выполнения удаления: %f секунд\n", cpu_time_used_delete / 5);

    free(arr);

    return 0;
}
