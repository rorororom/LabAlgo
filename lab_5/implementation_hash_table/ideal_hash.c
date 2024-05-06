#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "ideal_hash.h"

bool Coprime(int32_t a, int32_t b) {
    if (!a || !b) return false; // or true idk

    int32_t shift = __builtin_ctz((uint32_t) a | (uint32_t) b);
    a >>= __builtin_ctz((uint32_t) a);
    do
    {
        b >>= __builtin_ctz((uint32_t) b);
        if (a > b) {int32_t tmp = a; a = b; b = tmp;}
        b -= a;
    } while (b);

    return (a << shift) == 1;
}

/**
 * @brief Нахождение ближайшей меньшей степени двойки для заданного числа
 * @param num Число, для которого нужно найти ближайшую меньшую степень двойки
 * @return Ближайшая меньшая степень двойки
 */
int32_t NearPowTwo(int32_t num) {
    if (num == 0) num = 1;
    return 1 << (32 - __builtin_clz(num));
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
        if (hashTable->table[i].size > 0) {
                GenerateCoeff(&hashTable->table[i].coeff.A, &hashTable->table[i].coeff.B, hashTable->table[i].size);
        }

        for (int j = 0; j < htSecondLevel[i].size; j++) {
            int key = htSecondLevel[i].arr[j];
            if (key == 0)
                continue;

            int hashValue = Hash(key, hashTable->table[i].coeff.A, hashTable->table[i].coeff.B, hashTable->table[i].size);

            if (hashTable->table[i].arr[hashValue] != 0) {
                    GenerateCoeff(&hashTable->table[i].coeff.A, &hashTable->table[i].coeff.B, hashTable->table[i].size);

                for (int as = 0; as < hashTable->table[i].size; as++) {
                    hashTable->table[i].arr[as] = 0;
                }
                j = -1; // потому что после выхода из тела цикла происходит ++
                        // так как в ассемблерном коде в конце тела цикла происходит dec регистра
                        // а я обнуляю счетчик до инкремента
                        // следовательно, если ставить 0, то счетчик будет идти с 1
            } else {
                hashTable->table[i].arr[j] = key;
            }
        }
    }

    free(htSecondLevel);
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
