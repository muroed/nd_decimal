#include "decimal_core.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal decim, s21_decimal *result_decimal) {
  nullify_all_decimal(result_decimal);
  chang_sign(&decim);
  *result_decimal = decim;
  return 0;
}

int s21_truncate(s21_decimal decim, s21_decimal *result_decimal) {
  return truncate_to_exp(decim, 0, result_decimal);
}
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal one, zeroDotFive, mod_res;

  s21_from_int_to_decimal(1, &one);
  s21_from_int_to_decimal(5, &zeroDotFive);
  set_exp(&zeroDotFive, 1);

  s21_mod(value, one, &mod_res);
  set_sign(&mod_res, 0);
  set_sign(&one, check_sign(value));

  s21_truncate(value, result);
  if (s21_is_greater_or_equal(mod_res, zeroDotFive))
    s21_add(*result, one, result);
  return OK;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one, mod_res;
  s21_from_int_to_decimal(1, &one);

  s21_mod(value, one, &mod_res);
  s21_truncate(value, result);
  if (check_sign(value) == 1 && !is_null_decimal(value) &&
      !is_null_decimal(mod_res)) {
    add_lite(*result, one, result);
    chang_sign(result);
  }
  return OK;
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ++ptr;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ++ptr;
  }

  return result;
}

s21_decimal s21_float_string_to_decimal(char *str) {
  int digits_counter = 7;
  s21_decimal result;
  nullify_all_decimal(&result);
  char *ptr = str;

  // Получаем в любом случае заново степень float из научной записи, а не
  // передаем полученную ранее в s21_from_float_to_decimal, т.к. она могла
  // измениться из-за округления
  int exp = s21_get_float_exp_from_string(str);

  while (*ptr) {
    if (*ptr == '.') {
      // Точку игнорируем, итоговую степень decimal мы будем отдельно считать
      ++ptr;
      continue;
    } else if (*ptr >= '0' && *ptr <= '9') {
      // Переводим цифры в строке в decimal, начиная с первой, используя
      // арифметику decimal
      s21_decimal tmp;
      nullify_all_decimal(&tmp);
      s21_mul(s21_decimal_get_from_char(*ptr),
              s21_int128_get_ten_pow(digits_counter), &tmp);
      s21_add(result, tmp, &result);
      --digits_counter;
      ++ptr;
    } else {
      break;
    }
  }
  // Учитываем, что в научной записи степень уже сдвинутая, чтобы далее
  // корректно выставить степень decimal
  exp = exp - 7;

  if (exp > 0) {
    // Для положительной степени производим умножение на 10^exp
    s21_mul(result, s21_int128_get_ten_pow(exp), &result);
  } else if (exp < 0) {
    // Для отрицательной степени производим деление на 10^exp
    if (exp < -28) {
      // Отдельно обрабатываем очень маленькие степени, т.к. мы не сможем
      // поделить больше чем на 10^28
      s21_div(result, s21_int128_get_ten_pow(28), &result);
      exp += 28;
    }
    s21_div(result, s21_int128_get_ten_pow(-exp), &result);
  }

  return result;
}

// add in .h

s21_decimal s21_decimal_get_from_char(char c) {
  s21_decimal result;

  switch (c) {
    case '0':
      nullify_all_decimal(&result);
      break;
    case '1':
      result = s21_decimal_get_one();
      break;
    case '2':
      s21_from_int_to_decimal(2, &result);
      break;
    case '3':
      s21_from_int_to_decimal(3, &result);
      break;
    case '4':
      s21_from_int_to_decimal(4, &result);
      break;
    case '5':
      s21_from_int_to_decimal(5, &result);
      break;
    case '6':
      s21_from_int_to_decimal(6, &result);
      break;
    case '7':
      s21_from_int_to_decimal(7, &result);
      break;
    case '8':
      s21_from_int_to_decimal(8, &result);
      break;
    case '9':
      s21_from_int_to_decimal(9, &result);
      break;
  }

  return result;
}

s21_decimal s21_decimal_get_one(void) {
  s21_decimal result;
  nullify_all_decimal(&result);
  result.bits[0] = 1;

  return result;
}

//возвращает 10 в степени pow в виде числа int128
//Допустимый диапазон для pow - [0, 38]. Валидация данных не осуществляется и
//должна производится перед вызовом функции

s21_decimal s21_int128_get_ten_pow(int pow) { return all_ten_pows[pow]; }