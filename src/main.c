#include <stdio.h>
#include "decimal_core.h"
#include "s21_decimal.h"

int main() {
    s21_decimal a = {{2147483647, 87654, 0, 0}};
    s21_decimal a1 = {{17891, 14567, 1, 0}};
    s21_decimal a2 = {{17890, 14567, 1, 0}};
    // set_exp(&a, 27);
    // print_decimal_bin(a);
    // printf("\n");
    chang_sign(&a);
    // set_exp(&a, 5);
    // set_exp(&a, 7);
    // print_decimal_bin(a);
    // chang_sign(&a);
    int b = 9;
    s21_decimal b_decimal = {{87654, 1568, 0, 0}};
    // s21_from_int_to_decimal(b, &a); 
    print_decimal_bin(a);
    print_decimal_bin(b_decimal);
    printf("%d\n", mul_lite(a, b_decimal, &a));
    print_decimal_bin(a);
    printf("%d\n", sub_lite(a, b_decimal, &a));
    print_decimal_bin(a);
    return 0;
}
