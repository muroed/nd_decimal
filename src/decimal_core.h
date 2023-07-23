#ifndef SRC_DECIMAL_CORE_H_
#define SRC_DECIMAL_CORE_H_

typedef struct {
  int bits[4];
} nd_decimal;

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define _2(bit) (1 << (bit))

#define BITS 4
#define BITS_IN_INT 32
#define INFO_BIT 3
#define ALL_BIT (BITS_IN_INT * INFO_BIT)
#define START_EXP_BIT 16
#define END_EXP_BIT 23
#define ZERO_BIT 0
#define SIGN_BIT 31
#define OK 0
#define ERR 1
#define MAX_EXP 28
#define NEG_INF -1.0 / 0.0
#define nd_NAN 0.0 / 0.0

#define COLOR_HEADER "\033[95m"
#define COLOR_BLUE "\033[94m"
#define COLOR_CYAN "\033[96m"
#define COLOR_GREEN "\033[92m"
#define COLOR_ORANGE "\033[93m"
#define COLOR_RED "\033[91m"
#define COLOR_END "\033[0m"
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f
#define nd_MAX_UINT 4294967295

int bit_on(int bits, int bit);
int bit_off(int bits, int bit);
int bit_swap(int bits, int bit);
int bit_is(int bits, int bit);
int get_global_bit(nd_decimal decim, int gbit);
int set_global_bit(nd_decimal *decim, int gbit, int new_bit);
int get_bits(nd_decimal decim, int gbit);
int get_bit(int bits, int bit);
int check_sign(nd_decimal decim);
int chang_sign(nd_decimal *decim);
int set_sign(nd_decimal *decim, int sign);
nd_decimal nullify_all_decimal(nd_decimal *decim);
int is_null_decimal(nd_decimal decim);
int is_null_decimal_bin(nd_decimal decim);
int set_bit(int bits, int bit, int new_bit);
// for debug
void print_decimal_bin(nd_decimal decim);
void print_decimal_int(nd_decimal decimal_int);
int get_exp(nd_decimal decim);
int set_exp(nd_decimal *decim, int new_exp);
int swap_int(int *value1, int *value2);
int truncate_to_exp(nd_decimal decim, int new_exp,
                    nd_decimal *result_decimal);

int swift_bits_right(int bits, int number);
nd_decimal bit_swift_right(nd_decimal decim, int number);
int bit_swift_left(nd_decimal decim, int number, nd_decimal *result);
nd_decimal bit_exclusive_or(nd_decimal decim1, nd_decimal decim2);
nd_decimal bit_and(nd_decimal decim1, nd_decimal decim2);
nd_decimal bit_negative(nd_decimal decim);
nd_decimal bit_or(nd_decimal decim1, nd_decimal decim2);
nd_decimal nd_decimal_get_inf(void);

int bank_round(nd_decimal *number, int n);
int bank_rounding(int a);
int balancing(nd_decimal *a, nd_decimal *b);
int shifting(nd_decimal *a, int n);
int nd_get_float_exp_from_string(char *str);
nd_decimal nd_float_string_to_decimal(char *str);
int nd_get_float_exp_from_string(char *str);
nd_decimal nd_decimal_get_from_char(char c);
nd_decimal nd_decimal_get_one(void);
nd_decimal nd_int128_get_ten_pow(int pow);

//степени числа 10
// 10 ^ pow

static const nd_decimal all_ten_pows[39] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
    [29] = {{0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x1}},
    [30] = {{0x40000000, 0x4674EDEA, 0x9F2C9CD0, 0xC}},
    [31] = {{0x80000000, 0xC0914B26, 0x37BE2022, 0x7E}},
    [32] = {{0x0, 0x85ACEF81, 0x2D6D415B, 0x4EE}},
    [33] = {{0x0, 0x38C15B0A, 0xC6448D93, 0x314D}},
    [34] = {{0x0, 0x378D8E64, 0xBEAD87C0, 0x1ED09}},
    [35] = {{0x0, 0x2B878FE8, 0x72C74D82, 0x134261}},
    [36] = {{0x0, 0xB34B9F10, 0x7BC90715, 0xC097CE}},
    [37] = {{0x0, 0xF436A0, 0xD5DA46D9, 0x785EE10}},
    [38] = {{0x0, 0x98A2240, 0x5A86C47A, 0x4B3B4CA8}}};

#endif  //  SRC_DECIMAL_CORE_H_
