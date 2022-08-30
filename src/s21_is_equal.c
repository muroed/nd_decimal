#include "decimal_core.h"
#include "s21_decimal.h"

int s21_is_equal(s21_decimal decim1, s21_decimal decim2) {
    int res_equal = 1;
    for (int i = 0; i < ALL_BIT; i++) {
        if (get_global_bit(decim1, i) != get_global_bit(decim2, i)) {
            res_equal = 0;
            break;
        }
    }
    return res_equal;
}
