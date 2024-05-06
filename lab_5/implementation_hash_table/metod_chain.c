#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "metod_chain.h"
#include "hash_func.h"

const int   CNT_ELEMENT     = 1000000;
const int   REHASH_FACTOR   = 2;
const float LOAD_FACTOR_HTC = 0.75; // Hash Table method Chain

//====================================================================================
//==================================CTOR_DTOR=========================================
//====================================================================================

List* LST_Create() {
    List* list = (List*)malloc(sizeof(List));
    assert(list);

    list->fixedElement = NULL;
    list->length = 0;

    return list;
}

struct HashTable* HT_CH_Create(int init_capacity) {
    struct HashTable* ht = (struct HashTable*)calloc(1, sizeof(struct HashTable));
    assert(ht);

    ht->length = init_capacity;
    ht->array = (List*)calloc(ht->length, sizeof(List));
    assert(ht->array);

    int size = 0;
    for (int i = 0; i < ht->length; ++i) {
        ht->array[i] = *LST_Create();
    }

    ht->coeff = HashGetCoeff(init_capacity);

    return ht;
}

void LST_Destroy(List* list) {
    Node* current = list->fixedElement;
    while (current != NULL) {
        Node* next = current->next;
        current->value = 0;
        free(current);
        current = next;
    }
}


void HT_CH_Destroy(struct HashTable* ht) {
    assert(ht);

    for (int i = 0; i < ht->length; ++i) {
        List* list = &ht->array[i];
        LST_Destroy(list);
    }

    ht->coeff->A = 0;
    ht->coeff->B = 0;
    ht->coeff->P = 0;
    ht->size = 0;
    ht->length = 0;
    free(ht->array);
    free(ht);

    ht->array = NULL;
    ht = NULL;
}

//====================================================================================
//==================================REHASH============================================
//====================================================================================

void HT_CH_Rehash(struct HashTable* ht) {
    assert(ht);

    size_t new_length = ht->length * REHASH_FACTOR;
    List* new_array = (List*)calloc(new_length, sizeof(List));
    assert(new_array);

    for (size_t i = 0; i < ht->length; ++i) {
        List* current_list = &ht->array[i];
        Node* current_node = current_list->fixedElement;

        while (current_node != NULL) {
            int new_hash = HashFunc(ht->coeff, current_node->value, new_length) % new_length;
            LST_Add(&new_array[new_hash], current_node->value);

            current_node = current_node->next;
        }
    }

    free(ht->array);

    ht->array = new_array;
    ht->length = new_length;
}

void RehashIfNeeded(struct HashTable* ht) {
    assert(ht);

    float load_factor = (float)ht->size / ht->length;
    if (load_factor > LOAD_FACTOR_HTC) {
        HT_CH_Rehash(ht);
    }
}

//====================================================================================
//==================================SEARCH============================================
//====================================================================================

bool HT_CH_Search(int key, struct HashTable* ht) {
    assert(ht);

    int hash = HashFunc(ht->coeff, key, ht->length) % ht->length;
    List* list = &ht->array[hash];
    Node* current = list->fixedElement;

    while (current != NULL) {
        if (current->value == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}


//====================================================================================
//==================================INSERT============================================
//====================================================================================

void LST_Add(struct List* list, int value) {
    assert(list);

    Node* new_node = (Node*)malloc(sizeof(Node));
    assert(new_node);

    new_node->value = value;
    new_node->next = NULL;

    if (list->fixedElement == NULL) {
        list->fixedElement = new_node;
    } else {
        Node* current = list->fixedElement;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}


void HT_CH_Insert(int key, struct HashTable* ht) {
    assert(ht);

    if (HT_CH_Search(key, ht)) {
        return;
    }

    RehashIfNeeded(ht);

    int hash = HashFunc(ht->coeff, key, ht->length) % ht->length;

    if (ht->array[hash].fixedElement == NULL) {
        LST_Add(&ht->array[hash], key);
    } else {
        Node* current = ht->array[hash].fixedElement;
        while (current != NULL) {
            if (current->value == key) {
                return;
            }
            current = current->next;
        }

        LST_Add(&ht->array[hash], key);
    }
    ht->size++;
}

//====================================================================================
//==================================REMOVE============================================
//====================================================================================

void HT_CH_RemoveKey(int key, struct HashTable* ht) {
    assert(ht);

    if (!HT_CH_Search(key, ht))
        return;

    int hash = HashFunc(ht->coeff, key, ht->length) % ht->length;
    List* list = &ht->array[hash];
    Node* current = list->fixedElement;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value == key) {
            if (prev == NULL) {
                list->fixedElement = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
