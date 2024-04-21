#ifndef HASH_FUNC_INT_H
#define HASH_FUNC_INT_H

#include "open_hash.h"

int hash_multiplication(int key, struct HashTable* ht);
int hash_bitwise(int key, struct HashTable* ht);
int hash_remainder(int key, struct HashTable* ht);

#endif
