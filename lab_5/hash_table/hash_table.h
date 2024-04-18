#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdlib.h>
#include <stdbool.h>

const size_t HT_TABLE_SIZE        = 4001;
const size_t HT_TABLE_SIZE_SMALL  = 503;
const size_t HT_TABLE_SIZE_BIG    = 40001;
const int    START_CAPACITY       = 100;
typedef unsigned int key_type;
typedef unsigned value_type;
typedef struct Node Node;
typedef struct List List;

struct HashTable {
    size_t   length;
    List*    array;
    key_type (*hash_function)    (value_type value);
};

struct Node {
    value_type value;
    Node* next;
};

struct List {
    Node* fixedElement;
    int length;
    int capacity;
};

typedef struct HashTable HashTable;

HashTable* HT_Create();
void       HT_Add(value_type key, struct HashTable* ht);
bool       HT_ElementPresent(value_type key, struct HashTable* ht);
void       HT_Destroy       (HashTable* table);

List*      LST_Create();
void       LST_Add          (struct List* list, value_type value);
void       LST_Destroy      (List* list);

void CtorList(List* list);
void DtorList(List* list);
void PushElement(List* list, Node* position, char* value, Node** insertedValPtr);
void PopElement(List* list, Node* position);

#endif
