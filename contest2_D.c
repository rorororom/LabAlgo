#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define P_CONST 10000003

#define CHECK_SCANF_D(res, input, var, message, status) \
    res = fscanf(input, "%d", var);                     \
    if (res != 1) {                                     \
        fprintf(output, "%s", message);                 \
        return status;                                  \
    }

#define CHECK_SCANF_S(res, input, var, message, status) \
    res = fscanf(input, "%s", var);                     \
    if (res != 1) {                                     \
        fprintf(output, "%s", message);                 \
        return status;                                  \
    }

struct node {
    int value;
    int flag_zero;
};

struct HashFuncData {
    int A;
    int B;
};

struct HashTable {
    struct HashData* table;
    struct HashFuncData data;
    int size;
};

struct HashData {
    struct HashFuncData data;
    struct node* arr;
    int size;
};

typedef int status_t;

enum STATUS {
    OK,
    ERROR
};

/**
 * Генерирует размер хэш-таблицы, который является ближайшей к степени двойки сверху для данного N.
 * @param N - количество элементов
 * @return ближайшая к степени двойки сверху размер хэш-таблицы
 */
int GenerSizeHT(int N) {
    int power = 1;
    while (power <= N) {
        power = power << 1;
    }
    return power;
}

/**
 * Генерирует случайные коэффициенты A, B, P для хэш-таблицы.
 * @param A - коэффициент A
 * @param B - коэффициент B
 * @param size - размер хэш-таблицы
 */
void HF_GenerCoeff(int* A, int* B, size_t size) {
    *A = rand() % size;
    *A = 2 * (*A) + 1;
    *B = rand() % size;
}

/**
 * Создает хэш-таблицу с указанным размером.
 * @param N - количество элементов
 * @return указатель на созданную хэш-таблицу
 */
struct HashTable* HT_Ctor(size_t N) {
    struct HashTable* hashTable = (struct HashTable*)calloc(1, sizeof(struct HashTable));

    int size = GenerSizeHT(N);

    hashTable->size = size;

    HF_GenerCoeff(&hashTable->data.A, &hashTable->data.B, hashTable->size);
    return hashTable;
}

/**
 * Создает хэш-таблицу с учетом коллизий.
 * @param HT - исходная хэш-таблица
 * @param collizion - массив коллизий
 * @return указатель на созданную хэш-таблицу с учетом коллизий
 */
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

/**
 * Обновляет переменные A B с учетом коллизий.
 * @param A    - коэффициент A
 * @param B    - коэффициент B
 * @param size - размер
 * @param key  - ключ
 */
int HashFunc(int A, int B, int size, int key) {
    return ((A * key + B) % P_CONST + P_CONST) % P_CONST % size;
}

/**
 * Вычисляет коллизии для элементов исходного массива исходной хэш-таблицы.
 * @param arr - исходный массив элементов
 * @param collizion - массив коллизий
 * @param N - количество элементов
 * @param HT - исходная хэш-таблица
 */
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

/**
 * Обновляет хэш-таблицу с учетом коллизий.
 * @param ht_collizion - хэш-таблица с учетом коллизий
 * @param arr - исходный массив элементов
 * @param N - количество элементов
 * @param collizion - массив коллизий
 */
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


/**
 * Обновляет хэш-таблицу с учетом коллизий.
 * @param HT - исходная хэш-таблица
 * @param collizion - массив коллизий
 */
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

/**
 * Строит корректную хэш-функцию для хэш-таблицы с учетом коллизий (2 уровень).
 * @param HT - исходная хэш-таблица
 * @param HT_collizion - хэш-таблица с учетом коллизий
 * @param arr - исходный массив элементов
 */
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

/**
 * Считывает данные из ввода.
 * @param arr - указатель на массив элементов
 * @param N - указатель на количество элементов
 * @param flagZero - указатель на флаг наличия элементов со значением 0
 * @param input - файловый поток ввода
 * @param output - файловый поток вывода
 * @return статус выполнения
 */
status_t ReadData(int** arr, int* N, bool* flagZero, FILE* input, FILE* output) {
    int res;
    CHECK_SCANF_D(res, stdin, N, "не считался размер\n", ERROR)

    *arr = (int*)calloc(*N, sizeof(int));

    for (size_t i = 0; i < *N; i++) {
        CHECK_SCANF_D(res, stdin, &((*arr)[i]), "не считался размер\n", ERROR)

        if ((*arr)[i] == 0) {
            *flagZero = true;
        }
    }

    return OK;
}

/**
 * Обрабатывает команды для хэш-таблицы.
 * @param HT - указатель на хэш-таблицу
 * @param flagZero - флаг наличия элементов со значением 0
 * @param input - файловый поток ввода
 * @param output - файловый поток вывода
 * @return статус выполнения
 */
status_t ProcessCommands(struct HashTable* HT, bool flagZero, FILE* input, FILE* output) {
    char command[10];
    int res;
    CHECK_SCANF_S(res, input, command, "не считался размер\n", ERROR)

    while (command[0] != '.') {
        int value = atoi(command);
        if (value == 0) {
            if (flagZero)
                fprintf(output, "YES\n");
            else
                fprintf(output, "NO\n");

            CHECK_SCANF_S(res, input, command, "не считалось значение\n", ERROR)
        }

        int hash1 = ((HT->A * value + HT->B) % HT->P + HT->P) % HT->P % HT->size;
        if (HT->table[hash1].arr == NULL) {
            fprintf(output, "NO\n");

            CHECK_SCANF_S(res, input, command, "не считалось значение\n", ERROR)
        }

        int hash2 = HashFunc(&HT->table[hash1], value);
        if (HT->table[hash1].arr[hash2].value == value) {
            fprintf(output, "YES\n");
        } else {
            fprintf(output, "NO\n");
        }

        CHECK_SCANF_S(res, input, command, "не считалось значение\n", ERROR)
    }

    return OK;
}


int main() {
    srand(time(NULL));
    FILE* input  = stdin;
    FILE* output = stdout;

    int N = 0;
    int* arr;

    bool flagZero = false;

    status_t res = ReadData(&arr, &N, &flagZero, input, output);
    if (res)
        return 1;

    struct HashTable* HT = HT_Ctor(N);

    int* collizion = (int*)calloc(HT->size, sizeof(int));
    assert(collizion);

    CalculateCollisions(arr, &collizion, N, HT);

    struct HashTable* ht_collizion = HT_collizion(HT, collizion);

    UpdateCollizion(ht_collizion, arr, N, collizion);

    UpdateHT(HT, collizion);

    BuildCorrectHashTable(HT, ht_collizion, arr);

    res = ProcessCommands(HT, flagZero, input, output);
    if (res)
        return 1;

    free(ht_collizion);
    free(HT);

    return 0;
}

