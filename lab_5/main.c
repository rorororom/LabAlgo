#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "unsigned_int/hash_func.h"
#include "hash_table/hash_table.h"
#include "testing/testing.h"

// int main() {
//     testing("array_tests", hash_remainder, "hash_remainder", 1000);
//     // testing("array_tests", HeapLine,      "heapLine",      100000, 1000000, 100000);
// }

int main()
{
    FILE* file = fopen("array_tests/unsigned_int.in", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    struct HashTable* ht = HT_Create((*)(key_type) *value_type(hash_remainder));

    for (size_t i = 0; i < 1000000; i++) {
        
    }

    for (size_t i = 0; i < source.words; i++) {
        HT_Add(source.textArray[i], ht);
    }

    writeToFile("output7.txt", ht);
    dispersion(ht);

    return 0;
}

void writeToFile(const char* filename, struct HashTable* ht) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    int max = 0;
    int max_i = 0;
    for (size_t i = 0; i < ht->length; i++) {
        if (max < ht->array[i].length) {
            max = ht->array[i].length;
            max_i = i;
        }
        fprintf(file, "%zu %d\n", i, ht->array[i].length);
    }

    printf("%d %d\n", max, max_i);
    fclose(file);
}
