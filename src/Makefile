CC= gcc -std=c11 #-Wall -Wextra -Werror 
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)
TEST_FLAGS  := --coverage -c -g
CHECK_FLAGS := -lcheck
LIN_FLAGS := -lpthread -pthread -lrt -lm -lsubunit
ifeq ($(shell uname), Linux)
CHECK_FLAGS += $(LIN_FLAGS)
endif
OBJ_DIR     := obj
TEST_SRC_DIR:= tests_src
TEST_OBJ_DIR:= tests_obj
GCOV_OBJ_DIR:= gcov_res
CHECKMK_FILE:= asd.check

all: tests
re: clean main
tests: core.a test clean

core.a: core.c $(LIBSOURCES)
	$(CC) -c $^
	ar rc libcore.a core.o $(LIBOBJECTS)
	ranlib libcore.a

main: core.a main.c
	$(CC) main.c -o a.out -L. -lcore
	./a.out

add_test: clean add_test.c
	@$(CC) add_test.c -o add_test.out
	@./add_test.out $(CHECKMK_FILE)
	@make tests

test: $(LIBOBJECTS)
#clean_mode=1
	@checkmk clean_mode=1 $(CHECKMK_FILE) > decimal_tests.c
	@$(CC) decimal_tests.c $^ -L. -lcore $(CHECK_FLAGS) -o test_decimal.out
	@./test_decimal.out


clean:
	@rm -rf *.a
	@rm -rf *.o
	@rm -rf *.out


style:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.c
#	@clang-format -n *.h
#	@clang-format -n $(TEST_DIR)*.c
#	@clang-format -n $(TEST_DIR)*.h
	@rm .clang-format