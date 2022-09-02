#include "s21_decimal_tst.h"

START_TEST(s21_div_tests_1) {
    int a = (int)Rand_R(-10e3, 10e3);
    int b = (int)Rand_R(-10e3, 10e3);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_div(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a / b, c);
}
END_TEST

START_TEST(s21_div_tests_2) {
    int a = (int)Rand_R(1, 10e3);
    int b = (int)Rand_R(1, 10e3);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_div(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    if (a / b != (int)(c)) {
        printf("%d * %d\n", a, b);
    }
    ck_assert_int_eq(a / b, (int)(c));
}
END_TEST

START_TEST(s21_div_tests_3) {
    float a = Rand_R(-10e8, 10e8);
    float b = Rand_R(-10e8, 10e8);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_div(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);
    ck_assert_float_eq_tol((int)(a / b), c, 2);
}
END_TEST

START_TEST(s21_div_tests_4) {
    float a = Rand_R(-1000, 1000);
    float b = Rand_R(-20, 20);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_div(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);

    // if (fabs(a+b-c) > 10e-1) {
    //     printf("%f + %f = %f ||||| %f\n", a, b, (float)(a+b), c);
    //     print_dec(_a);
    //     print_dec(_b);
    //     print_dec(res);
    //     print_float(c);
    //     print_float(a+b);
    // }
    ck_assert_float_eq_tol((int)(a / b), c, 2);
}
END_TEST

START_TEST(s21_div_tests_5) {
    int a = 9999999;
    float b = Rand_R(10e-20, 10e-5);
    float c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    s21_div(_a, _b, &res);
    s21_from_decimal_to_float(res, &c);

    ck_assert_float_eq_tol(a / b, c, 10e10);
}
END_TEST

START_TEST(s21_div_tests_6) {
    int num1 = 100;
    int num2 = 50;
    int res_origin = 2;
    s21_decimal a;
    s21_decimal b;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_div_tests_7) {
    int num1 = -32768;
    int num2 = 2;
    int res_origin = -16384;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_div_tests_8) {
    int num1 = 2;
    int num2 = 2;
    int res_origin = 1;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_div_tests_9) {
    int num1 = 0;
    int num2 = 5;
    int res_origin = num1 / num2;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_div_tests_10) {
    s21_decimal dec1 = {{100, 0, 0, 0}, S21_NORMAL};
    s21_decimal dec2 = {{99999, 0, 0, 0}, S21_NORMAL};

    float res_s21 = 0;
    float res = 100.0 / 99999.0;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_tests_11) {
    s21_decimal dec1;
    s21_decimal dec2;
    int tmp1 = 100;
    float tmp2 = 999.99;
    float res_s21 = 0.0;
    float res = 0.100001;
    s21_from_int_to_decimal(tmp1, &dec1);
    s21_from_float_to_decimal(tmp2, &dec2);
    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_tests_12) {
    s21_decimal dec1 = {{1000, 0, 0, 0}, S21_NORMAL};
    s21_set_scale(&dec1, 1);
    s21_decimal dec2 = {{5, 0, 0, 0}, S21_NORMAL};
    s21_set_scale(&dec2, 1);

    float res_s21 = 0.0;
    float res = 200;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq(res_s21, res);
}
END_TEST

START_TEST(s21_div_tests_13) {
    s21_decimal dec1;
    s21_decimal dec2;
    int tmp1 = -100;
    int tmp2 = -99999;
    float res_s21 = 0;
    float res = 0.00100001;
    s21_from_int_to_decimal(tmp1, &dec1);
    s21_from_int_to_decimal(tmp2, &dec2);
    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_tests_14) {
    s21_decimal dec1 = {{1005, 0, 0, 0}, S21_NORMAL};
    s21_set_scale(&dec1, 1);
    s21_set_bit(&dec1, 127, 1);
    s21_decimal dec2 = {{999995, 0, 0, 0}, S21_NORMAL};
    s21_set_scale(&dec2, 1);
    s21_set_bit(&dec2, 127, 1);

    float res_s21 = 0;
    float res = 0.001005005;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_tests_15) {
    s21_decimal dec1 = {{10.0e3, 0, 0, 0}, S21_NORMAL};
    s21_decimal dec2 = {{2.00e2, 0, 0, 0}, S21_NORMAL};

    int res_s21 = 0;
    int res = 50;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_tests_16) {
    s21_decimal dec1 = {{1110, 0, 0, 0}, S21_NORMAL};
    s21_decimal dec2 = {{0, 0, 0, 0}, S21_NULL};

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_tests_17) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_PLUS_INF;
    s21_set_sign(&dec2, 1);

    s21_decimal res1;
    nullify_all_decimal(&res1);
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_tests_18) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_PLUS_INF;
    s21_set_sign(&dec2, 0);

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_div_tests_19) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_MINUS_INF;
    s21_set_sign(&dec2, 0);

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_tests_20) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_MINUS_INF;
    s21_set_sign(&dec2, 1);

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_div_tests_21) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec2.state = S21_MINUS_INF;
    s21_set_sign(&dec2, 1);

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_tests_22) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_PLUS_INF;
    dec2.state = S21_MINUS_INF;
    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_tests_23) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_MINUS_INF;
    s21_set_sign(&dec2, 0);
    dec2.state = S21_NORMAL;
    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_tests_24) {
    s21_decimal dec1;
    s21_decimal dec2;
    nullify_all_decimal(&dec1);
    nullify_all_decimal(&dec2);
    dec1.state = S21_NAN;
    s21_set_sign(&dec2, 0);
    dec2.state = S21_NAN;
    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 3);
}
END_TEST

Suite *suite_s21_div_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_div");
    tc = tcase_create("case_div");

    tcase_add_loop_test(tc, s21_div_tests_1, 0, 1000);
    tcase_add_loop_test(tc, s21_div_tests_2, 0, 1000);
    tcase_add_loop_test(tc, s21_div_tests_3, 0, 1000);
    tcase_add_loop_test(tc, s21_div_tests_4, 0, 1000);
    tcase_add_test(tc, s21_div_tests_5);
    tcase_add_test(tc, s21_div_tests_6);
    tcase_add_test(tc, s21_div_tests_7);
    tcase_add_test(tc, s21_div_tests_8);
    tcase_add_test(tc, s21_div_tests_9);
    tcase_add_test(tc, s21_div_tests_10);
    tcase_add_test(tc, s21_div_tests_11);
    tcase_add_test(tc, s21_div_tests_12);
    tcase_add_test(tc, s21_div_tests_13);
    tcase_add_test(tc, s21_div_tests_14);
    tcase_add_test(tc, s21_div_tests_15);
    tcase_add_test(tc, s21_div_tests_16);
    tcase_add_test(tc, s21_div_tests_17);
    tcase_add_test(tc, s21_div_tests_18);
    tcase_add_test(tc, s21_div_tests_19);
    tcase_add_test(tc, s21_div_tests_20);
    tcase_add_test(tc, s21_div_tests_21);
    tcase_add_test(tc, s21_div_tests_22);
    tcase_add_test(tc, s21_div_tests_23);
    tcase_add_test(tc, s21_div_tests_24);
    suite_add_tcase(s, tc);
    return s;
}
