#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define AVL
// #define SPLAY
// #define CARTESIAN
#define SKIP_LIST

#define STEP 100000
#define MAX_TEST 1000000

#ifdef  SKIP_LIST
#include "../skip_list/skip_list.h"
#endif

#ifdef SPLAY
#include "../splay_tree/splay_tree.h"
#endif

#ifdef CARTESIAN
#include "../cartesian_tree/cartesian_tree.h"
#endif

#ifdef AVL
#include "../AVL/avl_tree.h"
#endif

#ifdef SKIP_LIST
void testing_insert(int* arr, int n, struct SkipList* skipList) {
#endif

#if defined(AVL) || defined(CARTESIAN) || defined(SPLAY)
void testing_insert(int* arr, int n, node* root) {
#endif
    for (size_t i = 0; i < n; i++) {
#ifdef SKIP_LIST
        insert(skipList, arr[i]);
#endif

#ifdef AVL
        root = Insert(root, arr[i]);
#endif

#ifdef CARTESIAN
        pnode newnode = createNode(arr[i]);
        if (newnode != NULL) {
            insert(root, newnode);
        }
#endif

#ifdef SPLAY
        root = Insert(root, arr[i]);
#endif
    }
}

#ifdef SKIP_LIST
void testing_delete(int* arr, int n, struct SkipList* skipList) {
#endif
#if defined(AVL) || defined(CARTESIAN) || defined(SPLAY)
void testing_delete(int* arr, int n, node* root) {
#endif
    for (size_t i = 0; i < n / 2; i++) {
#ifdef SKIP_LIST
        erase(skipList, arr[i]);
#endif

#ifdef AVL
        root = RemoveTree(root, arr[i]);
#endif

#ifdef CARTESIAN
        if (exists(root, arr[i])) {
            erase(root, arr[i]);
        }
#endif

#ifdef SPLAY
        root = Delete(root, arr[i]);
#endif
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
#ifdef SKIP_LIST
            SkipList* skipList = createSkipList();
#endif
#if defined(AVL) || defined(CARTESIAN) || defined(SPLAY)
            node* root = NULL;
#endif

            start = clock();
#ifdef SKIP_LIST
            testing_insert(arr, i, skipList);
#endif
#if defined(AVL) || defined(CARTESIAN) || defined(SPLAY)
            testing_insert(arr, i, root);
#endif
            end = clock();
            time_insert += ((double)(end - start)) / CLOCKS_PER_SEC;

            start = clock();
#ifdef SKIP_LIST
            testing_delete(arr, i, skipList);
#endif
#if defined(AVL) || defined(CARTESIAN) || defined(SPLAY)
            testing_delete(arr, i, root);
#endif
            end = clock();
            time_delete += ((double)(end - start)) / CLOCKS_PER_SEC;
#ifdef SKIP_LIST
            destroySkipList(skipList);
#endif
#ifdef AVL
            DeleteTree(root);
#endif
#ifdef CARTESIAN
            deleteTree(root);
#endif
#ifdef SPLAY
            Free(root);
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
