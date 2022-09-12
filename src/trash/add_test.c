#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
  char str[1024];
  FILE* fp = NULL;
  fp = fopen(argv[1], "a");
  int bit1, bit2, bit3, bit4;
  srand(time(NULL));
  while (str[0] != '-') {
      printf("Name of test: ");
      scanf("%s", str);
      fprintf(fp,"%s %s\n", "#test", str);
      fprintf(fp, "s21_decimal a = {{%d, %d, %d, %d}};\n", rand(), rand(), rand(), 0);
      if (rand() % 4 == 2)
        fprintf(fp, "chang_sign(&a);\n");
      fprintf(fp, "s21_decimal b = {{%d, %d, %d, %d}};\n", rand(), rand(), rand(), 0);
      if (rand() % 4 == 3)
        fprintf(fp, "chang_sign(&b);\n");
      printf("Name of function: ");
      scanf("%s", str);
      fprintf(fp,"ck_assert_int_eq(s21_%s(a, b), s21_%s(b, b));\n", str, str);
      fprintf(fp, "\n");
      printf("ADD AGAIN?: ");
      scanf("%s", str);
  }
  fprintf(fp, "\n");
  fclose(fp);
  return 0;
}
