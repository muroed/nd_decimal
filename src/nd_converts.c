#include "nd_decimal.h"

int nd_from_int_to_decimal(int src_int, nd_decimal *dst_decimal) {
  int error_mark = 0;
  if (!dst_decimal)
    return 1;
  else {
    nullify_all_decimal(dst_decimal);
    if (src_int < 0) {
      src_int = -src_int;
      chang_sign(dst_decimal);
    }
    dst_decimal->bits[0] = src_int;
  }
  return error_mark;
}

int nd_from_decimal_to_int(nd_decimal src, int *dst) {
  int result = 0;
  int ten_pow = get_exp(src);
  if (!dst) {
    result = 1;
  } else if (ten_pow > 28) {
    *dst = 0;
    result = 1;
  } else {
    nd_truncate(src, &src);

    for (int i = 1; i < 3; i++) {
      for (int j = 0; j < 16; j++) {
        if (get_bit(src.bits[i], j) == 1) {
          result = 1;
          break;
        }
      }
      if (result == 1) {
        break;
      }
    }

    if (result == 0) {
      if (check_sign(src) == 1)
        *dst = 0 - src.bits[0];
      else
        *dst = src.bits[0];
      if (*dst) *dst = set_bit(*dst, 31, check_sign(src));
    }
  }
  return result;
}

// 0 - Ок
// 1 - Ошибка

int nd_from_float_to_decimal(float src, nd_decimal *dst) {
  int error_mark = 0;
  float mark = src;
  if (!dst) {
    error_mark = 1;
  } else if (src == 0.0) {
    error_mark = 0;
    *dst = nullify_all_decimal(dst);
    if (signbit(src) != 0) {  //смотрим знак, + или -
      set_sign(dst, 0);       //добавляем знак для -0.0
    }
  } else if (isinf(mark) || isnan(mark)) {
    error_mark = 1;
    *dst = nd_decimal_get_inf();
    if (signbit(src) != 0) {
      set_sign(dst, 0);
    }
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    error_mark = 1;
    *dst = nd_decimal_get_inf();
    if (signbit(src) != 0) {
      set_sign(dst, 0);
    }
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    error_mark = 1;
    *dst = nullify_all_decimal(dst);
  } else {
    *dst = nullify_all_decimal(dst);
    nd_decimal results;
    char flt[64];
    // Приводим float в научную запись - одна цифра до запятой и 6 цифр после
    // запятой В итоге мы получаем 7 значащих цифр, которые нам и нужно
    // перевести по заданию из float в decimal
    sprintf(flt, "%.7E", fabsf(src));
    int exp = nd_get_float_exp_from_string(flt);

    if (exp <= -23) {
      // Если степень слишком маленькая, то не все значащие цифры поместятся в
      // decimal Поэтому корректируем точность и заново приводим float в научную
      // запись уже с новой точностью
      int float_precision = exp + 28;
      sprintf(flt, "%.*E", float_precision, fabsf(src));
    }

    // Переводим строку с научной нотацией в decimal
    results = nd_float_string_to_decimal(flt);

    if (signbit(src) != 0) {
      set_sign(&results, 0);
    }
    if (src < 0) {
      set_sign(&results, 1);
    }

    *dst = results;
  }
  return error_mark;
}

int nd_from_decimal_to_float(nd_decimal src, float *dst) {
  int return_code = OK;

  if (!dst) {
    return_code = 1;
  } else {
    double reserve = 0;
    for (int i = 0; i < 96; i++)
      if (src.bits[i / 32] & (1u << (i % 32))) reserve += pow(2, i);
    int sign = (src.bits[3] < 0) ? 1 : 0;
    int ten_pow = (src.bits[3] << 1) >> 17;
    if (ten_pow >= 0) {
      if (ten_pow > 28) {
        *dst = 0;
        return_code = 1;
      } else {
        for (int i = ten_pow; i > 0; i--) {
          reserve /= 10;
        }
        *dst = (float)reserve;
        if (sign) *dst *= -1;
      }
    }
  }
  return return_code;
}
