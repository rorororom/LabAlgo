#ifndef TESTING_H
#define TESTING_H

#include <stdlib.h>

typedef void (*HeapFunction)(int*, size_t);

void testing(const char *testFolder, HeapFunction heapFunction,
             const char *nameFileForTime, size_t from, size_t to, size_t step);
#endif
