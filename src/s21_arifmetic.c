
#include "decimal_core.h"
#include "s21_decimal.h"


// https://russianblogs.com/article/568550142/


// add without degree and sign
int add_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  s21_decimal carry;
  nullify_all_decimal(result_decimal);
  nullify_all_decimal(&carry);

  *result_decimal = bit_exclusive_or(decim1, decim2);
  error_mark = bit_swift_left(bit_and(decim1, decim2), 1, &carry);
  while (is_null_decimal(carry) == 0 && error_mark == 0) {
    s21_decimal tmp = *result_decimal;
    *result_decimal = bit_exclusive_or(*result_decimal, carry);
    error_mark = bit_swift_left(bit_and(tmp, carry), 1, &carry);
  }
  return error_mark;
}

// add without degree
int add_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);

  if (sign_decim1 == 1 && sign_decim2 == 1) {
    chang_sign(result_decimal);
    error_mark = add_lite(decim1, decim2, result_decimal);
  } else if (sign_decim1 == 1) {
    chang_sign(&decim1);
    error_mark = sub_lite(decim2, decim1, result_decimal);
  } else if (sign_decim2 == 1) {
    chang_sign(&decim2);
    error_mark = sub_lite(decim1, decim2, result_decimal);
  } else {
    error_mark = add_lite(decim1, decim2, result_decimal);
  }
  return error_mark;
}

int  s21_add(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  int error_mark = 0;
  int exp_decim1 = get_exp(decim1);
  int exp_decim2 = get_exp(decim2);

  if (exp_decim1 < exp_decim2) swap_int(&exp_decim1, &exp_decim2);

  error_mark = truncate_to_exp(decim1, exp_decim1 - exp_decim2, &decim1);
  if (error_mark == 0) error_mark = truncate_to_exp(decim2, exp_decim1 - exp_decim2, &decim2);

  if (error_mark == 0) error_mark = add_sign(decim1, decim2, result_decimal);

  return error_mark;
}

s21_decimal negative_decimal(s21_decimal decim) {
  s21_decimal one = {{1, 0, 0, 0}};
  add_lite(bit_negative(decim), one, &decim);  
  return decim;
}
// ПРОВЕРИТЬ НОМЕРА ОШИБОК!!!
int sub_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  return !add_lite(decim1, negative_decimal(decim2), result_decimal);
}
/*
 1 - 2
'+' '+'
   >    '+'
   <    '-'
'+' '-'
   >    '+'
   <    '+'
'-' '-'
   >    '-'
   <    '+'
'-' '+'
   >    '-'
   <    '-'
*/

//   ПРОВЕРИТЬ ЛОГИКУ !!!!
int sub_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);
  int priority = s21_is_greater(decim1, decim2);

  if (sign_decim1 == 1 && sign_decim2 == 1) {
    if (priority == 1) {
      error_mark = sub_lite(decim1, decim2, result_decimal);
      chang_sign(result_decimal);
    } else {
      error_mark = sub_lite(decim2, decim1, result_decimal);
    }
  } else if (sign_decim1 == 1) {
    error_mark = add_lite(decim1, decim2, result_decimal);
    chang_sign(result_decimal);
  } else if (sign_decim2 == 1) {
    error_mark = add_lite(decim1, decim2, result_decimal);
  } else {
    if (priority == 1) {
      error_mark = sub_lite(decim1, decim2, result_decimal);
    } else {
      error_mark = sub_lite(decim2, decim1, result_decimal);
      chang_sign(result_decimal);
    }
  }
  return error_mark;
}

int mul_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  int error_mark = 0;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  nullify_all_decimal(result_decimal);
  
  while (s21_is_not_equal(bit_or(decim2, zero), zero) == 1) {
    if (s21_is_equal(bit_and(decim2, one), one) == 1)
      add_lite(*result_decimal, decim1, result_decimal);
    error_mark = bit_swift_left(decim1, 1, &decim1);
    decim2 = bit_swift_right(decim2, 1);
  }
  return error_mark;
}

int mul_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);
  nullify_all_decimal(result_decimal);

  if (sign_decim1 == sign_decim2)
    error_mark = mul_lite(decim1, decim2, result_decimal);
  else {
    error_mark = mul_lite(decim1, decim2, result_decimal);
    chang_sign(result_decimal);
  }
  return error_mark;
}

int div_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal* result) {
  int status;
  s21_decimal one;
  s21_from_int_to_decimal(1, &one);
  s21_decimal temp;
  nullify_all_decimal(&temp);
  *result = one;
  if (s21_is_equal(decim1, decim2)) {
    *result = one;
  } else if (s21_is_less(decim1, decim2)) {
    nullify_all_decimal(result);
  } else {
    s21_decimal divcopy = decim2;
  
    while(s21_is_greater(decim1, decim2) == 1) {
      bit_swift_left(decim2, 1, &decim2);
      bit_swift_left(*result, 1, result);
    }
    if (s21_is_less(decim1, decim2) == 1) {
      decim2 = bit_swift_right(decim2, 1);
      *result = bit_swift_right(*result, 1);
    }
    sub_lite(decim1, decim2, &temp);
    status = div_lite(temp, divcopy, &one);
    status = add_lite(*result, one, result);
  }
  return status;
}

// int div_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal, s21_decimal* remainder) {
//   int error_mark = 0;
//   s21_decimal one = {{1, 0, 0, 0}};
//   nullify_all_decimal(result_decimal);

//   while (s21_is_greater_or_equal(decim1, decim2) == 1 && error_mark == 0) {
//     error_mark = add_lite(*result_decimal, one, result_decimal);
//     sub_lite(decim1, decim2, &decim1);
//   }
//     *remainder = decim1;
//   return error_mark;
// }

int div_exp(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  int error_mark = 0;
  int exp_buffer = 0;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal remainder, new_result;
  nullify_all_decimal(&remainder);


  while (s21_is_not_equal(decim1, zero) && (exp_buffer=get_exp(*result_decimal)) < MAX_EXP && !error_mark) {
    // div_lite(decim1, decim2, &new_result, &remainder);
    add_lite(*result_decimal, new_result, result_decimal);
    set_exp(result_decimal, exp_buffer);
    if (s21_is_not_equal(remainder, zero) == 1) {
      mul_lite(remainder, ten, &remainder);
      mul_lite(*result_decimal, ten, result_decimal);
      set_exp(result_decimal, exp_buffer + 1);
    }
    decim1 = remainder;
  }
  return error_mark;
}

int div_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  nullify_all_decimal(result_decimal);
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);

  if (sign_decim1 == sign_decim2)
    error_mark = div_exp(decim1, decim2, result_decimal);
  else {
    error_mark = div_exp(decim1, decim2, result_decimal);
    chang_sign(result_decimal);
  }

  return error_mark;
}

int mod_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal *result_decimal) {
  int error_mark = 0;
  nullify_all_decimal(result_decimal);
  s21_decimal null;
  // error_mark = div_lite(decim1, decim2, &null, result_decimal);
  return error_mark;
}

int mod_sign(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  int error_mark = 0;

  if (check_sign(decim1) == 1) {
    error_mark = mod_lite(decim1, decim2, result_decimal);
    chang_sign(result_decimal);
  } else {
    error_mark = mod_lite(decim1, decim2, result_decimal);
  }
  return error_mark;
}
