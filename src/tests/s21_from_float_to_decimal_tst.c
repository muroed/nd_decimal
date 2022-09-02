#include "s21_decimal_tst.h"

START_TEST(s21_from_float_to_decimal_1) {
    s21_decimal var;
    ck_assert_int_eq(s21_from_float_to_decimal(1e-29, &var), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
    s21_decimal var;
    ck_assert_int_eq(s21_from_float_to_decimal(79238162514264337593543950335.0, &var), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
    s21_decimal var;
    ck_assert_int_eq(s21_from_float_to_decimal(-79338162514264337593543950335.0, &var), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
    s21_decimal var;
    ck_assert_int_eq(s21_from_float_to_decimal(1e-25, &var), 0);
    float a = 0;
    s21_from_decimal_to_float(var, &a);
    ck_assert_float_eq(a, 1e-25);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
    float n = Rand_R(-10, 10);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(n, value, 1e-8);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
    float n = Rand_R(-10000000, 100000000);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(n, value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
    s21_decimal res;
    float n = 0.000000000000000000000000001;
    s21_from_float_to_decimal(n, &res);
    float x = 0.00000000000000000000000000000001;
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq(n, x);
}
END_TEST

Suite *suite_s21_from_float_to_decimal_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_from_float_to_decimal");
    tc = tcase_create("case_from_float_to_decimal");

    tcase_add_test(tc, s21_from_float_to_decimal_1);
    tcase_add_test(tc, s21_from_float_to_decimal_2);
    tcase_add_test(tc, s21_from_float_to_decimal_3);
    tcase_add_test(tc, s21_from_float_to_decimal_4);
    tcase_add_loop_test(tc, s21_from_float_to_decimal_5, 0, 1000);
    tcase_add_loop_test(tc, s21_from_float_to_decimal_6, 0, 1000);
    tcase_add_test(tc, s21_from_float_to_decimal_7);
    suite_add_tcase(s, tc);
    return s;
}
