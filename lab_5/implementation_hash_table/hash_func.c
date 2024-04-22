#include "hash_func.h"
#include <math.h>
#include <assert.h>

int hash_multiplication(int key, int length) {
    double A = 0.618033; // константа предложена Кнутом (см. Томас Кормен стр. 296)
    int h = (int)(((long double)(length) * fmod(key * A, 1))) % (int)(length);

    return h;
}

int hash_bitwise(int key, int length) {
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

    return (int)(result % length);
}


int hash_remainder(int key, int length) {
    return key % length;
}
