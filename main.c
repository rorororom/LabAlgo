#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "testing/testing.h"

int main() {
    testing("array_tests", BuildHeapLinearly,    "BuildHeapLinearly",    100000, 1000000, 100000);
    testing("array_tests", BuildHeapByInsertion, "BuildHeapByInsertion", 100000, 1000000, 100000);
}
