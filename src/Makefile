CC= gcc -std=c11 #-Wall -Wextra -Werror 
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)
HEADER:= decimal_core.h s21_decimal.h

all: $(LIBOBJECTS)
	ar rc s21_decimal.a $^
	ranlib s21_decimal.a

core.a: $(LIBSOURCES)
	$(CC) -c $(LIBSOURCES) $(HEADER)
	ar rc libcore.a $(LIBOBJECTS)
	ranlib libcore.a

main: clean core.a main.c
	$(CC) main.c -o a.out -L. -lcore
	./a.out

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf a.out

re: clean test

style:
	python3 ../materials/linters/cpplint.py --extensions=c,h *.c *.h
