#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>


#include "ideal_hash.h"

bool Coprime(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a == 1;
}

/**
 * @brief Нахождение ближайшей меньшей степени двойки для заданного числа
 * @param N Число, для которого нужно найти ближайшую меньшую степень двойки
 * @return Ближайшая меньшая степень двойки
 */
int NearestLowerPowerOfTwo(int N) {
    int power = 1;
    while (power < N) {
        power <<= 1;
    }
    return power;
}

/**
 * @brief Генерирует случайное число в заданном диапазоне.
 *
 * @param min Минимальное значение диапазона.
 * @param max Максимальное значение диапазона.
 * @return Случайное число в диапазоне [min, max].
 */

int GenerateA(int min, int max) {
    double scaled = (double)rand() / RAND_MAX;
    int res = (int)(scaled * (max - min + 1) + min);
    return res;
}

int Hash(int key, int A, int B, int size) {
    return ((A * key + B) % COEFF_P + COEFF_P) % COEFF_P % size;
}

void GenerateCoeff(int* A, int* B, int size) {
    (*A) = GenerateA(3, COEFF_P);
    (*B) = rand() %  size;
};

// void GenerateSecondaryHashTable(struct HashTable* hashTable, int* collisions, int* arr, size_t N) {
//
// }

void BuildHashTable(struct HashTable* hashTable, int* arr, int N) {
    GenerateCoeff(&hashTable->coeff.A, &hashTable->coeff.B, hashTable->size);

    int* collisions = (int*)calloc(hashTable->size, sizeof(int));

    while (true) {
        for (int i = 0; i < N; i++) {
            int key = arr[i];
            if (key == 0)
                continue;

            int hashValue = Hash(key, hashTable->coeff.A, hashTable->coeff.B, hashTable->size);
            collisions[hashValue]++;
        }

        int sum = 0;
        for (int i = 0; i < hashTable->size; i++) {
            sum += collisions[i] * collisions[i];
        }

        if (sum < 4 * N) {
            break;
        }

        for (int i = 0; i < hashTable->size; i++) {
            collisions[i] = 0;
        }

        GenerateCoeff(&hashTable->coeff.A, &hashTable->coeff.B, hashTable->size);

    }

    for (int i = 0; i < hashTable->size; i++) {
        hashTable->table[i].size = collisions[i] * collisions[i];
        if (hashTable->table[i].size == 0) {
            continue;
        }
        hashTable->table[i].arr = (int*)calloc(hashTable->table[i].size, sizeof(int));
        assert(hashTable->table[i].arr);
    }

     HashTableLevelTwo* htSecondLevel = (HashTableLevelTwo*)malloc(hashTable->size * sizeof(HashTableLevelTwo));
    for (int i = 0; i < hashTable->size; i++) {
        htSecondLevel[i].arr = (int*)calloc(collisions[i], sizeof(int));
        htSecondLevel[i].size = 0;
    }

    for (int i = 0; i < N; i++) {
        int key = arr[i];
        if (key == 0)
            continue;
        int hashValue = Hash(key, hashTable->coeff.A, hashTable->coeff.B, hashTable->size);
        htSecondLevel[hashValue].arr[htSecondLevel[hashValue].size++]= key;
    }

    for (int i = 0; i < hashTable->size; i++) {
        int* temp_arr = (int*)calloc(hashTable->table[i].size, sizeof(int));

        if (hashTable->table[i].size > 0) {
                GenerateCoeff(&hashTable->table[i].coeff.A, &hashTable->table[i].coeff.B, hashTable->table[i].size);
        }

        for (int j = 0; j < htSecondLevel[i].size; j++) {
            int key = htSecondLevel[i].arr[j];
            if (key == 0)
                continue;

            int hashValue = Hash(key, hashTable->table[i].coeff.A, hashTable->table[i].coeff.B, hashTable->table[i].size);

            if (temp_arr[hashValue] != 0) {
                    GenerateCoeff(&hashTable->table[i].coeff.A, &hashTable->table[i].coeff.B, hashTable->table[i].size);

                for (int as = 0; as < hashTable->table[i].size; as++) {
                    temp_arr[as] = 0;
                }
                j = -1;
            } else {
                temp_arr[hashValue] = key;
            }
        }

        for (int j = 0; j < hashTable->table[i].size; j++) {
            hashTable->table[i].arr[j] = temp_arr[j];
        }

        free(temp_arr);
    }
}


bool HT_ID_Search(struct HashTable* hashTable, int value) {
    int hash1 = Hash(value, hashTable->coeff.A, hashTable->coeff.B, hashTable->size);

    if (hashTable->table[hash1].size == 0) {
        return false;
    }

    int hash2 = Hash(value, hashTable->table[hash1].coeff.A, hashTable->table[hash1].coeff.B, hashTable->table[hash1].size);

    if (hashTable->table[hash1].arr[hash2] == value)
        return true;
    else
        return false;
}
