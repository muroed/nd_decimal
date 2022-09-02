#include "s21_decimal_tst.h"

START_TEST(s21_from_decimal_to_float_1) {
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(5.0, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
    float n = Rand_R(-8388608, 8388608);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
    float n = Rand_R(-10, 10);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(n, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
    s21_decimal var;
    var.state = S21_NULL;
    float value = 0;
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
    float n = 0;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(n, value, 10e-5);
    ck_assert_int_eq(var.state, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
    float n = 79238162514264337593543950335.0;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_int_eq(var.state, S21_PLUS_INF);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
    float n = -79238162514264337593543950335.0;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_int_eq(var.state, S21_MINUS_INF);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
    float n = 0.0 / 0.0;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_int_eq(var.state, S21_NAN);
}
END_TEST

Suite *suite_s21_from_decimal_to_float_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_from_decimal_to_float");
    tc = tcase_create("case_from_decimal_to_float");

    tcase_add_test(tc, s21_from_decimal_to_float_1);
    tcase_add_loop_test(tc, s21_from_decimal_to_float_2, 0, 1000);
    tcase_add_loop_test(tc, s21_from_decimal_to_float_3, 0, 1000);
    tcase_add_test(tc, s21_from_decimal_to_float_4);
    tcase_add_test(tc, s21_from_decimal_to_float_5);
    tcase_add_test(tc, s21_from_decimal_to_float_6);
    tcase_add_test(tc, s21_from_decimal_to_float_7);
    tcase_add_test(tc, s21_from_decimal_to_float_8);

    suite_add_tcase(s, tc);
    return s;
}
