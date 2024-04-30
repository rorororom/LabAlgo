#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEP 100000
#define MAX_TEST 1000000

#define DEKARTOVO_TREE

#include "../dekartovo_tree/dekartovo_tree.h"

void testing_insert(int* arr, int n, pnode root) {
    for (size_t i = 0; i < n; i++) {
        pnode newnode = createNode(arr[i]);
        if (newnode != NULL) {
            insert(&root, newnode);
        }
    }
}

void testing_delete(int* arr, int n, pnode root) {
    for (size_t i = 0; i < n / 2; i++) {
       if (exists(root, arr[i])) {
            erase(&root, arr[i]);
        }
    }
}

int main() {
    FILE* file_i = fopen("../res/p3_insert.txt", "w");
    if (file_i == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    FILE* file_d = fopen("../res/p3_delete.txt", "w");
    if (file_d == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    for (size_t i = STEP; i <= MAX_TEST; i += STEP) {
        char filename[50];
        sprintf(filename, "../array/test_%zu.txt", i);

        FILE* file = fopen(filename, "r");

        if (file == NULL) {
            printf("Ошибка при создании файла %s\n", filename);
            return 1;
        }

        int* arr = (int*)calloc(i, sizeof(int));
        for (size_t j = 0; j < i; j++) {
            fscanf(file, "%d", &arr[j]);
        }

        double time_insert = 0, time_delete = 0;
        for (int j = 0; j < 5; j++) {
            clock_t start, end;
            pnode root = NULL;

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
