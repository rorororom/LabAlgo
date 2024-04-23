#ifndef OPEN_HASH_LINE_H
#define OPEN_HASH_LINE_H

#include <stdint.h>

extern const int CNT_ELEMENT;

enum STATUS {
    EMPTY = 0,
    DELETED,
    OCCUPIED
};

typedef struct Entry{
    int status;
    int key;
} Entry;

enum HASH_METHOD {
    LINEAR,
    SQUARE,
    TWO_HASH
};

typedef struct HashTable{
    int length;
    int size;
    Entry* table;
    uint8_t hash_method;
} HashTable;

struct HashTable* HT_Create(uint8_t method, int init_size);
void              HT_Destroy(struct HashTable* ht);

void HT_Rehash     (struct HashTable* ht, int new_length);
void CheckAndRehash(struct HashTable* ht);

void HT_InsertLinear (int key, HashTable* ht);
void HT_InsertSquare (int key, HashTable* ht);
void HT_InsertTwoHash(int key, HashTable* ht);

int HT_SearchLinear       (int key, struct HashTable* ht);
int HT_SearchQuadratic    (int key, struct HashTable* ht);
int HT_SearchDoubleHashing(int key, struct HashTable* ht);

void HT_RemoveKey(int key, HashTable* ht);

#endif
