#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap/heap_build.h"
#include "testing/testing.h"

int main() {
    testing("array_tests", HeapInsertion, "heapInsertion", 100000, 1000000, 100000);
    testing("array_tests", HeapLine,      "heapLine",      100000, 1000000, 100000);
}
