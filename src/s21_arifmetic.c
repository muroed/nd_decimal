
#include "decimal_core.h"
#include "s21_decimal.h"


// https://russianblogs.com/article/568550142/


// int add(int num1, int num2) {
//     int res = 0, carry = 0;
//     res = num1^num2;
//     carry = (num1&num2) << 1;
//     while (carry) {
//         int tmp = res;
//         res = res^carry;
//         carry = (tmp&carry) << 1;
//     }
//     return res;
// }

// add without degree
int s21_add_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  unsigned int error_mark = 0;
  s21_decimal carry;
  nullify_all_decimal(result_decimal);
  nullify_all_decimal(&carry);

  *result_decimal = bit_exclusive_or(decim1, decim2);
  error_mark = bit_swift_left(bit_and(decim1, decim2), 1, &carry);
  while (is_null_decimal(carry) == 0 && error_mark == 0) {
    s21_decimal tmp = *result_decimal;
    *result_decimal = bit_exclusive_or(*result_decimal, carry);
    error_mark = bit_swift_left(bit_and(tmp, carry), 1, &carry);
  }
  return error_mark;
}
