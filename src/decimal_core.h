#ifndef SRC_DECIMAL_CORE_H_
#define SRC_DECIMAL_CORE_H_

#include <stdio.h>
#include "s21_decimal.h"

#define _2(bit) (1 << (bit))

#define BITS 4
#define BITS_IN_INT 32
#define INFO_BIT 3
#define ALL_BIT (BITS_IN_INT * BITS)
#define START_EXP_BIT 16
#define END_EXP_BIT 23
#define ZERO_BIT 0
#define SIGN_BIT 31
#define OK 0
#define ERR 1

#define COLOR_HEADER "\033[95m"
#define COLOR_BLUE "\033[94m"
#define COLOR_CYAN "\033[96m"
#define COLOR_GREEN "\033[92m"
#define COLOR_ORANGE "\033[93m"
#define COLOR_RED "\033[91m"
#define COLOR_END "\033[0m"

int bit_on(int bits, int bit);
int bit_off(int bits, int bit);
int bit_swap(int bits, int bit);
int bit_is(int bits, int bit);
int get_global_bit(s21_decimal a, int gbit);
int get_bits(s21_decimal a, int gbit);
int get_bit(int bits, int bit);
int check_sign(s21_decimal a);
int chang_sign(s21_decimal* a);
s21_decimal nullify_all_decimal(s21_decimal *a);
int set_bit(int bits, int bit, int new_bit);
void print_decimal_bin(s21_decimal a); // for debug
int get_exp(s21_decimal decim);
int set_exp(s21_decimal* decim, int new_exp);

#endif  //  SRC_DECIMAL_CORE_H_
