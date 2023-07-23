#include "decimal_core.h"
#include "s21_decimal.h"

//  включает бит под номером bit в bits
int bit_on(int bits, int bit) { return bits | _2(bit % BITS_IN_INT); }
//  выключает бит под номером bit в bits
int bit_off(int bits, int bit) { return bits & ~(_2(bit % BITS_IN_INT)); }
//  меняет значение бита и возвращает новый bit

// включен ли бит под номером bit в bits
int bit_is(int bits, int bit) { return (bits & (_2(bit % BITS_IN_INT))) != 0; }
// получить бит
int get_bit(int bits, int bit) { return bit_is(bits, bit % BITS_IN_INT); }
// получить int из decimal по номеру бита
int get_bits(s21_decimal decim, int gbit) {
  return decim.bits[(gbit % (ALL_BIT + BITS_IN_INT)) / BITS_IN_INT];
}

int get_global_bit(s21_decimal decim, int gbit) {
  return get_bit(get_bits(decim, gbit), gbit);
}
int set_global_bit(s21_decimal* decim, int gbit, int new_bit) {
  return decim->bits[(gbit % (ALL_BIT + BITS_IN_INT)) / BITS_IN_INT] =
             set_bit(get_bits(*decim, gbit), gbit, new_bit);
}
//  возвращает знак 1 '-'; 0 '+'
int check_sign(s21_decimal decim) {
  return get_bit(decim.bits[INFO_BIT], SIGN_BIT);
}
//  возвращает новый измененный знак decimal
int chang_sign(s21_decimal* decim) {
  if (check_sign(*decim) == 1)
    decim->bits[INFO_BIT] = bit_off(decim->bits[INFO_BIT], SIGN_BIT);
  else
    decim->bits[INFO_BIT] = bit_on(decim->bits[INFO_BIT], SIGN_BIT);
  return check_sign(*decim);
}

int set_sign(s21_decimal* decim, int sign) {
  decim->bits[INFO_BIT] = set_bit(decim->bits[INFO_BIT], SIGN_BIT, sign);
  return check_sign(*decim);
}
//  Зануление всего decimal
s21_decimal nullify_all_decimal(s21_decimal* decim) {
  for (int i = 0; i < BITS; i++) decim->bits[i] = 0;
  return *decim;
}
//  Меняет в bits бит под номером bit на new_bit
int set_bit(int bits, int bit, int new_bit) {
  if (new_bit) {
    bits = bit_on(bits, bit);
  } else {
    bits = bit_off(bits, bit);
  }
  return bits;
}
/*
отображение decimal по битам
bits[3]:
зеленая цифра: знак decimal
Желтые цифры: Обязательно нули иначе красные цифры
Голубые цифры: степень десятки для запятой

bits[2] - bits[0]:
Красные единицы
Белые нули
*/

// void print_decimal_bin(s21_decimal decim) {
//   for (int i = BITS - 1; i >= 0; i--) {
//     int n = BITS_IN_INT - 1;
//     printf("|%s[%d]%s|", COLOR_BLUE, i, COLOR_END);
//     // printf("|%sbits[%d]%s|", COLOR_BLUE, i, COLOR_END);
//     if (i == BITS - 1) {
//       printf("%s%d%s", COLOR_GREEN, get_bit(decim.bits[i], SIGN_BIT),
//              COLOR_END);
//       n--;
//       while (n >= 0) {
//         int b = 0;
//         if ((n < START_EXP_BIT && n >= ZERO_BIT) ||
//             (n > END_EXP_BIT && n < SIGN_BIT)) {
//           if ((b = get_bit(decim.bits[i], n)) == 0)
//             printf("%s%d%s", COLOR_ORANGE, b, COLOR_END);
//           else
//             printf("%s%d%s", COLOR_RED, b, COLOR_END);
//         } else {
//           if (get_bit(decim.bits[i], n) == 1)
//             printf("%s%d%s", COLOR_CYAN, get_bit(decim.bits[i], n),
//             COLOR_END);
//           else
//             printf("%d", get_bit(decim.bits[i], n));
//         }
//         n--;
//       }
//     } else {
//       while (n >= 0) {
//         if (get_bit(decim.bits[i], n) == 1) {
//           printf("%s%c%s", COLOR_RED, '1', COLOR_END);
//         } else {
//           printf("0");
//         }
//         n--;
//       }
//     }
//   }
//   printf("\n");
// }

// void print_decimal_int(s21_decimal decim) {
//   printf("{{%d, %d, %d, %d}};\n", decim.bits[0], decim.bits[1],
//   decim.bits[2],
//          decim.bits[3]);
// }

