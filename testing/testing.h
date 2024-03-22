#ifndef TESTING_H
#define TESTING_H

#include <stdlib.h>

typedef void (*SortFunction)(int*, size_t);

void testSorting(const char *testFolder, SortFunction sortFunc, const char *resultPath);
void testing(const char *testFolder, SortFunction sortFunc, const char *resultPath,
             const char *nameFileForTime, size_t from, size_t to, size_t step, size_t k);
void compareFiles(const char* file1, const char* file2);
#endif
