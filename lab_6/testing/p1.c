#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define STEP 100000
#define MAX_TEST 1000000

#include "../naive_search_tree/naive_tree.h"

void testing_insert(int* arr, int n, struct Node* root) {
    assert(arr);
    root = insert(root, arr[0]);
    for (size_t i = 1; i < n; i++) {
        insert(root,  arr[i]);
    }
}

void testing_delete(int* arr, int n, struct Node* root) {
    assert(arr);
    assert(root);

    for (size_t i = 0; i < n / 2; i++) {
        deleteNode(root, arr[i]);
    }
}

int main() {
    FILE* file_i = fopen("../res/p1_insert_2.txt", "w");
    if (file_i == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    FILE* file_d = fopen("../res/p1_delete_2.txt", "w");
    if (file_d == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    for (size_t i = MAX_TEST; i <= 1 * MAX_TEST; i += STEP) {
        char filename[50];
        sprintf(filename, "../array/tetsA.txt");

        FILE* file = fopen(filename, "r");

        if (file == NULL) {
            printf("Ошибка при создании файла %s\n", filename);
            return 1;
        }

        int* arr = (int*)calloc(i, sizeof(int));
        for (size_t j = 0; j < i; j++) {
            int res = fscanf(file, "%d", &arr[j]);
            if (res != 1) {
                printf("не считалось\n");
                return 1;
            }
        }

        double time_insert = 0, time_delete = 0;
        for (int j = 0; j < 5; j++) {
            printf("j = %d\n", j);
            clock_t start, end;
            struct Node* root = NULL;

            start = clock();
            testing_insert(arr, i, root);
            end = clock();
            time_insert += ((double)(end - start)) / CLOCKS_PER_SEC;

            start = clock();
            testing_delete(arr, i, root);
            end = clock();
            time_delete += ((double)(end - start)) / CLOCKS_PER_SEC;
            deleteTree(root);
            free(root);
        }

        fprintf(file_i, "%zu %f\n", i, time_insert / 5);
        fprintf(file_d, "%zu %f\n", i, time_delete / 5);

        fclose(file);
    }

    fclose(file_i);
    fclose(file_d);

    return 0;
}
