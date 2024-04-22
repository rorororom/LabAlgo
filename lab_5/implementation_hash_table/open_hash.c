#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "open_hash.h"
#include "hash_func.h"

const int CNT_ELEMENT = 1000000;

#define NOT_FOUND -1

//====================================================================================
//==================================CTOR_DTOR=========================================
//====================================================================================

struct HashTable* HT_Create(char* method, int init_size) {
    struct HashTable* ht = (struct HashTable*)calloc(1, sizeof(struct HashTable));

    ht->length           = init_size;
    ht->hash_method      = strdup(method);
    ht->table            = (struct Entry*)calloc(ht->length, sizeof(struct Entry));
    ht->size              = 0;
    return ht;
}

void HT_Destroy(struct HashTable* ht) {
    free(ht->table);
    free(ht->hash_method);
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

            if (strcmp(ht->hash_method, "line") == 0) {
                HT_InsertLinear(key, ht);

            } else if (strcmp(ht->hash_method, "square") == 0) {
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

    if (load_factor > 0.75) {
        int new_length = ht->length * 2;
        HT_Rehash(ht, new_length);
    }
}

//====================================================================================
//==================================INSERT============================================
//====================================================================================

void HT_InsertLinear(int key, HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        index = (index + 1) % ht->length;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;

    CheckAndRehash(ht);
}


void HT_InsertSquare(int key, HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);
    int i = 1;

    while (ht->table[index].status == OCCUPIED) {
        index = (index + i * i) % ht->length;
        i++;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;

    CheckAndRehash(ht);
}

void HT_InsertTwoHash(int key, HashTable* ht) {
    assert(ht);

    int index = hash_multiplication(key, ht->length);
    int i = 1;
    int h2 = hash_remainder(key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        index = (index + i * h2) % ht->length;
        i++;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;

    CheckAndRehash(ht);
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

    if (strcmp(ht->hash_method, "line") == 0) {
        index = HT_SearchLinear(key, ht);

    } else if (strcmp(ht->hash_method, "square") == 0) {
        index = HT_SearchQuadratic(key, ht);

    } else {
        index = HT_SearchDoubleHashing(key, ht);
    }

    if (index != -1) {
        ht->table[index].status = DELETED;
        ht->size--;
    }
}
