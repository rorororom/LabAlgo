#ifndef IDEAL_HASH_H
#define IDEAL_HASH_H

struct node {
    int value;
    int flag_zero;
};

struct HashFuncData {
    int A;
    int B;
};

struct HashTable {
    struct HashData* table;
    struct HashFuncData data;
    int size;
};

struct HashData {
    struct HashFuncData data;
    struct node* arr;
    int size;
};

typedef int status_t;

enum STATUS {
    OK,
    ERROR
};

int HT_ID_Build(int* arr, int N, struct HashData* hashTable);
bool HT_ID_Search(struct HashData* hashTable, int value);

#endif
