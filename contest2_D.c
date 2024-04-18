#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct node {
    int value;
    int flag_zero;
};

struct HashTable {
    struct arrHash2* table;
    int size;
    int A;
    int B;
    int P;
};

struct arrHash2 {
    int A;
    int B;
    int P;
    struct node* arr;
    int size;
};

typedef int status_t;

enum STATUS {
    OK,
    ERROR
};

int GenerSizeHT(int N) {
    int power = 1;
    while (power <= N) {
        power *= 2;
    }
    return power;
}

status_t ReadData(int** arr, int* N, bool* flagZero) {
    int res = scanf("%d", N);
    if (res != 1) {
        printf("не считался размер\n");
        return ERROR;
    }

    *arr = (int*)calloc(*N, sizeof(int));

    for (size_t i = 0; i < *N; i++) {
        int res = scanf("%d", &((*arr)[i]));
        if (res != 1) {
            printf("не считался размер\n");
            return ERROR;
        }

        if((*arr)[i] == 0) {
            *flagZero = true;
        }
    }

    return OK;
}

void HF_GenerCoeff(int* A, int* B, int* P, size_t size) {
    *A = rand() % size;
    *A = 2 * (*A) + 1;
    *B = rand() % size;
    *P = rand() % size + size;
    *P = 2 * (*P) + 1;
}

struct HashTable* HT_Ctor(size_t N) {
    struct HashTable* hashTable = (struct HashTable*)calloc(1, sizeof(struct HashTable));

    int size = GenerSizeHT(N);

    hashTable->size = size;

    HF_GenerCoeff(&hashTable->A, &hashTable->B, &hashTable->P, hashTable->size);
    return hashTable;
}

struct HashTable* HT_collizion(struct HashTable* HT, int* collizion) {
    struct HashTable* ht_collizion = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    assert(ht_collizion);

    ht_collizion->table = (struct arrHash2*)calloc(HT->size, sizeof(struct arrHash2));
    assert(ht_collizion->table);

    for (size_t i = 0; i < HT->size; i++) {
        if (collizion[i] != 0) {
            ht_collizion->table[i].arr = (struct node*)calloc(collizion[i], sizeof(struct node));
            assert(ht_collizion->table[i].arr);
        }

        ht_collizion->table[i].size = 0;
    }

    ht_collizion->size = HT->size;
    ht_collizion->A = HT->A;
    ht_collizion->B = HT->B;
    ht_collizion->P = HT->P;

    return ht_collizion;
}

void CalculateCollisions(int* arr, int** collizion, int N, struct HashTable* HT) {
    while (true) {
        for (int i = 0; i < N; i++) {
            int key = arr[i];
            if (key == 0)
                continue;
            int hashValue = ((HT->A * key + HT->B) % HT->P + HT->P) % HT->P % HT->size;
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

        HF_GenerCoeff(&HT->A, &HT->B, &HT->P, HT->size);
    }
}

void UpdateCollizion(struct HashTable* ht_collizion, int* arr, int N, int* collizion) {
    for (int i = 0; i < N; i++) {
        int key = arr[i];
        if (key == 0)
            continue;
        int hashValue = ((ht_collizion->A * key + ht_collizion->B) % ht_collizion->P + ht_collizion->P) % ht_collizion->P % ht_collizion->size;
        ht_collizion->table[hashValue].arr[ht_collizion->table[hashValue].size].value = key;
        ht_collizion->table[hashValue].size++;
    }
}

int HashFunc(struct arrHash2* ht, int key) {
    return ((ht->A * key + ht->B) % ht->P + ht->P) % ht->P % ht->size;
}

void UpdateHT(struct HashTable* HT, int* collizion) {
    HT->table = (struct arrHash2*)calloc(HT->size, sizeof(struct arrHash2));
    for (size_t i = 0; i < HT->size; i++) {
        HT->table[i].size = collizion[i] * collizion[i];
        if (HT->table[i].size == 0) {
            continue;
        }
        HT->table[i].arr = (struct node*)calloc(HT->table[i].size, sizeof(struct node));
        assert(HT->table[i].arr);
    }
}

void BuildCorrectHashFunc2(struct HashTable* HT, struct HashTable* HT_collizion, int* arr) {
    for (size_t i = 0; i < HT->size; i++) {
        if (HT->table[i].size > 0) {
            HF_GenerCoeff(&HT->table[i].A, &HT->table[i].B, &HT->table[i].P, HT->table[i].size);
        }

        struct node* temp_arr = (struct node*)calloc(HT->table[i].size, sizeof(struct node));

        for (int j = 0; j < HT_collizion->table[i].size; j++) {
            int key = HT_collizion->table[i].arr[j].value;
            if (key == 0)
                continue;

            int hashValue = ((HT->table[i].A * key + HT->table[i].B) % HT->table[i].P + HT->table[i].P) % HT->table[i].P % HT->size;

            if (temp_arr[hashValue].value != 0) {
                HF_GenerCoeff(&HT->table[i].A, &HT->table[i].B, &HT->table[i].P, HT->table[i].size);
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

void ProcessCommands(struct HashTable* HT, bool flagZero) {
    char command[10];
    int res = scanf("%s", command);
    if (res != 1) {
        printf("не считался размер\n");
        return;
    }

    while (command[0] != '.') {
        int value = atoi(command);
        if (value == 0) {
            if(flagZero)
                printf("YES\n");
            else
                printf("NO\n");

            int res = scanf("%s", command);
            if (res != 1) {
                printf("не считался размер\n");
                return;
            }
            continue;
        }

        int hash1 = ((HT->A * value + HT->B) % HT->P + HT->P) % HT->P % HT->size;
        if (HT->table[hash1].arr == NULL) {
            printf("NO\n");

            int res = scanf("%s", command);
            if (res != 1) {
                printf("не считался размер\n");
                return;
            }

            continue;
        }

        int hash2 = HashFunc(&HT->table[hash1], value);
        if (HT->table[hash1].arr[hash2].value == value) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        scanf("%s", command);
    }
}

int main() {
    srand(time(NULL));

    int N = 0;
    int* arr;

    bool flagZero = false;

    status_t res = ReadData(&arr, &N, &flagZero);
    if (res)
        return 1;

    struct HashTable* HT = HT_Ctor(N);

    int* collizion = (int*)calloc(HT->size, sizeof(int));
    assert(collizion);

    CalculateCollisions(arr, &collizion, N, HT);

    struct HashTable* ht_collizion = HT_collizion(HT, collizion);

    UpdateCollizion(ht_collizion, arr, N, collizion);

    UpdateHT(HT, collizion);

    BuildCorrectHashFunc2(HT, ht_collizion, arr);

    ProcessCommands(HT, flagZero);

    free(ht_collizion);
    free(HT);
    return 0;
}

