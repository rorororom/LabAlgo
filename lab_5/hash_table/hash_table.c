#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "hash_table.h"
List* LST_Create() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->fixedElement = NULL;
    list->length = 0;
    list->capacity = START_CAPACITY;

    return list;
}

HashTable* HT_Create(key_type (*func)(value_type)) {
    HashTable* ht         = (HashTable*)calloc(1, sizeof(HashTable));
    ht->length            = HT_TABLE_SIZE_BIG;
    ht->hash_function     = func;
    ht->array = (List*)calloc(ht->length, sizeof(List));
    for (size_t i = 0; i < ht->length; ++i) {
        ht->array[i] = *LST_Create();
    }
    return ht;
}

void HT_Add(value_type key, struct HashTable* ht) {
    if (HT_ElementPresent(key, ht)) {                      // Проверка наличия элемента
        return;
    }

    key_type hash = ht->hash_function(key) % ht->length;
    LST_Add(&ht->array[hash], key);
}

void LST_Add(struct List* list, value_type value) {
    assert(list);
    Node* new_node = (Node*)malloc(sizeof(Node));
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

bool HT_ElementPresent(value_type key, struct HashTable* ht) {
    key_type hash = ht->hash_function(key) % ht->length;
    struct List* list = &ht->array[hash];
    assert (list);
    Node* current = list->fixedElement;
    while (current != NULL) {
        if (current->value == key) {
            return true;                            // Элемент уже присутствует в списке
        }
        current = current->next;
    }
    return false;                                   // Элемент не найден
}

void HT_Destroy(HashTable* table) {
    for (size_t i = 0; i < table->length; i++) {
        List* current = &table->array[i];

        while (current != NULL) {
            LST_Destroy(current);
        }

    }
    free(table->array);
    free(table);
}

void LST_Destroy(List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->fixedElement;
    while (current != NULL) {
        Node* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

}

static void ListElemCtor(Node** elem);
void ListElemInit(Node* elem, value_type value, Node* next);
static void ListElemDtor(Node* elem);

void CtorList(List* list) {
    assert(list);

    Node* zeroElement = NULL;
    ListElemCtor(&zeroElement);

    list->fixedElement = zeroElement;
    list->length = 0;
}

static void ListElemCtor(Node** elem) {
    assert(elem);

    *elem = (Node*)calloc(1, sizeof(Node));

    if (*elem == NULL) {
        printf("error memory limit\n");
        exit(1);
    }

    (*elem)->value = NULL;
    (*elem)->next = NULL;
}

void DtorList(List* list) {
    assert(list);

    Node* listHead = list->fixedElement;

    while (listHead != NULL) {
        Node* temp = listHead;
        listHead = listHead->next;
        ListElemDtor(temp);
    }

    list->fixedElement = NULL;
}

void PushElement(List* list, Node* position, char* value, Node** insertedValPtr) {
    assert(list);
    assert(position);
    assert(insertedValPtr);

    Node* newNode = NULL;
    ListElemCtor(&newNode);

    *insertedValPtr = newNode;

    ListElemInit(newNode, value, position->next);
    position->next = newNode;

    list->length++;
}

void ListElemInit(Node* elem, value_type value, Node* next) {
    assert(elem);

    elem->value = value;
    elem->next = next;
}

void PopElement(List* list, Node* position) {
    assert(list);
    assert(position);

    Node* current = list->fixedElement;
    while (current->next != position) {
        current = current->next;
    }

    current->next = position->next;
    ListElemDtor(position);
    list->length--;
}

static void ListElemDtor(Node* elem) {
    assert(elem);

    free(elem->value);
    elem->next = NULL;
    free(elem);
}
