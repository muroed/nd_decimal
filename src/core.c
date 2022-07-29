#include "decimal_core.h"
#include "s21_decimal.h"
//  включает бит под номером bit в bits
int bit_on(int bits, int bit) {
    return bits | _2(bit);
}
//  выключает бит под номером bit в bits
int bit_off(int bits, int bit) {
    return bits & ~(_2(bit));
}
//  меняет значение бита и возвращает новый bit
int bit_swap(int bits, int bit) {
// return bit_is(bits, bit) ? bit_off(bits, bit) : bit_on(bit, bit);
return bits ^ _2(bit);
}
// включен ли бит под номером bit в bits
int bit_is(int bits, int bit) {
    return (bits & (_2(bit))) != 0;
}
// получить бит
int get_bit(int bits, int bit) {
    return bit_is(bits, bit);
}
//  возвращает знак 1 '-'; 0 '+'
int check_sign(s21_decimal a) {
    return get_bit(a.bits[INFO_BIT], SIGN_BIT);
}
//  возвращает новый измененный знак
int chang_sign(s21_decimal* a) {
    if (check_sign(*a) == 1)
        a->bits[INFO_BIT] = bit_off(a->bits[INFO_BIT], SIGN_BIT);
    else
        a->bits[INFO_BIT] = bit_on(a->bits[INFO_BIT], SIGN_BIT);
return get_bit(a->bits[INFO_BIT], SIGN_BIT);
}
//  Зануление всего decimal
s21_decimal nullify_all_decimal(s21_decimal *a) {
    for (int i = 0; i < BITS; i++) a->bits[i] = 0;
    return *a;
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
void print_decimal_bin(s21_decimal a) {
    for (int i = BITS - 1; i >=0; i--) {
        int n = BITS_IN_INT - 1;
        printf("|%sbits[%d]%s|", COLOR_BLUE, i, COLOR_END);
        if (i == BITS - 1) {
            printf("%s%d%s", COLOR_GREEN, get_bit(a.bits[i], SIGN_BIT), COLOR_END);
            n--;
            while (n >= 0) {
                int b = 0;
                if ((n < START_EXP_BIT && n >= ZERO_BIT) || (n > END_EXP_BIT && n < SIGN_BIT)) {
                    if ((b = get_bit(a.bits[i], n)) == 0)
                        printf("%s%d%s", COLOR_ORANGE, b, COLOR_END);
                    else
                        printf("%s%d%s", COLOR_RED, b, COLOR_END);
                } else {
                    if (get_bit(a.bits[i], n) == 1)
                        printf("%s%d%s", COLOR_CYAN, get_bit(a.bits[i], n), COLOR_END);
                    else
                        printf("%d", get_bit(a.bits[i], n));
                }
                n--;
            }
        } else {
            while (n >= 0) {
                if (get_bit(a.bits[i], n) == 1) {
                    printf("%s%c%s", COLOR_RED, '1', COLOR_END);
                } else {
                    printf("0");
                }
                n--;
            }
        }
    }
}

/*
Лучше начать с дополнительных функций, get bit(получение бита 0 или 1), set bit(замена 0 бита на 1),
change bit, nullify bit, print_decimal_bin( в двоичном виде распечатка),
get scale( получение истового числа скейла), check sign,
change sing(проверка и замена знака), nullify all decimal(зануление всего децимала), Nullify scale.
Ну что то ещё возможно. А так можно начать с конвертеров,
там поймёшь как все устроено, и не нужны какие то ещё функции необходимые по заданию.
А дальше уже сложения.
*/
