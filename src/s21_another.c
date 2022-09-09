#include "decimal_core.h"
#include "s21_decimal.h"

int s21_negative(s21_decimal decim, s21_decimal *result_decimal) {
  nullify_all_decimal(result_decimal);
  chang_sign(&decim);
  *result_decimal = decim;
  return 0;
}