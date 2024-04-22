#ifndef HASH_FUNC_INT_H
#define HASH_FUNC_INT_H

#include "open_hash.h"

int hash_multiplication(int key, int length);
int hash_bitwise       (int key, int length);
int hash_remainder     (int key, int length);

#endif
