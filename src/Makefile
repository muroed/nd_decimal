CC= gcc -std=c11 #-Wall -Wextra -Werror 
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)
TEST_FLAGS  := --coverage -c -g

OBJ_DIR     := obj
TEST_SRC_DIR:= tests_src
TEST_OBJ_DIR:= tests_obj
GCOV_OBJ_DIR:= gcov_res

all: re
re: clean test

core.a: core.c $(LIBSOURCES)
	$(CC) -c $^
	ar rc libcore.a core.o $(LIBOBJECTS)
	ranlib libcore.a

test: core.a main.c
	$(CC) main.c -o a.out -L. -lcore
	./a.out

gcov_report: $(TEST_OBJ_DIR)/main.o $(GCOV_OBJ) $(MATH_SRC)
	ar rc s21_math.a $(GCOV_OBJ)
	ranlib 	s21_math.a
	$(CC) $(LFLAGS) --coverage $(TEST_OBJ) $(TEST_OBJ_DIR)/main.o s21_math.a -o test
	- ./test
	./../materials/lcov/bin/lcov -f -c --directory . -o ./coverage.info 
	./../materials/lcov/bin/genhtml coverage.info --output-directory=res
	#rm -f *.gcda *.gcov *.o *.gcno
	open res/index.html
clean:
	@rm -rf *.a
	@rm -rf *.o
	@rm -rf a.out


style:
	python3 ../materials/linters/cpplint.py --extensions=c,h *.c *.h
