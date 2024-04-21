#ifndef IDEAL_HASH_H
#define IDEAL_HASH_H

struct node {
    int value;
    int flag_zero;
};

struct HashTable {
    struct arrHash2* table;
    int size;
    int A;
    int B;
    int P;
};

struct arrHash2 {
    int A;
    int B;
    int P;
    struct node* arr;
    int size;
};

typedef int status_t;

enum STATUS {
    OK,
    ERROR
};

int HT_ID_Build(int* arr, int N, struct arrHash2* hashTable);
bool HT_ID_Search(struct arrHash2* hashTable, int value);

#endif
