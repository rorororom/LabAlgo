#include <stdint.h>
#include <stdio.h>

#define MODULE 1000

//Битовое представление
unsigned int hash_int_representation(float key) {
    unsigned int int_representation = *(unsigned int*)&key;

    long long result = 0;
    unsigned int base = 1;
    while (int_representation > 0 && base < 10000) {
        if (int_representation % 2 == 1) {
            result += base * 1;
        }
        base *= 10;
        int_representation  /= 2;
    }

    return (int)(result % MODULE);
}


unsigned int hash_float_bitwise(float key) {
    if (key == 0.0f)
        return 0;

    uint32_t *ptr = (uint32_t *)&key;
    uint32_t bits = *ptr;

    int result = 0;
    int base = 1;
    for (int i = 31; i >= 29; i--) {
        result += ((bits >> i) & 1) * base;
        base *= 10;
    }

    return result;
}

typedef union {
  float f;
  struct {
    unsigned int mantissa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
} float_cast;

// Извлечение мантиссы
unsigned int hash_mantissa(float key, unsigned int table_size) {
    float_cast data;
    data.f = key;
    return data.parts.mantissa % MODULE;
}

int cnt = 0;
// Извлечение экспоненты
unsigned int hash_exponent(float key, unsigned int table_size) {
    float_cast data;
    data.f = key;
    int ans = data.parts.exponent % 1000;
    if (cnt < 10) {
        printf("%f %d\n", key, ans);
        cnt++;
    }
    return ans;
}

// Произведение мантиссы на экспоненту.
unsigned int hash_mantissa_times_exponent(float key, unsigned int table_size) {
    unsigned int mantissa = hash_mantissa(key, table_size);
    unsigned int exponent = hash_exponent(key, table_size);

    return (mantissa * exponent) % MODULE;
}
