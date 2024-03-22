#include <stdio.h>
#include <stdlib.h>

#include "sorts/p1_quadraticSort.h"
#include "sorts/p2_heapSort.h"
#include "sorts/p3_mergeSort.h"
#include "sorts/p4_fastSort.h"
#include "sorts/p5_quickSortDifferPivot.h"
#include "sorts/p6_introSort.h"
#include "sorts/p7_introspectiveSort.h"
#include "sorts/p8_LSD_MSD.h"

#include "testing/testing.h"

int main() {
    testing("big_tests", LSDsort, "big_tests_qs2", "LSD", 0, 1000000, 10000, 5);
    testing("big_tests", LSDsort, "big_tests_qs2", "MSD", 0, 1000000, 10000, 5);
}


