#ifndef SRC_TESTS_S21_DECIMAL_H_
#define SRC_TESTS_S21_DECIMAL_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../s21_decimal.h"
#define _EPS (10e3)

Suite *suite_s21_decimal_test(void);
Suite *suite_s21_from_int_to_decimal_ste(void);
Suite *suite_s21_from_float_to_decimal_ste(void);
Suite *suite_s21_set_scale_ste(void);
Suite *suite_s21_from_decimal_to_float_ste(void);
Suite *suite_s21_from_decimal_to_int_ste(void);
Suite *suite_s21_is_greater_ste(void);
Suite *suite_s21_is_equal_ste(void);
Suite *suite_s21_add_ste(void);
Suite *suite_s21_is_not_equal_ste(void);
Suite *suite_s21_is_greater_or_equal_ste(void);
Suite *suite_s21_is_less_ste(void);
Suite *suite_s21_is_less_or_equal_ste(void);
Suite *suite_s21_sub_ste(void);
Suite *suite_s21_round_ste(void);
Suite *suite_s21_mul_ste(void);
Suite *suite_s21_div_ste(void);
Suite *suite_s21_mod_ste(void);
Suite *suite_s21_truncate_ste(void);
Suite *suite_s21_floor_ste(void);

float Rand_R(float a, float b);
void run_tests(void);
void run_testcase(Suite *tc);

#endif  // TESTS_S21_DECIMAL_TST_H_
