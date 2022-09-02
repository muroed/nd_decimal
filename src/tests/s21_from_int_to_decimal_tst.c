#include "s21_decimal_tst.h"

START_TEST(s21_from_int_to_decimal_1) {
    s21_decimal val;

    s21_from_int_to_decimal(0, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-128, &val);
    ck_assert_int_eq(val.bits[0], 128);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

Suite *suite_s21_from_int_to_decimal_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_from_int_to_decimal");
    tc = tcase_create("case_from_int_to_decimal");
    tcase_add_test(tc, s21_from_int_to_decimal_1);
    suite_add_tcase(s, tc);
    return s;
}
