CC= gcc -std=c11
CFLAGS = -g #-Wall -Wextra -Werror
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -fprofile-arcs --coverage
LCHECK := -lcheck -lgmp
LIN_FLAGS := -lpthread -lcheck -pthread -lrt -lm -lsubunit
ifeq ($(shell uname), Linux)
CHECK_FLAGS += $(LIN_FLAGS)
endif

SOURCES:= core.c s21_another.c s21_arifmetic.c s21_comparison.c s21_converts.c s21_from_decimal_to_int.c

OBJECTS := $(addprefix obj/,$(SOURCES:.c=.o))
OBJECTS_GCOV := $(addprefix obj_gcov/,$(SOURCES:.c=.o))
OBJ_DIR     := obj
OBJ_GCOV_DIR:= obj_gcov
CHECKMK_FILE:= asd.check
HEADER:= s21_decimal.h decimal_core.h

all: clean gcov_report

create_dir:
	mkdir -p $(OBJ_DIR) $(OBJ_GCOV_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	mv *.o $(OBJ_DIR)/

$(OBJ_GCOV_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	@mv *.o *gcno $(OBJ_GCOV_DIR)/

s21_decimal.a: create_dir $(OBJECTS)
	ar rc libdecimal.a $(OBJ_DIR)/*.o

libgcov.a: create_dir $(OBJECTS_GCOV)
	ar rcs libgcov.a $(OBJ_GCOV_DIR)/*.o

decimal_tests.c:
	@checkmk clean_mode=1 $(CHECKMK_FILE) > decimal_tests.c

test: decimal_tests.c $(HEADER) libgcov.a
# echo "TYT"
	$(CC) $(CFLAGS) $^ -o test_test.out $(LCHECK) $(LDFLAGS) $(GCOV_FLAGS)
	./test_test.out
	@mv *.gcda *.gcno $(OBJ_GCOV_DIR)

gcov_report: test
	@rm -f $(OBJ_GCOV_DIR)/*tests*
	@lcov/bin/./lcov -c -d $(OBJ_GCOV_DIR)/. -o $(OBJ_GCOV_DIR)/coverage.info
	@lcov/bin/./genhtml $(OBJ_GCOV_DIR)/coverage.info --output-directory out


clean:
	@rm -rf *.a *.gcda *.gcno *.o *.out
	rm -rf $(OBJ_DIR) $(OBJ_GCOV_DIR) out


style:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.c
#	@clang-format -n *.h
#	@clang-format -n $(TEST_DIR)*.c
#	@clang-format -n $(TEST_DIR)*.h
	@rm .clang-format