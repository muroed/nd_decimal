CC= gcc -std=c11 #-Wall -Wextra -Werror 
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)


all: $(LIBOBJECTS)
	ar rc s21_decimal.a $^
	ranlib s21_decimal.a

core.a: core.c
	$(CC) -c core.c
	ar rc libcore.a core.o
	ranlib libcore.a

main: core.a main.c
	$(CC) main.c -o a.out -L. -lcore
	./a.out

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf a.out

re: clean test

style:
	python3 ../materials/linters/cpplint.py --extensions=c,h *.c *.h
