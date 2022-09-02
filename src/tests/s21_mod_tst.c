#include "s21_decimal_tst.h"

START_TEST(s21_mod_tests_1) {
    int a = (int)Rand_R(-10e3, 10e3);
    int b = (int)Rand_R(1, 10e300);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mod(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a % b, c);
}
END_TEST

START_TEST(s21_mod_tests_2) {
    int a = (int)Rand_R(-11, 10e3);
    int b = (int)Rand_R(-10e3, -1);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mod(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq(a % b, (int)(c));
}
END_TEST

START_TEST(s21_mod_tests_3) {
    int a = Rand_R(-10e8, 10e8);
    int b = Rand_R(-10e8, 10e8);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mod(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);
    ck_assert_int_eq((int)(a % b), c);
}
END_TEST

START_TEST(s21_mod_tests_4) {
    int a = Rand_R(-1000, 1000);
    int b = Rand_R(-20, -1);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mod(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);

    ck_assert_int_eq((a % b), c);
}
END_TEST

START_TEST(s21_mod_tests_5) {
    int a = 9999999;
    int b = Rand_R(-10e20, 10e40);
    int c = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_int_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    s21_mod(_a, _b, &res);
    s21_from_decimal_to_int(res, &c);

    ck_assert_int_eq((int)(a % b), c);
}
END_TEST

START_TEST(s21_mod_tests_6) {
    float a = 99999999999.9999999999;
    int b = 0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_int_to_decimal(b, &_b);
    ck_assert_int_eq(3, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_7) {
    float a = 89228162514264337593543950335.0;
    float b = -79228162514264337593543950335.0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(2, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_8) {
    float a = 89228162514264337593543950335.0;
    float b = -89228162514264337593543950335.0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(3, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_9) {
    float a = 89228162514264337593543950335.0;
    float b = -2;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(2, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_10) {
    float a = 89228162514264337593543950335.0;
    float b = 2;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(1, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_11) {
    float a = -89228162514264337593543950335.0;
    float b = 2;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);

    ck_assert_int_eq(2, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_12) {
    float a = -89228162514264337593543950335.0;
    float b = 2;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(2, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_13) {
    float a = 234234;
    float b = -89228162514264337593543950335.0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(0, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_14) {
    float a = -234234;
    float b = -89228162514264337593543950335.0;

    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;

    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(0, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_15) {
    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;
    s21_decl_to_null(&_a);
    s21_decl_to_null(&_b);
    s21_decl_to_null(&res);
    _a.state = S21_NAN;

    ck_assert_int_eq(3, s21_mod(_a, _b, &res));
}
END_TEST

START_TEST(s21_mod_tests_16) {
    s21_decimal _a;
    s21_decimal _b;
    s21_decimal res;
    _b.state = S21_NORMAL;
    _a.state = S21_NULL;

    ck_assert_int_eq(0, s21_mod(_a, _b, &res));
}
END_TEST

Suite *suite_s21_mod_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_mod");
    tc = tcase_create("case_mod");

    tcase_add_loop_test(tc, s21_mod_tests_1, 0, 1000);
    tcase_add_loop_test(tc, s21_mod_tests_2, 0, 1000);
    tcase_add_loop_test(tc, s21_mod_tests_3, 0, 1000);
    tcase_add_loop_test(tc, s21_mod_tests_4, 0, 1000);
    tcase_add_loop_test(tc, s21_mod_tests_5, 0, 1000);
    tcase_add_test(tc, s21_mod_tests_6);
    tcase_add_test(tc, s21_mod_tests_7);
    tcase_add_test(tc, s21_mod_tests_8);
    tcase_add_test(tc, s21_mod_tests_9);
    tcase_add_test(tc, s21_mod_tests_10);
    tcase_add_test(tc, s21_mod_tests_11);
    tcase_add_test(tc, s21_mod_tests_12);
    tcase_add_test(tc, s21_mod_tests_13);
    tcase_add_test(tc, s21_mod_tests_14);
    tcase_add_test(tc, s21_mod_tests_15);
    tcase_add_test(tc, s21_mod_tests_16);
    suite_add_tcase(s, tc);
    return s;
}
