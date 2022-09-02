#include "s21_decimal_tst.h"

START_TEST(s21_round_test_1) {
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(5.5, &var);
    s21_round(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(6.0, value, 10e-5);
}
END_TEST

START_TEST(s21_round_test_2) {
    float n = Rand_R(-8388608, 8388608);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_round(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(round(n), value, 10);
}
END_TEST

Suite *suite_s21_round_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_s21_round");
    tc = tcase_create("case_round");

    tcase_add_test(tc, s21_round_test_1);
    tcase_add_loop_test(tc, s21_round_test_2, 0, 1000);
    suite_add_tcase(s, tc);
    return s;
}
