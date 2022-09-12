#include "decimal_core.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal decim, s21_decimal *result_decimal) {
  nullify_all_decimal(result_decimal);
  chang_sign(&decim);
  *result_decimal = decim;
  return 0;
}

int s21_truncate(s21_decimal decim, s21_decimal *result_decimal) {
  return truncate_to_exp(decim, 0, result_decimal);
}
int s21_round(s21_decimal decim, s21_decimal *result_decimal) {
  return 0;
}
int s21_floor(s21_decimal decim, s21_decimal *result_decimal) {

  return 0;
}