#include "decimal_core.h"
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src_int, s21_decimal *dst_decimal) {
  nullify_all_decimal(dst_decimal);
  int error_mark = 0;
  if (!dst_decimal)
    error_mark = 1;
  else if (src_int < 0) {
    src_int = -src_int;
    chang_sign(dst_decimal);
  }
  dst_decimal->bits[0] = src_int;
  return error_mark;
}

// int s21_from_decimal_to_int(s21_decimal src_decimal, int *dst_int) {
//   int error_mark = 0;
//   if (!dst_int)
//     error_mark = 0;
//   else {
//     int exp = get_exp(src_decimal);
//     s21_decimal 
//   }
// }


int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error_mark = 0;
    if (!dst) {
        error_mark = 1;
    } else {
        int scale = get_exp(src), sign;
        sign = (check_sign(src)) ? -1 : 1;
        s21_decimal ten;
        s21_from_int_to_decimal(10, &ten);
        while (scale > 0) {
            div_lite(src, ten, &src);
            scale--;
        }
        set_global_bit(&src, 31, 0);
        *dst = src.bits[0];
        *dst *= sign;
    }
    return error_mark;
}

// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//     int result = 0;
//     int ten_pow = get_exp(src);
//     if (!dst) {
//         result = 1;
//     } else if (ten_pow > 28) {
//         *dst = 0;
//         result = 1;
//     } else {
//         s21_truncate(src, &src);

//         for (int i = 1; i < 3; i++) {
//             for (int j = 0; j < 16; j++) {
//                 if (get_bit(src.bits[i], j) == 1) {
//                     result = 1;
//                     break;
//                 }
//             }
//             if (result == 1) {
//                 break;
//             }
//         }

//         if (result == 0) {
//             if (check_sign(src) == 1)
//                 *dst = 0 - src.bits[0];
//             else
//                 *dst = src.bits[0];
//             if (*dst) *dst = set_bit(*dst, 31, check_sign(src));

//         }
//     }
//     return result;
// }