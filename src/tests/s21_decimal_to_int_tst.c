#include "s21_decimal_tst.h"

START_TEST(s21_from_decimal_to_int_test_1) {
    s21_decimal var;
    int value = 0;

    for (int i = -1073741824; i <= 1073741824; i += 10000) {
        s21_from_int_to_decimal(i, &var);
        s21_from_decimal_to_int(var, &value);
        ck_assert_int_eq(i, value);
    }
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
    s21_decimal var;
    int value = 0;
    s21_from_float_to_decimal(1.4525e10, &var);
    ck_assert_int_eq(s21_from_decimal_to_int(var, &value), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
    s21_decimal var;
    var.state = S21_NULL;
    int value = 0;
    s21_from_decimal_to_int(var, &value);
    ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
    s21_decimal var;
    var.state = S21_PLUS_INF;
    int value = 0;
    ck_assert_int_eq(s21_from_decimal_to_int(var, &value), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
    s21_decimal var;
    var.state = S21_NAN;
    int value = 0;
    ck_assert_int_eq(s21_from_decimal_to_int(var, &value), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_6) {
    s21_decimal var;
    var.state = S21_MINUS_INF;
    int value = 0;
    ck_assert_int_eq(s21_from_decimal_to_int(var, &value), 1);
}
END_TEST

Suite *suite_s21_from_decimal_to_int_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_from_decimal_to_int");
    tc = tcase_create("case_from_decimal_to_int");

    tcase_add_test(tc, s21_from_decimal_to_int_test_1);
    tcase_add_test(tc, s21_from_decimal_to_int_test_2);
    tcase_add_test(tc, s21_from_decimal_to_int_test_3);
    tcase_add_test(tc, s21_from_decimal_to_int_test_4);
    tcase_add_test(tc, s21_from_decimal_to_int_test_5);
    tcase_add_test(tc, s21_from_decimal_to_int_test_6);

    suite_add_tcase(s, tc);
    return s;
}
