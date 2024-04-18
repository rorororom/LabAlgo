#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "struct_list.h"
#include "hash_table.h"

static void ListElemCtor(Node** elem);
static void ListElemInit(Node* elem, char* value, Node* next);
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
