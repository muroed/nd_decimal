#include "decimal_core.h"
#include "nd_decimal.h"

// https://russianblogs.com/article/568550142/

// add without degree and sign
int add_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal* result_decimal) {
  nullify_all_decimal(result_decimal);
  int error_mark = 0;
  for (int i = 0; i < 96; i++) {
    int bit_decim1 = get_global_bit(decim1, i);
    int bit_decim2 = get_global_bit(decim2, i);
    if (bit_decim1 ^ bit_decim2 ^ error_mark) {
      set_global_bit(result_decimal, i, 1);
    } else {
      set_global_bit(result_decimal, i, 0);
    }
    error_mark = (bit_decim1 && bit_decim2) || (bit_decim1 && error_mark) ||
                 (bit_decim2 && error_mark);
  }
  return error_mark;
}

int nd_add(nd_decimal decim1, nd_decimal decim2,
            nd_decimal* result_decimal) {
  int error_mark = 0;
  int decim1_sign = check_sign(decim1);
  int decim2_sign = check_sign(decim2);
  balancing(&decim1, &decim2);
  int scale = get_exp(decim1);
  if (!(decim1_sign ^ decim2_sign)) {
    error_mark = add_lite(decim1, decim2, result_decimal);
    set_sign(result_decimal, decim1_sign);
  } else if (is_less_or_equal_lite(decim1, decim2)) {
    sub_lite(decim2, decim1, result_decimal);
    set_sign(result_decimal, decim2_sign);
  } else {
    sub_lite(decim1, decim2, result_decimal);
    set_sign(result_decimal, decim1_sign);
  }
  if (error_mark && scale) {
    bank_round(&decim1, 1);
    bank_round(&decim2, 1);
    error_mark = nd_add(decim1, decim2, result_decimal);
  } else {
    set_exp(result_decimal, scale);
  }
  return error_mark;
}

