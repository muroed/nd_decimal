#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

// #include "decimal_core.h"

typedef struct {
    int bits[4];
} s21_decimal;

int s21_is_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_not_equal(s21_decimal decim1, s21_decimal decim2);
int s21_is_greater(s21_decimal decim1, s21_decimal decim2);

#endif  //  SRC_S21_DECIMAL_H_
