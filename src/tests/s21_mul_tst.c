#include "s21_decimal_tst.h"

START_TEST(s21_mul_tests_1) {
    int a = (int)Rand_R(-10e3, 10e3);
    int b = (int)Rand_R(-10e3, 10e3);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a * b, c);
}
END_TEST

START_TEST(s21_mul_tests_2) {
    int a = (int)Rand_R(0, 10e3);
    int b = (int)Rand_R(0, 10e3);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    if (a * b != (int)(c)) {
        printf("%d * %d\n", a, b);
    }
    ck_assert_int_eq(a * b, (int)(c));
}
END_TEST

START_TEST(s21_mul_tests_3) {
    float a = Rand_R(-10e8, 10e8);
    float b = Rand_R(-10e8, 10e8);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a * b, c, 10e10);
}
END_TEST

START_TEST(s21_mul_tests_4) {
    float a = Rand_R(-1000, 1000);
    float b = Rand_R(-1000, 1000);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a * b, c, 10e-1);
}
END_TEST

START_TEST(s21_mul_tests_5) {
    int a = 9999999;
    float b = Rand_R(10e-20, 10e-5);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);

    ck_assert_float_eq_tol(a * b, c, 10e-1);
}
END_TEST

START_TEST(s21_mul_tests_6) {
    float a = 0;
    float b = 10e1;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a * b, c, 10e-1);
}
END_TEST

START_TEST(s21_mul_tests_7) {
    float a = 10e1;
    float b = 0;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a * b, c, 10e-1);
}
END_TEST

START_TEST(s21_mul_tests_8) {
    s21_decimal _a;
    _a.state = S21_NAN;
    s21_decimal _b;
    _b.state = S21_NORMAL;
    s21_decimal res;

    ck_assert_int_eq(s21_mul(_a, _b, &res), 3);
}
END_TEST

START_TEST(s21_mul_tests_9) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_mul(_a, _b, &res), 2);
}
END_TEST

START_TEST(s21_mul_tests_10) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_PLUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_mul(_a, _b, &res), 1);
}
END_TEST

START_TEST(s21_mul_tests_11) {
    s21_decimal _a;
    _a.state = S21_MINUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_mul(_a, _b, &res), 1);
}
END_TEST

START_TEST(s21_mul_tests_12) {
    float a = 10e27;
    float b = 10e27;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    int x = s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_int_eq(1, x);
}
END_TEST

START_TEST(s21_mul_tests_13) {
    float a = -10e27;
    float b = 10e27;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    int x = s21_mul(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_int_eq(2, x);
}
END_TEST

Suite *suite_s21_mul_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_mul");
    tc = tcase_create("case_mul");

    tcase_add_loop_test(tc, s21_mul_tests_1, 0, 1000);
    tcase_add_loop_test(tc, s21_mul_tests_2, 0, 1000);
    tcase_add_loop_test(tc, s21_mul_tests_3, 0, 1000);
    tcase_add_loop_test(tc, s21_mul_tests_4, 0, 1000);
    tcase_add_loop_test(tc, s21_mul_tests_5, 0, 1000);
    tcase_add_test(tc, s21_mul_tests_6);
    tcase_add_test(tc, s21_mul_tests_7);
    tcase_add_test(tc, s21_mul_tests_8);
    tcase_add_test(tc, s21_mul_tests_9);
    tcase_add_test(tc, s21_mul_tests_10);
    tcase_add_test(tc, s21_mul_tests_11);
    tcase_add_test(tc, s21_mul_tests_12);
    tcase_add_test(tc, s21_mul_tests_13);
    suite_add_tcase(s, tc);
    return s;
}
