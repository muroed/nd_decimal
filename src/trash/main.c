#include <stdio.h>
#include "decimal_core.h"
#include "s21_decimal.h"
#include <math.h>
int main() {
s21_decimal a = {{210613260, 0, 0, 0}};
s21_decimal b = {{10, 0, 0, 0}};
s21_decimal res;
nullify_all_decimal(&res);
// add_lite(a, b, &res);
print_decimal_bin(a);
print_decimal_bin(b);
// print_decimal_bin(b);
// printf("__%d__\n", div_lite(a, b, &res, &a));
div_lite(a, b, &res);
print_decimal_bin(res);
// printf("__%d__\n", s21_is_equal(b, a1));/
    // print_decimal_bin(a);
    // print_decimal_bin(a1);
    // s21_negative(a, &a);
    // print_decimal_bin(b);
    // printf("%d", -a.bits[0] % (0 - b_decimal.bits[0]));
    // printf("%d\n", sub_sign(a, b_decimal, &a));
    // print_decimal_bin(a);
    return 0;
}
// 1010000010101111011001110
// 10000010101111011001110