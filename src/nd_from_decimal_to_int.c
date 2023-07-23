#include "nd_decimal.h"
#include "decimal_core.h"

int nd_from_decimal_to_int(nd_decimal src, int *dst) {
    int result = OK;
    int ten_pow = (src.bits[3] << 1) >> 17;

    if (!dst) {
        result = ERR;
    } else if (ten_pow > 28) {
        *dst = 0;
        result = ERR;
    } else {
        // nd_truncate(src, &src);
        if (check_sign(src) == 1)
            *dst = 0 - src.bits[0];
        else
            *dst = src.bits[0];
        if (*dst) *dst = set_bit(*dst, 31, check_sign(src));
    }
    return result;
}
