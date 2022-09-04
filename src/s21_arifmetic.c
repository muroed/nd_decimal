
#include "decimal_core.h"
#include "s21_decimal.h"


// https://russianblogs.com/article/568550142/


// int add(int num1, int num2) {
//     int res = 0, carry = 0;
//     res = num1^num2;
//     carry = (num1&num2) << 1;
//     while (carry) {
//         int tmp = res;
//         res = res^carry;
//         carry = (tmp&carry) << 1;
//     }
//     return res;
// }

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

// int negtive(int n) {
//     return add(~n, 1);
// }

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
}

// Удалить знаковый бит
// int getSign(int n) {
//     return n >> 31;
// } 

// // Находим абсолютное значение n
// int positive(int n) {
//     return (getSign(n) & 1) ? negtive(n) : n;
// }

// int multiply(int a, int b) {
//     // Если двухзначные биты знака несовместимы, результат отрицательный
//     bool isNegtive = false;
//     if(getSign(a) ^ getSign(b))
//         isNegtive = true;
//     a = positive(a);
//     b = positive(b);
//     int res = 0;
//     while (b | 0) {
//         // Когда соответствующий бит b равен 1, нужно только добавить
//         if(b & 1)
//             res = add(res, a);
//         a = a << 1; // сдвиг влево
//         b = b >> 1; // б сдвиг вправо
//     }
//     return isNegtive == true ? negtive(res) : res;
// }


// int res = 0;
//     while (b | 0) {
//         // Когда соответствующий бит b равен 1, нужно только добавить
//         if(b & 1)
//             res = add(res, a);
//         a = a << 1; // сдвиг влево
//         b = b >> 1; // б сдвиг вправо
//     }
//     return isNegtive == true ? negtive(res) : res;
// }
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

// int divide(int a, int b) {
//     // Делитель не может быть 0
//     if (b == 0)
//         throw std::runtime_error("Divided can't be zero...");

//     bool isNegtive = false;
//     if (getSign(a) ^ getSign(b))
//         isNegtive = true;

//     a = positive(a);
//     b = positive(b);

//     int res = 0;
//     while (a >= b) {
//         res = add(res, 1);
//         a = subtraction(a, b);
//     }
//     return beNegtive == true ? negtive(res) : res;
// }

int div_lite(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal, s21_decimal* remainder) {
  int error_mark = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  nullify_all_decimal(result_decimal);

  while (s21_is_greater_or_equal(decim1, decim2) == 1) {
    error_mark = add_lite(*result_decimal, one, result_decimal);
    sub_lite(decim1, decim2, &decim1);
    *remainder = decim1;
  }
  return error_mark;
}

int div_exp(s21_decimal decim1, s21_decimal decim2, s21_decimal* result_decimal) {
  int error_mark = 0;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal remainder, new_result;
  nullify_all_decimal(&remainder);


  while (s21_is_equal(decim1, zero) == 0 && get_exp(*result_decimal) <= 28) {
    div_lite(decim1, decim2, &new_result, &remainder);
    int exp_buffer = get_exp(*result_decimal);
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
