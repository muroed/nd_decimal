#include "s21_decimal_tst.h"

START_TEST(s21_sub_tests_1) {
    int a = (int)Rand_R(-10e5, 10e1);
    int b = (int)Rand_R(-10e5, 10e1);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a - b, c);
}
END_TEST

START_TEST(s21_sub_tests_2) {
    int a = (int)Rand_R(0, 10e5);
    int b = (int)Rand_R(0, 10e5);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a - b, c);
}
END_TEST

START_TEST(s21_sub_tests_3) {
    float a = Rand_R(-10e8, 10e8);
    float b = Rand_R(-10e8, 10e8);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e2);
}
END_TEST

START_TEST(s21_sub_tests_4) {
    float a = Rand_R(-1000, 1000);
    float b = Rand_R(-1000, 1000);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e-1);
}
END_TEST

START_TEST(s21_sub_tests_5) {
    float a = 10e10;
    float b = 1e-10;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e5);
}
END_TEST

START_TEST(s21_sub_tests_6) {
    float a = 10e27;
    float b = 1e-10;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e-1);
}
END_TEST

START_TEST(s21_sub_tests_7) {
    float a = 10e-10;
    float b = 1e25;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e-1);
}
END_TEST

START_TEST(s21_sub_tests_8) {
    float a = 0;
    float b = 10e1;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e-1);
}
END_TEST

START_TEST(s21_sub_tests_9) {
    float a = 10e1;
    float b = 0;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a - b, c, 10e-1);
}
END_TEST

START_TEST(s21_sub_tests_10) {
    s21_decimal _a;
    _a.state = S21_NAN;
    s21_decimal _b;
    _b.state = S21_NORMAL;
    s21_decimal res;

    ck_assert_int_eq(s21_sub(_a, _b, &res), 3);
}
END_TEST

START_TEST(s21_sub_tests_11) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_sub(_a, _b, &res), 3);
}
END_TEST

START_TEST(s21_sub_tests_12) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_PLUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_sub(_a, _b, &res), 1);
}
END_TEST

START_TEST(s21_sub_tests_13) {
    s21_decimal _a;
    _a.state = S21_MINUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_sub(_a, _b, &res), 2);
}
END_TEST

START_TEST(s21_sub_tests_14) {
    float a = 512;
    float b = 1;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    for (int i = 0; i < 9; ++i) {
        s21_left_shift(&_a);
    }
    s21_set_scale(&_a, s21_get_scale(_a) + 9);
    s21_sub(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
}
END_TEST

Suite *suite_s21_sub_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_sub");
    tc = tcase_create("case_sub");

    tcase_add_loop_test(tc, s21_sub_tests_1, 0, 1000);
    tcase_add_loop_test(tc, s21_sub_tests_2, 0, 1000);
    tcase_add_loop_test(tc, s21_sub_tests_3, 0, 1000);
    tcase_add_loop_test(tc, s21_sub_tests_4, 0, 1000);
    tcase_add_test(tc, s21_sub_tests_5);
    tcase_add_test(tc, s21_sub_tests_6);
    tcase_add_test(tc, s21_sub_tests_7);
    tcase_add_test(tc, s21_sub_tests_8);
    tcase_add_test(tc, s21_sub_tests_9);
    tcase_add_test(tc, s21_sub_tests_10);
    tcase_add_test(tc, s21_sub_tests_11);
    tcase_add_test(tc, s21_sub_tests_12);
    tcase_add_test(tc, s21_sub_tests_13);
    tcase_add_test(tc, s21_sub_tests_14);
    suite_add_tcase(s, tc);
    return s;
}
