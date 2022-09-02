#include "s21_decimal_tst.h"

START_TEST(s21_is_less_or_equal_test_1) {
    float a = Rand_R(-10e20, 10e20);
    float b = Rand_R(-10e20, 10e20);

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_2) {
    float a = Rand_R(-10e1, 10e1);
    float b = Rand_R(-10e1, 10e1);

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_3) {
    float a = -25.158531;
    float b = -39.425785;

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(b, &_b);
    ck_assert_int_eq(s21_is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_4) {
    float a = Rand_R(-10e20, 10e20);

    s21_decimal _a;
    s21_decimal _b;
    s21_from_float_to_decimal(a, &_a);
    s21_from_float_to_decimal(a, &_b);
    ck_assert_int_eq(s21_is_less(_a, _b), 0);
}
END_TEST

Suite *suite_s21_is_less_or_equal_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_is_less_or_equal");
    tc = tcase_create("case_is_less_or_equal");

    tcase_add_loop_test(tc, s21_is_less_or_equal_test_1, 0, 1000);
    tcase_add_loop_test(tc, s21_is_less_or_equal_test_2, 0, 1000);
    tcase_add_test(tc, s21_is_less_or_equal_test_3);
    tcase_add_loop_test(tc, s21_is_less_or_equal_test_4, 0, 1000);
    suite_add_tcase(s, tc);
    return s;
}