int sub_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal* result_decimal) {
  int error_mark = 0;
  nullify_all_decimal(result_decimal);
  for (int i = 0; i < 96; i++) {
    int bit_decim1 = get_global_bit(decim1, i);
    int bit_decim2 = get_global_bit(decim2, i);
    if (bit_decim1 ^ bit_decim2) {
      set_global_bit(result_decimal, i, 1);
    }
    if (!bit_decim1 && bit_decim2) {
      int k = i + 1;
      while ((bit_decim1 = !get_global_bit(decim1, k)) && k < 96) {
        set_global_bit(&decim1, k, 1);
        k++;
      }
      if (k == 96) {
        error_mark = 1;
        nullify_all_decimal(result_decimal);
      }
      set_global_bit(&decim1, k, 0);
    }
  }
  return error_mark;
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
int sub_sign(nd_decimal decim1, nd_decimal decim2,
             nd_decimal* result_decimal) {
  int error_mark = 0;
  int sign_decim1 = check_sign(decim1);
  int sign_decim2 = check_sign(decim2);
  int priority = nd_is_greater_or_equal(decim1, decim2);

  if (sign_decim1 == 1 && sign_decim2 == 1) {
    chang_sign(&decim1);
    chang_sign(&decim2);
    if (priority == 0) {
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

int nd_sub(nd_decimal decim1, nd_decimal decim2,
            nd_decimal* result_decimal) {
  int error_mark = 0;
  nullify_all_decimal(result_decimal);
  balancing(&decim1, &decim2);
  int exp = get_exp(decim1);
  error_mark = sub_sign(decim1, decim2, result_decimal);
  set_exp(result_decimal, exp);
  return error_mark;
}

int mul_lite(nd_decimal decim1, nd_decimal decim2,
             nd_decimal* result_decimal) {
  // nullify_all_decimal(result_decimal);

  int status = 0;
  nd_decimal tmp = *result_decimal;
  int sign = check_sign(decim1) ^ check_sign(decim2);
  set_sign(&tmp, check_sign(decim1) ^ check_sign(decim2));
  set_sign(&decim2, 0);
  set_sign(&decim1, 0);

  while (!is_null_decimal_bin(decim2) && !status) {
    if (get_global_bit(decim2, 0)) {
      status = add_lite(tmp, decim1, &tmp);
    }
    decim2 = bit_swift_right(decim2, 1);
    if (!status) status = bit_swift_left(decim1, 1, &decim1);
  }

  if (!status)
    *result_decimal = tmp;
  else if (check_sign(decim1) ^ check_sign(decim2))
    ++status;
  set_sign(result_decimal, sign);
  return status;
}

int nd_mul(nd_decimal decim1, nd_decimal decim2,
            nd_decimal* result_decimal) {
  nullify_all_decimal(result_decimal);
  int error_mark = 0;  // mul_lite(decim1, decim2, result_decimal);
  if (is_null_decimal(decim1) == 1 || is_null_decimal(decim2) == 1) {
    nullify_all_decimal(result_decimal);
  } else if (get_exp(decim1) == 0 && get_exp(decim2) == 0) {
    error_mark = mul_lite(decim1, decim2, result_decimal);
  } else {
    int result_exp = get_exp(decim1) + get_exp(decim2);
    error_mark = mul_lite(decim1, decim2, result_decimal);
    if (result_exp <= MAX_EXP)
      set_exp(result_decimal, result_exp);
    else
      nullify_all_decimal(result_decimal);
  }
  return error_mark;
}

int div_lite(nd_decimal decim1, nd_decimal decim2, nd_decimal* result) {
  int status = 0;
  nd_decimal one;
  nd_from_int_to_decimal(1, &one);
  nd_decimal temp;
  nullify_all_decimal(&temp);
  *result = one;
  if (is_equal_lite(decim1, decim2)) {
    *result = one;
  } else if (is_less_lite(decim1, decim2)) {
    nullify_all_decimal(result);
  } else {
    nd_decimal divcopy = decim2;
    nd_decimal tmp;
    while (is_greater_lite(decim1, decim2) == 1 && status == 0) {
      tmp = decim2;
      status = bit_swift_left(decim2, 1, &decim2);
      bit_swift_left(*result, 1, result);
    }
    if (status == 1) {
      decim2 = tmp;
      *result = bit_swift_right(*result, 1);
      status--;
    }
    if (is_less_lite(decim1, decim2) == 1) {
      decim2 = bit_swift_right(decim2, 1);
      *result = bit_swift_right(*result, 1);
    }
    sub_lite(decim1, decim2, &temp);
    status = div_lite(temp, divcopy, &one);
    status = add_lite(*result, one, result);
  }
  return status;
}

int int_div(nd_decimal decim1, nd_decimal decim2, nd_decimal* result) {
  int error_mark = 0;

  if (is_null_decimal(decim2)) {
    error_mark = 3;
  } else {
    nd_from_int_to_decimal(1, result);

    int sign = check_sign(decim1) ^ check_sign(decim2);
    set_sign(&decim1, 0);
    set_sign(&decim2, 0);

    int res_exp = get_exp(decim1) - get_exp(decim2);
    set_exp(&decim1, 0);
    set_exp(&decim2, 0);

    error_mark = div_lite(decim1, decim2, result);
    if (res_exp < 0) {
      error_mark = shifting(result, -res_exp);
      error_mark += -res_exp << 2;

      res_exp = 0;
    }
    set_exp(result, res_exp);
    set_sign(result, sign);
  }

  return error_mark;
}

nd_decimal mod_lite(nd_decimal decim1, nd_decimal decim2) {
  int status = 0;
  nd_decimal divcopy = decim2;
  nd_decimal res, tmp;
  nd_decimal zero = {{0, 0, 0, 0}};
  if (is_equal_lite(decim1, decim2))
    return zero;
  else if (is_less_lite(decim1, decim2))
    return decim1;

  while (is_less_or_equal_lite(decim2, decim1) && !check_sign(decim2) &&
         !is_null_decimal(decim2)) {
    tmp = decim2;
    status = bit_swift_left(decim2, 1, &decim2);
  }
  if (status == 1) {
    decim2 = tmp;
    status--;
  }
  if (is_less_lite(decim1, decim2)) {
    decim2 = bit_swift_right(decim2, 1);
  }
  sub_lite(decim1, decim2, &zero);
  res = mod_lite(zero, divcopy);
  return res;
}

int mod_sign(nd_decimal decim1, nd_decimal decim2, nd_decimal* result) {
  if (is_null_decimal(decim2)) return 3;
  nullify_all_decimal(result);
  int sign = check_sign(decim1);
  set_sign(&decim1, 0);
  set_sign(&decim2, 0);
  *result = mod_lite(decim1, decim2);
  set_sign(result, sign);
  return 0;
}

int nd_mod(nd_decimal decim1, nd_decimal decim2, nd_decimal* result) {
  balancing(&decim1, &decim2);
  int exp = get_exp(decim1);
  int res = mod_sign(decim1, decim2, result);
  set_exp(result, exp);
  return res;
}

int additional_int_prec(nd_decimal decim1, nd_decimal decim2,
                        nd_decimal* result, int status) {
  set_exp(&decim2, get_exp(decim2) - status);
  int decim1_sign = check_sign(decim1);
  int decim2_sign = check_sign(decim2);
  nd_decimal mod_res, div_res;
  nullify_all_decimal(&div_res);
  nullify_all_decimal(&mod_res);

  nd_mod(decim1, decim2, &mod_res);
  shifting(&mod_res, -1);

  set_exp(&decim2, get_exp(decim2) + status);

  while (is_less_lite(mod_res, decim2)) bank_round(&decim2, 1);
  int_div(mod_res, decim2, &div_res);
  status = nd_add(div_res, *result, result);
  set_sign(result, decim1_sign ^ decim2_sign);
  return status;
}

int nd_div(nd_decimal decim1, nd_decimal decim2, nd_decimal* result) {
  int status = int_div(decim1, decim2, result);
  if (!(status & 3)) {
    status >>= 2;
    nd_decimal mod_res;
    nullify_all_decimal(&mod_res);
    if (status) status = additional_int_prec(decim1, decim2, result, status);
    nd_truncate(*result, result);
    nd_mod(decim1, decim2, &mod_res);
    if (!is_null_decimal_bin(mod_res)) {
      nd_decimal div_res, tmp;
      nd_decimal ten = {{10, 0, 0, 0}};
      nullify_all_decimal(&div_res);
      nullify_all_decimal(&tmp);
      int exp = get_exp(mod_res);
      for (int sub_stat = 0; !sub_stat; nullify_all_decimal(&tmp)) {
        sub_stat = mul_lite(mod_res, ten, &tmp);
        if (!sub_stat) {
          mod_res = tmp;
          if (++exp < 29) set_exp(&mod_res, exp);
        }
      }
      if (!get_exp(mod_res)) set_exp(&mod_res, 28);
      while (is_less_lite(mod_res, decim2)) bank_round(&decim2, 1);
      int_div(mod_res, decim2, &div_res);
      if (exp > 28) set_exp(&div_res, exp - get_exp(decim2));
      status = nd_add(div_res, *result, result);
    }
  } else {
    status &= 3;
  }
  if (status == 1 && check_sign(decim1) ^ check_sign(decim2)) ++status;
  return status;
}
