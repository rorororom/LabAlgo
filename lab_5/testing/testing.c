#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// #define HASH_OPEN
#define HASH_CHAIN

#ifdef HASH_OPEN
#include "../implementation_hash_table/open_hash.h"
#endif

#ifdef HASH_CHAIN
#include "../implementation_hash_table/metod_chain.h"
#endif


#define TEST_STEP 10000
#define MAX_TEST_SIZE 1000000
#define INIT_CAP 10000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nn {
    char op;
    int key;
} nn;

nn* readData(const char* testFile, int size) {
    FILE* file = fopen(testFile, "r");
    if (file == NULL) {
        printf("Error opening input file: %s\n", testFile);
        return NULL;
    }

    // Выделяем память под массив структур Node
    nn* nodes = (nn*)malloc(size * sizeof(nn));
    if (nodes == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    // Считываем данные из файла в массив
    for (int i = 0; i < size; i++) {
        char op;
        int key;
        int res = fscanf(file, " %c %d", &op, &key);
        if (res != 2)
            abort();
        nodes[i].op = op;
        nodes[i].key = key;

    }

    fclose(file);

    return nodes;
}

void testing(struct nn* node, struct HashTable* ht, int method, int size) {

    int key;
    char op;

    for (size_t i = 0; i < size; i++){
        op = node[i].op;
        key = node[i].key;
        if (op == '+') {
#ifdef HASH_OPEN
            if (method == LINEAR) {
                HT_InsertLinear(key, ht);
            }
            else if (method == SQUARE) {
                HT_InsertSquare(key, ht);
            }
            else {
                HT_InsertTwoHash(key, ht);
            }
#endif

#ifdef HASH_CHAIN
            HT_CH_Insert(key, ht);
#endif

        } else if (op == '-') {
#ifdef HASH_OPEN
            HT_RemoveKey(key, ht);
#endif
#ifdef HASH_CHAIN
            HT_CH_RemoveKey(key, ht);
#endif
        } else if (op == '?') {
#ifdef HASH_OPEN
            int found = 0;
            if (method == LINEAR) {
                found = HT_SearchLinear(key, ht);
            }
            else if (method == SQUARE) {
                found = HT_SearchQuadratic(key, ht);
            }
            else {
                found = HT_SearchDoubleHashing(key, ht);
            }
#endif
#ifdef HASH_CHAIN
            int found = HT_CH_Search(key, ht);
#endif
        }

    }
}

int GenerSizeHT(int N) {
    int power = 1;
    while (power < N) {
        power <<= 1;
    }
    return power;
}


int main() {
    clock_t start, end;
    double cpu_time_used;

    FILE* result = fopen("../res/result2_p3_chain.txt", "w");
    if (result == NULL) {
        printf("Error opening input file");
        return 1;
    }

    for (int i = 2 * TEST_STEP; i <= MAX_TEST_SIZE; i += TEST_STEP) {
        int size = GenerSizeHT(i);
        printf("size = %d\n", size);
#ifdef HASH_OPEN
        struct HashTable* ht = HT_Create(TWO_HASH, size);
        printf("%d %d %d %d\n", ht->coeff->A, ht->coeff->B, ht->coeff->P, ht->length);
#endif
#ifdef HASH_CHAIN
        struct HashTable* ht = HT_CH_Create(size);
#endif

        char filename[256];
        printf("%d\n", i);
        snprintf(filename, sizeof(filename), "../array_tests/test2_%d.txt", i);

        nn* nodes = readData(filename, i);
        if (nodes == NULL) {
            fprintf(stderr, "Ошибка чтения данных из файла\n");
            return 1;
        }

        start = clock();

        testing(nodes, ht, 0, i);

        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Вычисляем время выполнения теста
        fprintf(result, "%d %f\n", i, cpu_time_used);
#ifdef HASH_OPEN
        HT_Destroy(ht);
#endif
#ifdef HASH_CHAIN
        HT_CH_Destroy(ht);
#endif
    }

    fclose(result);


    return 0;
}
