#ifndef HASH_FUNC_FLOAT_H
#define HASH_FUNC_FLOAT_H

unsigned int hash_int_representation(float key);
unsigned int hash_mantissa(float key, unsigned int table_size);
unsigned int hash_exponent(float key, unsigned int table_size);
unsigned int hash_mantissa_times_exponent(float key, unsigned int table_size);
unsigned int hash_float_bitwise(float key);

#endif
