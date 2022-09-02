CC := gcc
ASAN := #-fsanitize=address
STDFLAGS := -c -Wall -Wextra -Werror -std=c11
CFLAGS := $(STDFLAGS) $(ASAN)
TST_CFLAGS := -g $(STDFLAGS) $(shell pkg-config --cflags check)
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
TST_LIBS := -lcheck $(shell pkg-config --libs check)
ifeq ($(shell uname), Linux)
TST_LIBS := -lcheck_pic $(shell pkg-config --libs check) -lpthread -lrt -lm -lsubunit
endif

LIB ?= s21_decimal.a
TEST_LIB ?= s21_decimal_tests.a
TEST_EXE ?= run_test

DIR := ./
TEST_DIR := $(DIR)tests/

OBJ_DIR := $(DIR)objs/
TEST_OBJ_DIR := $(TEST_DIR)objs/

SRC := $(wildcard $(DIR)s21_*.c)
INC := $(wildcard $(DIR)*.h)

TEST_SRC := $(wildcard $(TEST_DIR)*.c)
TEST_INC := $(wildcard $(TEST_DIR)*.h)

OBJ := $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
GCOV_OBJ := $(addprefix $(TEST_OBJ_DIR), $(notdir $(SRC:.c=.o)))
TEST_OBJ := $(addprefix $(TEST_OBJ_DIR), $(notdir $(TEST_SRC:.c=.o)))

GCOV_TARGET ?= $(DIR)coverage
GCOV_INFO ?= coverage.info

AR := ar rc
RAN := ranlib
MK := mkdir -p
RM := rm -rf

all: gcov_report test $(LIB)

$(LIB): create_obj_dir $(OBJ)
	$(AR) $(LIB) $(OBJ)
	$(RAN) $(LIB)

create_obj_dir:
	@$(MK) $(OBJ_DIR)

$(TEST_LIB): $(GCOV_OBJ) $(INC)
	$(AR) $(TEST_LIB) $(GCOV_OBJ)
	$(RAN) $(TEST_LIB)

test: create_obj_test_dir $(TEST_LIB) $(TEST_OBJ_DIR)main.o $(TEST_OBJ) $(TEST_INC)
	$(CC) $(TEST_OBJ_DIR)main.o $(TEST_OBJ) $(ASAN) $(GCOV_FLAGS) -o $(TEST_EXE) $(TST_LIBS) -L. $(TEST_LIB)

create_obj_test_dir:
	@$(MK) $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)main.o: main.c
	$(CC) $(CFLAGS) -o $(TEST_OBJ_DIR)main.o main.c

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c $(TEST_INC)
	$(CC) $(TST_CFLAGS) $< -o $@

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) $< -o $@

$(GCOV_OBJ): $(TEST_OBJ_DIR)%.o: $(SRC_DIR)%.c $(TEST_INC)
	$(CC) $(CFLAGS) $< -o $@

gcov_report: $(GCOV_TARGET)

$(GCOV_TARGET): CFLAGS += $(GCOV_FLAGS)
$(GCOV_TARGET): $(GCOV_INFO)
	genhtml $(GCOV_INFO) -o $(GCOV_TARGET)

$(GCOV_INFO): test
	$(DIR)$(TEST_EXE)
	geninfo $(TEST_OBJ_DIR) -b . -o $(DIR)$(GCOV_INFO)

open:
	open coverage/src/index.html

check_cpplint:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.c
	@clang-format -n *.h
	@clang-format -n $(TEST_DIR)*.c
	@clang-format -n $(TEST_DIR)*.h
	@rm .clang-format

check_cppcheck:
	-find . -type f -name "*.c" | xargs cppcheck -q --enable=all --inconclusive --platform=unix64 --std=c11

valgrind:
	valgrind ./run_test --leak-check=full

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(TEST_OBJ_DIR)
	$(RM) $(TEST_LIB)
	$(RM) $(GCOV_INFO)

fclean: clean
	$(RM) $(GCOV_TARGET)
	$(RM) $(TEST_EXE)
	$(RM) $(LIB)

re: fclean all

.PHONY: all open check_cpplint check_cppcheck clean fclean re
