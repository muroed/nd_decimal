#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include "decimal_core.h"

// typedef struct {
//     int bits[4];
// } s21_decimal;

//  comparison help
int is_less_lite(s21_decimal decim1, s21_decimal decim2);
int is_less_or_equal_lite(s21_decimal decim1, s21_decimal decim2);
int is_greater_lite(s21_decimal decim1, s21_decimal decim2);
int is_equal_lite(s21_decimal decim1, s21_decimal decim2);
//  comparison
int s21_is_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_not_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_greater_or_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_greater(s21_decimal decim1, s21_decimal decim2);
int s21_is_less_or_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_less(s21_decimal decim1, s21_decimal decim2);

// convert
int s21_from_int_to_decimal(int src_int, s21_decimal *dst_decimal);
int s21_from_float_to_decimal(float src_float, s21_decimal *dst_decimal);
int s21_from_decimal_to_int(s21_decimal src_decimal, int *dst_int);
int s21_from_decimal_to_float(s21_decimal src_decimal, float *dst_float);

// arifmetic help
int add_lite(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int add_sign(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int sub_lite(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int sub_sign(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
s21_decimal negative_decimal(s21_decimal decim);
int mul_lite(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int mul_sign(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int div_lite(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int div_exp(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);
int div_sign(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);
int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int additional_int_prec(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result, int status);
s21_decimal mod_lite(s21_decimal value_1, s21_decimal value_2);
int mod_sign(s21_decimal decim1, s21_decimal decim2,
             s21_decimal *result_decimal);

// arifmetic
int s21_add(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);
int s21_sub(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);
int s21_mul(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);
int s21_div(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);
int s21_mod(s21_decimal decim1, s21_decimal decim2,
            s21_decimal *result_decimal);

// another
int s21_negate(s21_decimal decim, s21_decimal *result_decimal);
int s21_truncate(s21_decimal decim, s21_decimal *result_decimal);
int s21_round(s21_decimal decim, s21_decimal *result_decimal);
int s21_floor(s21_decimal decim, s21_decimal *result_decimal);

#endif  //  SRC_S21_DECIMAL_H_
