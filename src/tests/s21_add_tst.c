#include "s21_decimal_tst.h"

START_TEST(s21_add_tests_1) {
    int a = (int)Rand_R(-10e5, 10e1);
    int b = (int)Rand_R(-10e5, 10e1);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a + b, c);
}
END_TEST

START_TEST(s21_add_tests_2) {
    int a = (int)Rand_R(0, 10e5);
    int b = (int)Rand_R(0, 10e5);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a + b, c);
}
END_TEST

START_TEST(s21_add_tests_3) {
    float a = Rand_R(-10e8, 10e8);
    float b = Rand_R(-10e8, 10e8);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e2);
}
END_TEST

START_TEST(s21_add_tests_4) {
    float a = Rand_R(-1000, 1000);
    float b = Rand_R(-1000, 1000);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e-1);
}
END_TEST

START_TEST(s21_add_tests_5) {
    int a = 99999;
    float b = Rand_R(10e-20, 10e-5);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e-1);
}
END_TEST

START_TEST(s21_add_tests_6) {
    int a = 9999999;
    float b = Rand_R(10e-20, 10e-5);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e-1);
}
END_TEST

START_TEST(s21_add_tests_7) {
    float a = -13.961408124790879675776971571;
    float b = Rand_R(10e-10, 10e20);
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 10e14);
}
END_TEST

START_TEST(s21_add_tests_8) {
    float a = -4.0145249913658339424669715711;
    float b = Rand_R(-1.0, 1.0);
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 1);
}
END_TEST

START_TEST(s21_add_tests_9) {
    float a = -0.05311686657495426669;
    float b = Rand_R(-1.0123456, 1.123456);
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 1);
}
END_TEST

START_TEST(s21_add_tests_10) {
    float a = -0.2295073270356096218094683170;
    float b = Rand_R(-0.0003456, 0.123456);
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 1);
}
END_TEST

START_TEST(s21_add_tests_11) {
    float a = -10.229507327035609621809468317;
    float b = Rand_R(-10.12345, 12.123456);
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 1);
}
END_TEST

START_TEST(s21_add_tests_12) {
    float a = -385964.28330307537203556736209;
    float b = -79350946.66422744608203556736;
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 10);
}
END_TEST

START_TEST(s21_add_tests_13) {
    float a = 992294974041.00000000;
    float b = 992295073270.09468317;
    float x;

    s21_decimal res;
    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &x);
    ck_assert_float_eq_tol(a + b, x, 1);
}
END_TEST

START_TEST(s21_add_tests_14) {
    s21_decimal res;
    s21_decimal _a;
    _a.bits[0] = 0b11111111111111111111111111111111;
    _a.bits[1] = 0b11111111111111111111111111111111;
    _a.bits[2] = 0b11111111111111111111111111111111;
    _a.bits[3] = 0b00000000000000000010000000000000;
    _a.state = S21_NORMAL;
    s21_decimal _b;
    // s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(1400, &_b);
    ck_assert_int_eq(s21_add(_a, _b, &res), 1);
}
END_TEST

START_TEST(s21_add_tests_15) {
    float a = 0;
    float b = 10e1;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e-1);
}
END_TEST

START_TEST(s21_add_tests_16) {
    float a = 10e1;
    float b = 0;
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_add(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol(a + b, c, 10e-1);
}
END_TEST

START_TEST(s21_add_tests_17) {
    s21_decimal _a;
    _a.state = S21_NAN;
    s21_decimal _b;
    _b.state = S21_NORMAL;
    s21_decimal res;

    ck_assert_int_eq(s21_add(_a, _b, &res), 3);
}
END_TEST

START_TEST(s21_add_tests_18) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_add(_a, _b, &res), 3);
}
END_TEST

START_TEST(s21_add_tests_19) {
    s21_decimal _a;
    _a.state = S21_PLUS_INF;
    s21_decimal _b;
    _b.state = S21_PLUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_add(_a, _b, &res), 1);
}
END_TEST

START_TEST(s21_add_tests_20) {
    s21_decimal _a;
    _a.state = S21_MINUS_INF;
    s21_decimal _b;
    _b.state = S21_MINUS_INF;
    s21_decimal res;

    ck_assert_int_eq(s21_add(_a, _b, &res), 2);
}
END_TEST

Suite *suite_s21_add_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_add");
    tc = tcase_create("case_add");

    tcase_add_loop_test(tc, s21_add_tests_1, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_2, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_3, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_4, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_5, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_6, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_7, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_8, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_9, 0, 1000);
    tcase_add_loop_test(tc, s21_add_tests_10, 0, 1000);
    tcase_add_test(tc, s21_add_tests_11);
    tcase_add_test(tc, s21_add_tests_12);
    tcase_add_test(tc, s21_add_tests_13);
    tcase_add_test(tc, s21_add_tests_14);
    tcase_add_test(tc, s21_add_tests_15);
    tcase_add_test(tc, s21_add_tests_16);
    tcase_add_test(tc, s21_add_tests_17);
    tcase_add_test(tc, s21_add_tests_18);
    tcase_add_test(tc, s21_add_tests_19);
    tcase_add_test(tc, s21_add_tests_20);

    suite_add_tcase(s, tc);
    return s;
}
