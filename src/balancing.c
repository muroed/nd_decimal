#include "decimal_core.h"
#include "nd_decimal.h"

int shifting(nd_decimal *a, int n) {
  /// Multiply the number by 10 and increase the exponent by 1 thereby shifting
  /// the number to the left
  nd_decimal ten = {{10, 0, 0, 0}};
  nd_decimal tmp_result;
  nullify_all_decimal(&tmp_result);

  int exp = get_exp(*a);
  int status = exp == 28;

  while (!status && n--) {
    status = mul_lite(*a, ten, &tmp_result);
    if (!status) {
      *a = tmp_result;
      nullify_all_decimal(&tmp_result);
      status = (++exp == 28);
    }
  }

  set_exp(a, exp);
  return status;
}

int balancing(nd_decimal *a, nd_decimal *b) {
  int diff = get_exp(*a) - get_exp(*b);

  if (diff) {
    if (diff > 0)
      shifting(b, diff);
    else
      shifting(a, -diff);

    diff = get_exp(*a) - get_exp(*b);
    if (diff) {
      if (diff > 0)
        bank_round(a, diff);
      else
        bank_round(b, -diff);
    }
  }

  return OK;
}

int bank_rounding(int a) {
  /// returns 1 if you need to apply bank rounding or 0 if not
  return (a % 10 >= 5 || (a % 10 == 5 && (a / 10) % 2));
}

int bank_round(nd_decimal *number, int n) {
  nd_decimal one, ten, hund;
  nd_from_int_to_decimal(1, &one);
  nd_from_int_to_decimal(10, &ten);
  nd_from_int_to_decimal(100, &hund);

  while (n--) {
    nd_decimal mod_res;
    nullify_all_decimal(&mod_res);
    mod_sign(*number, hund, &mod_res);

    int exp = get_exp(*number) - 1;
    int_div(*number, ten, number);
    set_exp(number, exp);

    if (bank_rounding(mod_res.bits[0])) {
      int buf = number->bits[INFO_BIT];
      add_lite(*number, one, number);
      number->bits[INFO_BIT] = buf;
    }
  }

  return OK;
}
