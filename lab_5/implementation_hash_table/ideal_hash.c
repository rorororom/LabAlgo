#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define SEARCH_ITERATIONS 10000000
#define P_CONST           10000003

#include "ideal_hash.h"

int GenerSizeHT(int N) {
    int power = 1;
    while (power <= N) {
        power *= 2;
    }
    return power;
}

void HF_GenerCoeff(int* A, int* B, size_t size) {
    *A = rand() % size;
    *A = 2 * (*A) + 1;
    *B = rand() % size;
}

struct HashTable* HT_Ctor(size_t N) {
    struct HashTable* hashTable = (struct HashTable*)calloc(1, sizeof(struct HashTable));

    int size = GenerSizeHT(N);

    hashTable->size = size;

    HF_GenerCoeff(&hashTable->data.A, &hashTable->data.B, hashTable->size);
    return hashTable;
}

struct HashTable* HT_collizion(struct HashTable* HT, int* collizion) {
    struct HashTable* ht_collizion = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    assert(ht_collizion);

    ht_collizion->table = (struct HashData*)calloc(HT->size, sizeof(struct HashData));
    assert(ht_collizion->table);

    for (size_t i = 0; i < HT->size; i++) {
        if (collizion[i] != 0) {
            ht_collizion->table[i].arr = (struct node*)calloc(collizion[i], sizeof(struct node));
            assert(ht_collizion->table[i].arr);
        }

        ht_collizion->table[i].size = 0;
    }

    ht_collizion->size = HT->size;
    ht_collizion->data.A = HT->data.A;
    ht_collizion->data.B = HT->data.B;

    return ht_collizion;
}

int HashFunc(int A, int B, int size, int key) {
    return ((A * key + B) % P_CONST + P_CONST) % P_CONST % size;
}

void CalculateCollisions(int* arr, int** collizion, int N, struct HashTable* HT) {
    while (true) {
        for (int i = 0; i < N; i++) {
            int key = arr[i];
            if (key == 0)
                continue;

            int hashValue = HashFunc(HT->data.A, HT->data.B, HT->size, key);
            (*collizion)[hashValue]++;
        }

        int sum = 0;
        for (int i = 0; i < HT->size; i++) {
            sum += (*collizion)[i] * (*collizion)[i];
        }

        if (sum < 4 * N) {
            break;
        }

        for (int i = 0; i < HT->size; i++) {
            (*collizion)[i] = 0;
        }

        HF_GenerCoeff(&HT->data.A, &HT->data.B, HT->size);
    }
}

void UpdateCollizion(struct HashTable* ht_collizion, int* arr, int N, int* collizion) {
    for (int i = 0; i < N; i++) {
        int key = arr[i];
        if (key == 0)
            continue;

        int hashValue = HashFunc(ht_collizion->data.A, ht_collizion->data.B, ht_collizion->size, key);
        ht_collizion->table[hashValue].arr[ht_collizion->table[hashValue].size].value = key;
        ht_collizion->table[hashValue].size++;
    }
}

void UpdateHT(struct HashTable* HT, int* collizion) {
    HT->table = (struct HashData*)calloc(HT->size, sizeof(struct HashData));
    for (size_t i = 0; i < HT->size; i++) {
        HT->table[i].size = collizion[i] * collizion[i];
        if (HT->table[i].size == 0) {
            continue;
        }
        HT->table[i].arr = (struct node*)calloc(HT->table[i].size, sizeof(struct node));
        assert(HT->table[i].arr);
    }
}

void BuildCorrectHashTable(struct HashTable* HT, struct HashTable* HT_collizion, int* arr) {
    for (size_t i = 0; i < HT->size; i++) {
        if (HT->table[i].size > 0) {
            HF_GenerCoeff(&HT->table[i].data.A, &HT->table[i].data.B, HT->table[i].size);
        }

        struct node* temp_arr = (struct node*)calloc(HT->table[i].size, sizeof(struct node));

        for (int j = 0; j < HT_collizion->table[i].size; j++) {
            int key = HT_collizion->table[i].arr[j].value;
            if (key == 0)
                continue;

            int hashValue = HashFunc(HT->table[i].data.A,  HT->table[i].data.B, HT->size, key);

            if (temp_arr[hashValue].value != 0) {
                HF_GenerCoeff(&HT->table[i].data.A, &HT->table[i].data.B, HT->table[i].size);
                for (size_t k = 0; k < HT->table[i].size; k++) {
                    temp_arr[k].value = 0;
                }

                j = -1;
            } else {
                temp_arr[hashValue].value = key;
            }
        }

        for (size_t j = 0; j < HT->table[i].size; j++) {
            HT->table[i].arr[j].value = temp_arr[j].value;
        }

        free(temp_arr);
    }
}


int HT_ID_Build(int* arr, int N, struct HashData* hashTable) {
    struct HashTable* HT = HT_Ctor(N);

    int* collizion = (int*)calloc(HT->size, sizeof(int));
    assert(collizion);

    CalculateCollisions(arr, &collizion, N, HT);

    struct HashTable* ht_collizion = HT_collizion(HT, collizion);

    UpdateCollizion(ht_collizion, arr, N, collizion);

    UpdateHT(HT, collizion);

    BuildCorrectHashTable(HT, ht_collizion, arr);

    free(ht_collizion);
    free(HT);
    return 0;
}


bool HT_ID_Search(struct HashData* hashTable, int value) {

    int hash1 = HashFunc(hashTable->data.A, hashTable->data.B, hashTable->size, value);

    if (hashTable[hash1].arr == NULL) {
        return false;
    }

    int hash2 = HashFunc(hashTable[hash1].data.A, hashTable[hash1].data.B, hashTable->size, value);

    if (hashTable[hash1].arr[hash2].value == value )
        return true;
    else
        return false;
}
