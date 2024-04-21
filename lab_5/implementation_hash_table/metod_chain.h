#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdlib.h>

//===============================================================================
//=============================Struct List=======================================
//===============================================================================

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* fixedElement;
    int length;
} List;

//===============================================================================
//=============================HT_TABLE====================================
//===============================================================================

struct HashTable {
    size_t   length;
    List*    array;
    size_t   size;
};

List* LST_Create();
struct HashTable* HT_CH_Create(int init_capacity);
void LST_Destroy(List* list);
void HT_CH_Destroy(struct HashTable* ht);

void HT_CH_Rehash  (struct HashTable* ht);
void RehashIfNeeded(struct HashTable* ht);

bool HT_CH_Search(int key, struct HashTable* ht);

void LST_Add     (struct List* list, int value);
void HT_CH_Insert(int key, struct HashTable* ht);

void HT_CH_RemoveKey(int key, struct HashTable* ht);

#endif
