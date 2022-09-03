
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

// add without degree and sign
int add_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
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

// add without degree
int add_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);

  if (sign_decim1 == 1 && sign_decim2 == 1) {
    chang_sign(result_decimal);
    error_mark = add_lite(decim1, decim2, result_decimal);
  } else if (sign_decim1 == 1) {
    chang_sign(&decim1);
    // error_mark = s21_sub(decim2, decim1, result_decimal);
  } else if (sign_decim2 == 1) {
    chang_sign(&decim2);
    // error_mark = s21_sub(decim1, decim2, result_decimal);
  } else {
    error_mark = add_lite(decim1, decim2, result_decimal);
  }
  return error_mark;
}
