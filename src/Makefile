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

clean:
	@rm -rf *.a
	@rm -rf *.o
	@rm -rf a.out


style:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.c
#	@clang-format -n *.h
#	@clang-format -n $(TEST_DIR)*.c
#	@clang-format -n $(TEST_DIR)*.h
	@rm .clang-format