#include "hash_func.h"
#include <math.h>
#include <assert.h>

int hash_multiplication(int key, struct HashTable* ht) {
    assert(ht);
    double A = 0.618033;
    int h = (int)(((long double)(ht->length) * fmod(key * A, 1))) % (int)(ht->length);

    return h;
}

int hash_bitwise(int key, struct HashTable* ht) {
    assert(ht);

    if (key == 0)
        return 0;

    long long result = 0;
    int shift = 0;

    while (key > 0) {
        unsigned int bit = key % 2;
        result |= bit << shift;
        key /= 2;
        shift++;
    }

    return (int)(result % ht->length);
}


int hash_remainder(int key, struct HashTable* ht) {
    assert(ht);
    
    return key % ht->length;
}
