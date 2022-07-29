#include <stdio.h>
#include "decimal_core.h"

int main() {
    s21_decimal a = {{123435, 14567, 1, 0}};
    printf("\n");
    print_decimal_bin(a);
    printf("\n");
    // printf("%d\n%d\n", bit_on(a.bits[1], 31), get_bit(a.bits[1], 31));
    chang_sign(&a);
    print_decimal_bin(a);
    printf("\n");
    return 0;
}
