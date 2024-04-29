#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef int status_t;

enum STATUS {
    OK = 0,
    ERROR
};

#define COEFF_P 1000000007

#define CHECK_SCANF_D(res, input, output, var, message) \
    res = fscanf(input, "%d", var);                     \
    if (res != 1) {                                     \
        fprintf(output, "%s", message);                 \
        return ERROR;                                       \
    }

#define CHECK_SCANF_S(res, input, output, var, message) \
    res = fscanf(input, "%s", var);                     \
    if (res != 1) {                                     \
        fprintf(output, "%s", message);                 \
        return ERROR;                                       \
    }

/**
 * @brief Структура для хранения коэффициентов A и B.
 */
typedef struct Coefficients {
    int A; /**< Коэффициент A */
    int B; /**< Коэффициент B */
} Coefficients;


/**
 * @struct HashTableLevelTwo
 * @brief Структура, представляющая второй уровень хэш-таблицы
 */
typedef struct HashTableLevelTwo {
    Coefficients coeff; /**< Коэффициенты для хэш-функции */
    int* arr;            /**< Массив для хранения ключей */
    int size;            /**< Размер массива */
} HashTableLevelTwo;

/**
 * @struct HashTable
 * @brief Структура, представляющая основную хэш-таблицу
 */
typedef struct HashTable {
    int size;                 /**< Размер хэш-таблицы */
    Coefficients coeff;
    HashTableLevelTwo* table; /**< Массив вторичных хэш-таблиц */
} HashTable;

/**
 * @brief Проверка, являются ли два числа взаимно простыми
 * @param a Первое число
 * @param b Второе число
 * @return true, если a и b взаимно просты, иначе false
 */
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

status_t ReadDataAndFindData(FILE* input, FILE* output, struct HashTable* hashTable, bool nul) {
    char command[10];
    int res = 0;
    CHECK_SCANF_S(res, input, output, command, "не считались данные\n");
    while (command[0] != '.') {
        int value = atoi(command);
        if(value == 0)
        {
            if(nul) fprintf(output, "YES\n");
            else    fprintf(output, "NO\n");
                CHECK_SCANF_S(res, input, output, command, "не считались данные\n");
            continue;
        }


        int hash1  = ((hashTable->coeff.A * value + hashTable->coeff.B) % COEFF_P + COEFF_P) % COEFF_P % hashTable->size;
        if (hashTable->table[hash1].arr == NULL) {
            fprintf(output, "NO\n");
            CHECK_SCANF_S(res, input, output, command, "не считались данные\n");
            continue;
        }

        int A2 = hashTable->table[hash1].coeff.A, B2 = hashTable->table[hash1].coeff.B, P2 = COEFF_P;
        int hash2 = ((A2 * value + B2) % P2 + P2) % P2 % hashTable->table[hash1].size;

        if (hashTable->table[hash1].arr[hash2] == value )
            fprintf(output, "YES\n");
        else
            fprintf(output, "NO\n");

        CHECK_SCANF_S(res, input, output, command, "не считались данные\n");
    }
    return 1;
}

/**
 * @brief Хэш-функция для ключа.
 *
 * @param key Ключ.
 * @param A Коэффициент A.
 * @param B Коэффициент B.
 * @param size Размер таблицы.
 * @return Значение хэша для ключа.
 */
int Hash(int key, int A, int B, int size) {
    return ((A * key + B) % COEFF_P + COEFF_P) % COEFF_P % size;
}

/**
 * @brief Генерирует коэффициенты A и B для хэш-таблицы второго уровня.
 *
 * @param A Указатель на коэффициент A.
 * @param B Указатель на коэффициент B.
 * @param size Размер таблицы.
 */
void GenerateCoeff(int* A, int* B, int size) {
    (*A) = GenerateA(3, COEFF_P);
    (*B) = rand() %  size;
};

/**
 * @brief Генерирует вторичную хэш-таблицу.
 *
 * @param hashTable Основная хэш-таблица.
 * @param collisions Массив коллизий.
 * @param arr Массив ключей.
 * @param N Размер массива ключей.
 */
void GenerateSecondaryHashTable(struct HashTable* hashTable, int* collisions, int* arr, size_t N) {
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

/**
 * @brief Строит основную хэш-таблицу.
 *
 * @param hashTable Указатель на хэш-таблицу.
 * @param arr Массив ключей.
 * @param N Размер массива ключей.
 */
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

    GenerateSecondaryHashTable(hashTable, collisions, arr, N);
}


int main() {
    srand(time(NULL));
    FILE* input = stdin;
    FILE* output = stdout;

    int N = 0;
    int res = 0;
    CHECK_SCANF_D(res, input, output, &N, "не считался размер\n");

    bool nul = false;
    int* arr = (int*)calloc(N, sizeof(int));
    for (size_t i = 0; i < N; i++) {
        CHECK_SCANF_D(res, input, output, &arr[i], "не считался число\n")
        if(arr[i] == 0) {
            nul = true;
        }
    }

    int size = NearestLowerPowerOfTwo(N);

    HashTable hashTable;
    hashTable.size = size;

    hashTable.table = (HashTableLevelTwo*)malloc(size * sizeof(HashTableLevelTwo));
    assert(hashTable.table);

    BuildHashTable(&hashTable, arr, N);

    status_t status = ReadDataAndFindData(input, output, &hashTable, nul);
    if (status)
        return 1;

    return 0;
}
