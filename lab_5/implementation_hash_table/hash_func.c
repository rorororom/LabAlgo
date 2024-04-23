#include "hash_func.h"
#include <math.h>
#include <assert.h>

const int CONST_COEFF_A = 31;
const int CONST_COEFF_B = 103;

int hash_multiplication(int key, int length) {
    double A = 0.618033; // константа предложена Кнутом (см. Томас Кормен стр. 296)
    int h = (int)(((long double)(length) * fmod(key * A, 1))) % (int)(length);

    return h;
}

int hash_func_dreams(int key, int length) {
    int hash = (key + 1) % (length - 1);
    return hash;
}


int hash_remainder(int key, int length) {
    return key % length;
}
