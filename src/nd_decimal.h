#ifndef SRC_nd_DECIMAL_H_
#define SRC_nd_DECIMAL_H_

#include "decimal_core.h"

// typedef struct {
//     int bits[4];
// } nd_decimal;

//  comparison help
int is_less_lite(nd_decimal decim1, nd_decimal decim2);
int is_less_or_equal_lite(nd_decimal decim1, nd_decimal decim2);
int is_greater_lite(nd_decimal decim1, nd_decimal decim2);
int is_equal_lite(nd_decimal decim1, nd_decimal decim2);
//  comparison
int nd_is_equal(nd_decimal decim1, nd_decimal decim2);
int nd_is_not_equal(nd_decimal decim1, nd_decimal decim2);
int nd_is_greater_or_equal(nd_decimal decim1, nd_decimal decim2);
int nd_is_greater(nd_decimal decim1, nd_decimal decim2);
int nd_is_less_or_equal(nd_decimal decim1, nd_decimal decim2);
int nd_is_less(nd_decimal decim1, nd_decimal decim2);

// convert
int nd_from_int_to_decimal(int src_int, nd_decimal *dst_decimal);
int nd_from_float_to_decimal(float src_float, nd_decimal *dst_decimal);
int nd_from_decimal_to_int(nd_decimal src_decimal, int *dst_int);
int nd_from_decimal_to_float(nd_decimal src_decimal, float *dst_float);

// arifmetic help
int add_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int add_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int sub_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int sub_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
nd_decimal negative_decimal(nd_decimal decim);
int mul_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int mul_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int div_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int div_exp(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);
int div_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);
int int_div(nd_decimal value_1, nd_decimal value_2, nd_decimal *result);
int additional_int_prec(nd_decimal value_1, nd_decimal value_2,
                        nd_decimal *result, int status);
nd_decimal mod_lite(nd_decimal value_1, nd_decimal value_2);
int mod_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal *result_decimal);

// arifmetic
int nd_add(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);
int nd_sub(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);
int nd_mul(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);
int nd_div(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);
int nd_mod(nd_decimal decim1, nd_decimal decim2,
            nd_decimal *result_decimal);

// another
int nd_negate(nd_decimal decim, nd_decimal *result_decimal);
int nd_truncate(nd_decimal decim, nd_decimal *result_decimal);
int nd_round(nd_decimal decim, nd_decimal *result_decimal);
int nd_floor(nd_decimal decim, nd_decimal *result_decimal);

#endif  //  SRC_nd_DECIMAL_H_
