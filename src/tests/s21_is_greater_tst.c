#include "s21_decimal_tst.h"

START_TEST(s21_is_greater_test_1) {
    float a = Rand_R(-10e20, 10e20);
    float b = Rand_R(-10e20, 10e20);

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}
END_TEST

START_TEST(s21_is_greater_test_2) {
    float a = Rand_R(-10e1, 10e1);
    float b = Rand_R(-10e1, 10e1);

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}
END_TEST

START_TEST(s21_is_greater_test_3) {
    float a = -25.158531;
    float b = -39.425785;

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}

START_TEST(s21_is_greater_test_4) {
    float a = 0.0 / 0.0;
    float b = -39.425785;

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}

START_TEST(s21_is_greater_test_5) {
    float a = 0;
    float b = -39.425785;

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}

START_TEST(s21_is_greater_test_6) {
    float a = 0;
    float b = 39.425785;

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_greater(_a, _b), a > b);
}

START_TEST(s21_is_greater_test_7) {
    s21_decimal _a;
    _a.state = S21_NORMAL;
    _a.bits[0] = 0b10000000000000000000000000000000;
    _a.bits[1] = 0b11111111111111111111111111111111;
    _a.bits[2] = 0b11111111110000000000001111111111;
    _a.bits[3] = 0b00000000000111111000000000000000;
    s21_decimal _b;
    _b.state = S21_NORMAL;
    _b.bits[0] = 0b10000000000000000000000000000001;
    _b.bits[1] = 0b11111111111111111111111111111111;
    _b.bits[2] = 0b11111111110000000000001111111111;
    _b.bits[3] = 0b00000000000111000000000000000000;
    ck_assert_int_eq(s21_is_greater(_a, _b), 0);
}

Suite *suite_s21_is_greater_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_is_greater");
    tc = tcase_create("case_is_greater");

    tcase_add_loop_test(tc, s21_is_greater_test_1, 0, 1000);
    tcase_add_loop_test(tc, s21_is_greater_test_2, 0, 1000);
    tcase_add_test(tc, s21_is_greater_test_3);
    tcase_add_test(tc, s21_is_greater_test_4);
    tcase_add_test(tc, s21_is_greater_test_5);
    tcase_add_test(tc, s21_is_greater_test_6);
    tcase_add_test(tc, s21_is_greater_test_7);
    suite_add_tcase(s, tc);
    return s;
}
