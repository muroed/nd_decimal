#include "s21_decimal_tst.h"

START_TEST(s21_floor_test_1) {
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(5.5, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(s21_floor_test_2) {
    float n = Rand_R(-10e10, 10e10);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10);
}
END_TEST

START_TEST(s21_floor_test_3) {
    float n = Rand_R(-10e10, 10e10);
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10);
}
END_TEST

START_TEST(s21_floor_test_4) {
    float n = -6.03859187520912032422302842;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_5) {
    float n = 3908291258215925.4090869715711;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_6) {
    float n = -0.05311686657495426669;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_7) {
    float n = 2295073270.356096218094683170;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_8) {
    float n = 9.99999999999999999999;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_9) {
    float n = 987637685379687;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_10) {
    float n = 744367.68425;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

START_TEST(s21_floor_test_11) {
    float n = 744367.68425;
    s21_decimal var;
    float value = 0;
    s21_from_float_to_decimal(n, &var);
    s21_floor(var, &var);
    s21_from_decimal_to_float(var, &value);
    ck_assert_float_eq_tol(floor(n), value, 10e-1);
}
END_TEST

Suite *suite_s21_floor_ste(void) {
    Suite *s;
    TCase *tc;
    s = suite_create("s21_floor");
    tc = tcase_create("case_floor");

    tcase_add_test(tc, s21_floor_test_1);
    tcase_add_loop_test(tc, s21_floor_test_2, 0, 1000);
    tcase_add_loop_test(tc, s21_floor_test_3, 0, 1000);
    tcase_add_test(tc, s21_floor_test_3);
    tcase_add_test(tc, s21_floor_test_4);
    tcase_add_test(tc, s21_floor_test_5);
    tcase_add_test(tc, s21_floor_test_6);
    tcase_add_test(tc, s21_floor_test_7);
    tcase_add_test(tc, s21_floor_test_8);
    tcase_add_test(tc, s21_floor_test_9);
    tcase_add_test(tc, s21_floor_test_10);
    tcase_add_test(tc, s21_floor_test_11);
    suite_add_tcase(s, tc);
    return s;
}
