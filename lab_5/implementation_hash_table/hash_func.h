#ifndef HASH_FUNC_INT_H
#define HASH_FUNC_INT_H
#include <stdlib.h>
#include "open_hash.h"

size_t HashFunc(Coeff* c, int key, size_t size);
int hash_func_dreams(int key, int length);
int hash_multiplication(int key, int length);

struct Coeff* HashGetCoeff(size_t size);
#endif