/*
Лучше начать с дополнительных функций, get bit(получение бита 0 или 1), set
bit(замена 0 бита на 1), change bit, nullify bit, print_decimal_bin( в двоичном
виде распечатка), get scale( получение истового числа скейла), check sign,
change sing(проверка и замена знака), nullify all decimal(зануление всего
децимала), Nullify scale. Ну что то ещё возможно. А так можно начать с
конвертеров, там поймёшь как все устроено, и не нужны какие то ещё функции
необходимые по заданию. А дальше уже сложения.
*/

// получение степени из decimal
int get_exp(s21_decimal decim) {
  int exp = 0;
  for (int i = START_EXP_BIT; i <= END_EXP_BIT; i++) {
    if (bit_is(decim.bits[INFO_BIT], i)) exp += (1 << (i - START_EXP_BIT));
  }
  return exp;
}

int set_exp(s21_decimal* decim, int new_exp) {
  int sign = check_sign(*decim);
  decim->bits[INFO_BIT] = new_exp << START_EXP_BIT;
  if (check_sign(*decim) != sign) chang_sign(decim);
  return decim->bits[INFO_BIT];
}

int is_null_decimal(s21_decimal decim) {
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  return is_equal_lite(decim, null_decimal);
}

int is_null_decimal_bin(s21_decimal decim) {
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  int res_equal = 1;
  for (int i = 0; i < (ALL_BIT); i++) {
    if (get_global_bit(decim, i) != get_global_bit(null_decimal, i)) {
      res_equal = 0;
      break;
    }
  }
  return res_equal;
}

int swift_bits_right(int bits, int number) {
  if (bits < 0) {
    bits = bit_off(bits, SIGN_BIT);
    bits = bits >> number;
    bits = bit_on(bits, SIGN_BIT - number);
  } else {
    bits = bits >> number;
  }
  return bits;
}

int bit_swift_left(s21_decimal decim, int number, s21_decimal* result) {
  int error_mark = 0;
  nullify_all_decimal(result);
  int buffer_bits = 0;
  result->bits[INFO_BIT] = decim.bits[INFO_BIT];

  for (int i = 0; i < BITS - 1; i++) {
    if (i != 0)
      buffer_bits = swift_bits_right(decim.bits[i - 1],
                                     (BITS_IN_INT - (number % BITS_IN_INT)));
    if (i == 2)
      if (swift_bits_right(decim.bits[i],
                           (BITS_IN_INT - (number % BITS_IN_INT))) != 0)
        error_mark = 1;  // 1 - число слишком велико или равно бесконечности
    result->bits[i] = decim.bits[i] << number;
    result->bits[i] = result->bits[i] | buffer_bits;
  }

  return error_mark;
}

s21_decimal bit_swift_right(s21_decimal decim, int number) {
  s21_decimal result;
  nullify_all_decimal(&result);
  int buffer_bits = 0;
  result.bits[INFO_BIT] = decim.bits[INFO_BIT];

  for (int i = BITS - 2; i >= 0; i--) {
    if (i != BITS - 2)
      buffer_bits = decim.bits[i + 1] << (BITS_IN_INT - (number % BITS_IN_INT));
    result.bits[i] = swift_bits_right(decim.bits[i], number);
    result.bits[i] = result.bits[i] | buffer_bits;
  }

  return result;
}
// ^
s21_decimal bit_exclusive_or(s21_decimal decim1, s21_decimal decim2) {
  s21_decimal result;
  nullify_all_decimal(&result);
  for (int i = 0; i < BITS - 1; i++) {
    result.bits[i] = decim1.bits[i] ^ decim2.bits[i];
  }
  return result;
}
// &
s21_decimal bit_and(s21_decimal decim1, s21_decimal decim2) {
  s21_decimal result;
  nullify_all_decimal(&result);
  for (int i = 0; i < BITS - 1; i++) {
    result.bits[i] = decim1.bits[i] & decim2.bits[i];
  }
  return result;
}

int truncate_to_exp(s21_decimal decim, int new_exp,
                    s21_decimal* result_decimal) {
  int exp = get_exp(decim);
  if (exp > 0) set_exp(&decim, 0);
  int sign = check_sign(decim);
  if (sign == 1) chang_sign(&decim);
  int error_mark = 0;
  s21_decimal ten = {{10, 0, 0, 0}};
  for (int i = exp; i > new_exp && error_mark == 0; i--) {
    error_mark = div_lite(decim, ten, &decim);
  }
  *result_decimal = decim;
  if (sign == 1) chang_sign(result_decimal);
  set_exp(&decim, exp);
  return error_mark;
}

// int s21_truncate(s21_decimal value, s21_decimal *result) {
//     int error_mark = 0;
//     int sign = check_sign(value);
//     int scale = get_exp(value);
//     s21_decimal ten = {0};
//     *result = value;
//     s21_from_int_to_decimal(10, &ten);
//     while (scale != 0) {
//         error_mark = get_sign(div_simple(*result, ten, result));
//         scale--;
//     }
//     set_sign(result, sign);
//     return error_mark;
// }