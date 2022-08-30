#include <stdio.h>
#include "decimal_core.h"
#include "s21_decimal.h"

int main() {
    s21_decimal a = {{123435, 14567, 1, 0}};
    s21_decimal a1 = {{17891, 14567, 1, 0}};
    s21_decimal a2 = {{17890, 14567, 1, 0}};
    // set_exp(&a, 27);
    // print_decimal_bin(a);
    // printf("\n");
    // chang_sign(&a);
    // set_exp(&a, 5);
    // set_exp(&a, 7);
    // print_decimal_bin(a);
    // chang_sign(&a);
    print_decimal_bin(a1);
    printf("\n");
    print_decimal_bin(a2);
    printf("\n");
    printf("__%d__", s21_is_greater(a2, a1));


    return 0;
}
