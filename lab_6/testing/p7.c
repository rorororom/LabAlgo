#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEP 100000
#define MAX_TEST 1000000

// #define SKIP_LIST
// #define SPLAY_TREE
#define DEKARTOVO_TREE

#ifdef SKIP_LIST
#include "../skip_list/skip_list.h"
#endif
#ifdef SPLAY_TREE
#include "../splay_tree/splay_tree.h"
#endif
#ifdef DEKARTOVO_TREE
#include "../dekartovo_tree/dekartovo_tree.h"
#endif

#ifdef SKIP_LIST
void testing_insert(int* arr, int n, struct SkipList *skipList) {
    for (size_t i = 0; i < n; i++) {
        insert(skipList, arr[i]);
    }
}
#endif
#ifdef SPLAY_TREE
#endif
#ifdef DEKARTOVO_TREE
void testing_insert(int* arr, int n, struct node* t) {
    for (size_t i = 0; i < n; i++) {
        insert(t, it);
    }
}
#endif

#ifdef SKIP_LIST
void testing_delete(int* arr, int n, struct SkipList *skipList) {
    for (size_t i = 0; i < n / 2; i++) {
        erase(skipList, arr[i]);
    }
}
#endif
#ifdef DEKARTOVO_TREE
void testing_delete(int* arr, int n, struct SkipList *skipList) {
    for (size_t i = 0; i < n / 2; i++) {
        erase(skipList, arr[i]);
    }
}
#endif

int main() {
#ifdef SKIP_LIST
    FILE* file_i = fopen("../res/p7_insert.txt", "w");
#endif
#ifdef DEKARTOVO_TREE
    FILE* file_i = fopen("../res/p4_insert.txt", "w");
#endif
    if (file_i == NULL) {
        printf("ошинбос\n");
        return 1;
    }

#ifdef SKIP_LIST
    FILE* file_d = fopen("../res/p7_delete.txt", "w");
#endif
#ifdef DEKARTOVO_TREE
    FILE* file_d = fopen("../res/p4_delete.txt", "w");
#endif
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
#ifdef SKIP_LIST
            SkipList *skipList = createSkipList();
#endif

            start = clock();
#ifdef SKIP_LIST
            testing_insert(arr, i, skipList);
#endif
            end = clock();
            time_insert += ((double)(end - start)) / CLOCKS_PER_SEC;
            // display(skipList);

            start = clock();
#ifdef SKIP_LIST
            testing_delete(arr, i, skipList);
#endif
            end = clock();
            time_delete += ((double)(end - start)) / CLOCKS_PER_SEC;
            // display(skipList);
#ifdef SKIP_LIST
            destroySkipList(skipList);
#endif
        }

        fprintf(file_i, "%zu %f\n", i, time_insert / 5);
        fprintf(file_d, "%zu %f\n", i, time_delete / 5);

        fclose(file);
    }

    fclose(file_i);
    fclose(file_d);

    return 0;
}
