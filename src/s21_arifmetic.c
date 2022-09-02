
#include "decimal_core.h"
#include "s21_decimal.h"

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

int s21_add(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  unsigned int error_mark = 0;
  
}
