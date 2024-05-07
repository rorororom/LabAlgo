#ifndef HASH_FUNC_INT_H
#define HASH_FUNC_INT_H
#include <stdlib.h>
#include "metod_chain.h"

size_t HashFunc(Coeff* c, int key, size_t size);
int HashFuncDreams(int key, int length);
int HashMultiplication(int key, int length);

struct Coeff* HashGetCoeff(size_t size);
#endif
