#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "open_hash.h"
#include "hash_func.h"

const int CNT_ELEMENT = 1000000;
const float LOAD_FACTOR_HTO = 0.75; // Hast Table Open hash

#define NOT_FOUND -1

//====================================================================================
//==================================CTOR_DTOR=========================================
//====================================================================================

struct HashTable* HT_Create(uint8_t method, int init_size) {
    struct HashTable* ht = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    assert(ht);

    ht->length           = init_size;
    ht->hash_method      = method;
    ht->table            = (struct Entry*)calloc(ht->length, sizeof(struct Entry));
    assert(ht->table);

    ht->size              = 0;
    return ht;
}

void HT_Destroy(struct HashTable* ht) {
    free(ht->table);
    free(ht);
}

//====================================================================================
//==================================REHASH============================================
//====================================================================================

void HT_Rehash(struct HashTable* ht, int new_length) {
    assert(ht);

    struct Entry* old_table = ht->table;
    int old_length = ht->length;
    ht->length = new_length;

    ht->table = (struct Entry*)calloc(ht->length, sizeof(struct Entry));
    assert(ht->table);

    for (int i = 0; i < old_length; i++) {

        if (old_table[i].status == OCCUPIED) {
            int key = old_table[i].key;

            if (ht->hash_method == LINEAR) {
                HT_InsertLinear(key, ht);

            } else if (ht->hash_method == SQUARE) {
                HT_InsertSquare(key, ht);

            } else {
                HT_InsertTwoHash(key, ht);
            }
        }

    }

    free(old_table);
}

void CheckAndRehash(struct HashTable* ht) {
    assert(ht);

    float load_factor = (float)ht->size / ht->length;

    if (load_factor > LOAD_FACTOR_HTO) {
        int new_length = ht->length * 2;
        HT_Rehash(ht, new_length);
    }
}

//====================================================================================
//==================================INSERT============================================
//====================================================================================

void HT_InsertLinear(int key, HashTable* ht) {
    assert(ht);

    // CheckAndRehash(ht);

    int index = hash_multiplication(key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        index = (index + 1) % ht->length;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;
}

#define C1 0.5
#define C2 0.5

void HT_InsertSquare(int key, HashTable* ht) {
    assert(ht);

    // CheckAndRehash(ht);

    int hash = hash_multiplication(key, ht->length);
    int i = 1;
    int index = hash;

    while (ht->table[index].status == OCCUPIED) {
        index = (index + i * (i + 1) / 2) % ht->length;
        i++;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;
}

void HT_InsertTwoHash(int key, HashTable* ht) {
    assert(ht);

    // CheckAndRehash(ht);

    int h1 = hash_multiplication(key, ht->length);
    int i = 1;
    int h2 = hash_func_dreams(key, ht->length);
    int index = (h1 + i * h2) % ht->length;

    while (ht->table[index].status == OCCUPIED) {
        index = (h1 + i * h2) % ht->length;
        i++;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;
}

//====================================================================================
//==================================SEARCH============================================
//====================================================================================

int HT_SearchLinear(int key, struct HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);
    int originalIndex = index;
    int count = 0;

    while (ht->table[index].status != EMPTY && count < ht->length) {
        if (ht->table[index].key == key && ht->table[index].status == OCCUPIED) {
            return index;
        }
        index = (index + 1) % ht->length;
        count++;
        if (index == originalIndex) {
            break;
        }
    }

    return NOT_FOUND;
}

int HT_SearchQuadratic(int key, struct HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);
    int i = 1;
    int originalIndex = index;

    while (ht->table[index].status != EMPTY && i <= ht->length) {
        if (ht->table[index].key == key && ht->table[index].status == OCCUPIED) {
            return index;
        }
        index = (originalIndex + i * i) % ht->length;
        i++;
        if (index == originalIndex) {
            break;
        }
    }

    return NOT_FOUND;
}

int HT_SearchDoubleHashing(int key, struct HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);
    int originalIndex = index;
    int count = 0;

    while (ht->table[index].status != EMPTY && count < ht->length) {
        if (ht->table[index].key == key && ht->table[index].status == OCCUPIED) {
            return index;
        }
        int h2 = hash_remainder(key, ht->length);
        index = (index + h2) % ht->length;
        count++;
        if (index == originalIndex) {
            break;
        }
    }

    return NOT_FOUND;
}

//====================================================================================
//==================================REMOVE============================================
//====================================================================================

void HT_RemoveKey(int key, HashTable* ht) {
    int index = 0;

    if (ht->hash_method == LINEAR) {
        index = HT_SearchLinear(key, ht);

    } else if (ht->hash_method == SQUARE) {
        index = HT_SearchQuadratic(key, ht);

    } else {
        index = HT_SearchDoubleHashing(key, ht);
    }

    if (index != -1) {
        ht->table[index].status = DELETED;
        ht->size--;
    }
}
