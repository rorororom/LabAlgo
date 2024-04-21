#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TEST_STEP 10000
#define MAX_TEST_SIZE 1000000

#include "../implementation_hash_table/open_hash.h"
// #include "../implementation_hash_table/metod_chain.h"


void testing(const char *testFile, struct HashTable* ht) {
    FILE* file = fopen(testFile, "r");
    if (file == NULL) {
        printf("Error opening input file: %s\n", testFile);
        return;
    }

    int key;
    char op;

    while (fscanf(file, " %c %d", &op, &key) == 2) {
        if (op == '+') {
            HT_InsertLinear(key, ht);
        } else if (op == '-') {
            HT_RemoveKey(key, ht);
        } else if (op == '?') {
            int found = HT_SearchLinear(key, ht);
        }
    }


    fclose(file);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    FILE* result = fopen("../res/result3_p2_two_hash.txt", "w");
    if (result == NULL) {
        printf("Error opening input file: %s\n", result);
        return 1;
    }

    for (int i = TEST_STEP; i <= MAX_TEST_SIZE; i += TEST_STEP) {
        struct HashTable* ht = HT_Create("line", 10000);
        char filename[256];
        printf("%d\n", i);
        snprintf(filename, sizeof(filename), "../array_tests/test3_%d.txt", i);

        start = clock();

        testing(filename, ht);

        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Вычисляем время выполнения теста
        fprintf(result, "%d %f\n", i, cpu_time_used);
        HT_Destroy(ht);
    }

    fclose(result);


    return 0;
}
