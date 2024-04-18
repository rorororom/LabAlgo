#define MODULE 1000

//Битовое представление
unsigned int hash_int_representation(float key) {
    unsigned int int_representation = *(unsigned int*)&key;

    return int_representation % MODULE;
}

// Извлечение мантиссы
unsigned int hash_mantissa(unsigned int key, unsigned int table_size) {
    unsigned int mantissa_mask = 0x007FFFFF;
    unsigned int mantissa = key & mantissa_mask;
    return mantissa % MODULE;
}

// Извлечение экспоненты
unsigned int hash_exponent(unsigned int key, unsigned int table_size) {
    unsigned int exponent_mask = 0x7F800000;
    unsigned int exponent = (key & exponent_mask) >> 23;
    return exponent % MODULE;
}

// Произведение мантиссы на экспоненту.
unsigned int hash_mantissa_times_exponent(unsigned int key, unsigned int table_size) {
    unsigned int mantissa_mask = 0x007FFFFF;
    unsigned int mantissa = key & mantissa_mask;

    unsigned int exponent_mask = 0x7F800000;
    unsigned int exponent = (key & exponent_mask) >> 23;

    return (mantissa * exponent) % MODULE;
}
