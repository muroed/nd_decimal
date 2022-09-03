#include <stdio.h>
#include "decimal_core.h"
#include "s21_decimal.h"

int main() {
    s21_decimal a = {{123435, 14567, 1, 0}};
    s21_decimal a1 = {{17891, 14567, 0, 65536}};
    s21_decimal a2 = {{17890, 14567, 1, 0}};
    int dj= 0;
    // set_exp(&a, 27);
    // print_decimal_bin(a);
    // printf("\n");
    // chang_sign(&a);
    // set_exp(&a, 5);
    // set_exp(&a, 7);
    // print_decimal_bin(a);
    // chang_sign(&a);
    printf("%d\n", get_exp(a1));
    print_decimal_bin(a1);
    printf("\n");
    print_decimal_bin(a2);
    printf("\n");
    s21_from_decimal_to_int(a1, &dj);
    s21_truncate(a1, &a1);
    printf("%d\n", dj);
    printf("%d\n", get_exp(a1));
    print_decimal_bin(a1);
    printf("\n");
    print_decimal_bin(a2);
    printf("\n");


    printf("__%s__\n", s21_is_greater_or_equal(a2, a1) == 1 ? "True" : "False");
    printf("__%s__", s21_is_less_or_equal(a1, a2) == 1 ? "True" : "False");

    return 0;
}
