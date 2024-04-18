#ifndef TESTING_H
#define TESTING_H

#include <stdlib.h>
#include "../hash_table/hash_table.h"

typedef  (*hash_function)(key_type, value_type);

void testing(const char *testFolder, hash_function hashFunc,
             const char *nameFileForTime, size_t size);
#endif
