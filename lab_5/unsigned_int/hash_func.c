#include <math.h>
#include <stdio.h>

#define MODULE 1000

// Остаток от деления
unsigned int hash_remainder(unsigned int key) {
    return key % MODULE;
}

// Битовое представление
unsigned int hash_bitwise(unsigned int key) {
    long long result = 0;
    unsigned int base = 1;
    while (key > 0 && base < 10000) {
        if (key % 2 == 1) {
            result += base * 1;
        }
        base *= 10;
        key /= 2;
    }

    return (int)(result % MODULE);
}

// Метод умножения с константой
unsigned int HashMultiplication(unsigned int key) {
    double A = 0.618033;
    int h = MODULE * fmod(key * A, 1);

    return h;
}


