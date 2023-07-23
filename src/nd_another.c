#include "decimal_core.h"
#include "nd_decimal.h"

int nd_negate(nd_decimal decim, nd_decimal *result_decimal) {
  nullify_all_decimal(result_decimal);
  chang_sign(&decim);
  *result_decimal = decim;
  return 0;
}

int nd_truncate(nd_decimal decim, nd_decimal *result_decimal) {
  return truncate_to_exp(decim, 0, result_decimal);
}
int nd_round(nd_decimal value, nd_decimal *result) {
  nd_decimal one, zeroDotFive, mod_res;

  nd_from_int_to_decimal(1, &one);
  nd_from_int_to_decimal(5, &zeroDotFive);
  set_exp(&zeroDotFive, 1);

  nd_mod(value, one, &mod_res);
  set_sign(&mod_res, 0);
  set_sign(&one, check_sign(value));

  nd_truncate(value, result);
  if (nd_is_greater_or_equal(mod_res, zeroDotFive))
    nd_add(*result, one, result);
  return OK;
}

int nd_floor(nd_decimal value, nd_decimal *result) {
  nd_decimal one, mod_res;
  nd_from_int_to_decimal(1, &one);

  nd_mod(value, one, &mod_res);
  nd_truncate(value, result);
  if (check_sign(value) == 1 && !is_null_decimal(value) &&
      !is_null_decimal(mod_res)) {
    add_lite(*result, one, result);
    chang_sign(result);
  }
  return OK;
}

nd_decimal nd_decimal_get_inf(void) {
  nd_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

int nd_get_float_exp_from_string(char *str) {
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

nd_decimal nd_float_string_to_decimal(char *str) {
  int digits_counter = 7;
  nd_decimal result;
  nullify_all_decimal(&result);
  char *ptr = str;

  // Получаем в любом случае заново степень float из научной записи, а не
  // передаем полученную ранее в nd_from_float_to_decimal, т.к. она могла
  // измениться из-за округления
  int exp = nd_get_float_exp_from_string(str);

  while (*ptr) {
    if (*ptr == '.') {
      // Точку игнорируем, итоговую степень decimal мы будем отдельно считать
      ++ptr;
      continue;
    } else if (*ptr >= '0' && *ptr <= '9') {
      // Переводим цифры в строке в decimal, начиная с первой, используя
      // арифметику decimal
      nd_decimal tmp;
      nullify_all_decimal(&tmp);
      nd_mul(nd_decimal_get_from_char(*ptr),
              nd_int128_get_ten_pow(digits_counter), &tmp);
      nd_add(result, tmp, &result);
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
    nd_mul(result, nd_int128_get_ten_pow(exp), &result);
  } else if (exp < 0) {
    // Для отрицательной степени производим деление на 10^exp
    if (exp < -28) {
      // Отдельно обрабатываем очень маленькие степени, т.к. мы не сможем
      // поделить больше чем на 10^28
      nd_div(result, nd_int128_get_ten_pow(28), &result);
      exp += 28;
    }
    nd_div(result, nd_int128_get_ten_pow(-exp), &result);
  }

  return result;
}

// add in .h

nd_decimal nd_decimal_get_from_char(char c) {
  nd_decimal result;

  switch (c) {
    case '0':
      nullify_all_decimal(&result);
      break;
    case '1':
      result = nd_decimal_get_one();
      break;
    case '2':
      nd_from_int_to_decimal(2, &result);
      break;
    case '3':
      nd_from_int_to_decimal(3, &result);
      break;
    case '4':
      nd_from_int_to_decimal(4, &result);
      break;
    case '5':
      nd_from_int_to_decimal(5, &result);
      break;
    case '6':
      nd_from_int_to_decimal(6, &result);
      break;
    case '7':
      nd_from_int_to_decimal(7, &result);
      break;
    case '8':
      nd_from_int_to_decimal(8, &result);
      break;
    case '9':
      nd_from_int_to_decimal(9, &result);
      break;
  }

  return result;
}

nd_decimal nd_decimal_get_one(void) {
  nd_decimal result;
  nullify_all_decimal(&result);
  result.bits[0] = 1;

  return result;
}

//возвращает 10 в степени pow в виде числа int128
//Допустимый диапазон для pow - [0, 38]. Валидация данных не осуществляется и
//должна производится перед вызовом функции

nd_decimal nd_int128_get_ten_pow(int pow) { return all_ten_pows[pow]; }