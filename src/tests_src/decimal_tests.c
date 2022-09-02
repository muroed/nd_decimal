#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "tests_src/s21_decimal_test.h"
#include "s21_decimal.h"

int main() {
    int no_failed = 0;
    Suite *a, *b, *c, *d, *e, *f, *g, *h, *m, *l,  *n,  *j, *z, *t, *t1;
    SRunner* runner;
    a = floor_suite();
    b = tan_suite();
    c = abs_suite();
    d = acos_suite();
    e = fmod_suite();
    f = ceil_suite();
    g = atan_suite();
    h = fabs_suite();
    m = pow_suite();
    l = asin_suite();
    // h = asin_suite();
    // n = asin_suite();
    j = sin_suite();
    z = cos_suite();
    t = exp_suite();
    t1 = sqrt_suite();
    n = log_suite();

    runner = srunner_create(a);
    srunner_add_suite(runner, b);
    srunner_add_suite(runner, c);
    srunner_add_suite(runner, d);
    srunner_add_suite(runner, e);
    srunner_add_suite(runner, f);
    srunner_add_suite(runner, g);
    srunner_add_suite(runner, h);
    srunner_add_suite(runner, m);
    srunner_add_suite(runner, l);
    srunner_add_suite(runner, n);
    srunner_add_suite(runner, j);
    srunner_add_suite(runner, z);
    srunner_add_suite(runner, t);
    srunner_add_suite(runner, t1);
    srunner_set_log(runner, "test.log");
    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
