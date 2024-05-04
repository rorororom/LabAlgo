#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEP 100000
#define MAX_TEST 1000000


#include "../skip_list/skip_list.h"

void testing_insert(int* arr, int n, struct SkipList* skipList) {
    for (size_t i = 0; i < n; i++) {
        insert(skipList, arr[i]);
    }
}

void testing_delete(int* arr, int n, struct SkipList* skipList) {
    for (size_t i = 0; i < n / 2; i++) {
        // printf("%zu %d\n", i, arr[i]);
        erase(skipList, arr[i]);
    }
}

int main() {
    FILE* file_i = fopen("../res/p7_insert.txt", "w");
    if (file_i == NULL) {
        printf("ошинбос\n");
        return 1;
    }

    FILE* file_d = fopen("../res/p7_delete.txt", "w");
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

        srand(time(NULL));
        double time_insert = 0, time_delete = 0;
        for (int j = 0; j < 5; j++) {
            clock_t start, end;
            SkipList* skipList = createSkipList();

            start = clock();
            testing_insert(arr, i, skipList);
            end = clock();
            time_insert += ((double)(end - start)) / CLOCKS_PER_SEC;

            start = clock();
            testing_delete(arr, i, skipList);
            end = clock();
            time_delete += ((double)(end - start)) / CLOCKS_PER_SEC;
            destroySkipList(skipList);
        }

        fprintf(file_i, "%zu %f\n", i, time_insert / 5);
        fprintf(file_d, "%zu %f\n", i, time_delete / 5);
        fclose(file);
    }

    fclose(file_i);
    fclose(file_d);

    return 0;
}
