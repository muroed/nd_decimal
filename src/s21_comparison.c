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

int s21_is_not_equal(s21_decimal decim1, s21_decimal decim2) {
    int res_equal = 0;
    for (int i = 0; i < ALL_BIT; i++) {
        if (get_global_bit(decim1, i) != get_global_bit(decim2, i)) {
            res_equal = 1;
            break;
        }
    }
    return res_equal;
}

int s21_is_greater(s21_decimal decim1, s21_decimal decim2) {
    int res_greater = 0;
    int bit1, bit2;
    if (get_exp(decim1) > get_exp(decim2)) res_greater = 1;
    else
        for (int bit = ALL_BIT - BITS_IN_INT - 1; bit >= 0; bit--) {
        if ((bit1 = get_global_bit(decim1, bit)) != (bit2 = get_global_bit(decim2, bit))) {
            if (bit1 > bit2) res_greater = 1;
            break;
        }
    }
}

int s21_is_less(s21_decimal decim1, s21_decimal decim2) {
    int res_greater = 0;
    int bit1, bit2;
    if (get_exp(decim1) < get_exp(decim2)) res_greater = 1;
    else
        for (int bit = ALL_BIT - BITS_IN_INT - 1; bit >= 0; bit--) {
        if ((bit1 = get_global_bit(decim1, bit)) != (bit2 = get_global_bit(decim2, bit))) {
            if (bit1 < bit2) res_greater = 1;
            break;
        }
    }
}
