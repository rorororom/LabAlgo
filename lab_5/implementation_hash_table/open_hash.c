#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "open_hash.h"
#include "hash_func.h"

const int   CNT_ELEMENT     = 1000000;
const int   REHASH_FACTOR   = 2;
const float LOAD_FACTOR_HTO = 0.75;

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
    for (int i = 0; i < init_size; i++) {
        ht->table[i].status = EMPTY;
    }

    ht->coeff = HashGetCoeff(init_size);

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
    ht->size = 0;

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

    float load_factor = (float)(ht->size )/ (float)(ht->length);
    if (load_factor > LOAD_FACTOR_HTO) {
        int new_length = ht->length * REHASH_FACTOR;
        HT_Rehash(ht, new_length);
    }
}

//====================================================================================
//==================================INSERT============================================
//====================================================================================

void HT_InsertLinear(int key, HashTable* ht) {
    assert(ht);
    assert(ht->table);

    CheckAndRehash(ht);

    int index = HashFunc(ht->coeff, key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        if(ht->table[index].key == key) {
            return;
        }

        index = (index + 1) & (ht->length - 1);
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;
}

void HT_InsertSquare(int key, HashTable* ht) {
    assert(ht);
    assert(ht->table);

    CheckAndRehash(ht);

    int hash = HashFunc(ht->coeff, key, ht->length);

    int index = hash;
    int i = 1;

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].key == key){
            return;
        }

        index += i;
        index = index & (ht->length - 1);
        i++;
    }

    ht->table[index].status = OCCUPIED;
    ht->table[index].key = key;
    ht->size++;
}


void HT_InsertTwoHash(int key, HashTable* ht) {
    assert(ht);
    assert(ht->table);

    CheckAndRehash(ht);

    int hash1 = HashFunc(ht->coeff, key, ht->length);
    int hash2 = HashFuncDreams(key , ht->length);
    int index = hash1;

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].key == key){
            return;
        }
        index += hash2;
        index = index & (ht->length - 1);
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
    assert(ht->table);

    int index = HashFunc(ht->coeff, key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].key == key) {
            return index;
        }
        index = (index + 1) & (ht->length - 1);
    }

    return NOT_FOUND;
}

int HT_SearchQuadratic(int key, struct HashTable* ht) {
    assert(ht);
    assert(ht->table);

    int hash = HashFunc(ht->coeff, key, ht->length);
    int i = 1;
    int index = hash;

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].key == key) {
            return index;
        }
        index += i;
        index = index & (ht->length - 1);
        i++;
    }

    return NOT_FOUND;

}

int HT_SearchDoubleHashing(int key, struct HashTable* ht) {
    assert(ht);
    assert(ht->table);

    int hash1 = HashFunc(ht->coeff, key, ht->length);
    int index = hash1;
    int hash2 = HashFuncDreams(key, ht->length);

    while (ht->table[index].status == OCCUPIED) {
        if (ht->table[index].key == key) {
            return index;
        }
        index += hash2;
        index = index & (ht->length - 1);
    }

    return NOT_FOUND;
}


//====================================================================================
//==================================REMOVE============================================
//====================================================================================

void HT_RemoveKey(int key, HashTable* ht) {
    int index = 0;

    switch(ht->hash_method) {
        case LINEAR:
            index = HT_SearchLinear(key, ht);
            break;
        case SQUARE:
            index = HT_SearchQuadratic(key, ht);
            break;
        case TWO_HASH:
            index = HT_SearchDoubleHashing(key, ht);
            break;
        default:
            return;
    }

    if (index != NOT_FOUND) {
        ht->table[index].status = DELETED;
        ht->table[index].key = 0;
        ht->size--;
    }
}
