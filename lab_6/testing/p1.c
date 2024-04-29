#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../naive_search_tree/naive_tree.h"

#define SIZE       100000
#define SIZE_S     1000000
#define CNT_DELETE 50000
#define CNT_TEST   5

void runTest(int* arr, double* time_insert, double* time_delete, int size) {
    clock_t start, end;
    struct Node* root = NULL;

    start = clock();

    for (size_t i = 0; i < SIZE; ++i) {
        int key = arr[i];
        root = NST_Insert(root, key);
    }

    end = clock();
    (*time_insert) = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < CNT_DELETE; ++i) {
        int key = arr[i];
        root = NST_DeleteNode(root, key);
    }
    end = clock();
    (*time_delete) = ((double)(end - start)) / CLOCKS_PER_SEC;

    NST_Delete(root);
}


int main() {
    int* arr = (int*)calloc(SIZE_S, sizeof(int));
    assert(arr);

    for (size_t i = 0; i < SIZE_S; i++) {
        int res = scanf("%d", &arr[i]);
        if (res != 1) {
            printf("не удалось считать число\n");
            return 1;
        }
    }

    double tests_res_insert = 0, tests_res_delete = 0;

    double time_insert = 0, time_delete = 0;
    for (size_t i = 0; i < 1; ++i) {
        runTest(arr, &time_insert, &time_delete, SIZE_S);
        tests_res_insert += time_insert;
        tests_res_delete += time_delete;
    }

    printf("insert = %f\n delete = %f\n", tests_res_insert / 5, tests_res_delete / 5);
    return 0;
}
