#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H
#include <stdlib.h>

const int SIZE_DATA      = 20;
const int NOW_DATA       = 10;
const int WANT_COUNT_ADD = 10;
const int FREE_ELEMENT   = -1;
const int ZERO_ELEMENT   = 0;

typedef struct Node Node;
typedef struct List List;
typedef unsigned value_type;

struct Node {
    value_type value;
    Node* next;
};

struct List {
    Node* fixedElement;
    int length;
    int capacity;
};

#endif
