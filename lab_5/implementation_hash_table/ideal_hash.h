#ifndef IDEAL_HASH_H
#define IDEAL_HASH_H

#define COEFF_P 1000000007

#include <stdbool.h>
#include <stdint.h>

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

void BuildHashTable(struct HashTable* hashTable, int* arr, int N);
bool HT_ID_Search  (struct HashTable* hashTable, int value);

int32_t NearPowTwo(int32_t num);

#endif
