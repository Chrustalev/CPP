CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c++20
FLAGS_STD = -lstdc++

#TESTFLAGS= -pthread -lgtest -lgmock 

TESTFLAGS= -lgtest
MATHFLAGS= -lm

SRC = s21_matrix_oop.cpp s21_matrix_calc.cpp s21_matrix_adv.cpp
SRC_OBJ = s21_matrix_oop.o s21_matrix_calc.o s21_matrix_adv.o

TEST_SRC = test.cpp
TEST_OBJ = test.o

OPEN = x-www-browser

.PHONY: all clean test gcov_report s21_matrix_oop.a

s21_matrix_oop.a: clean
	$(CC) -c ${SRC} ${FLAGS} ${FLAGS_STD} ${MATHFLAGS}
	ar rcs s21_matrix_oop.a $(SRC_OBJ)

all: s21_matrix_oop.a


test: clean
	$(CC) ${SRC} ${TEST_SRC} -o ${TEST_OBJ} ${FLAGS} ${FLAGS_STD} ${TESTFLAGS} ${MATHFLAGS}
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s ./test.o
	
gcov_report: clean
	$(CC) --coverage ${SRC} ${TEST_SRC} -o ${TEST_OBJ} ${FLAGS} ${FLAGS_STD} ${TESTFLAGS} ${MATHFLAGS}
	./test.o
	lcov --directory . --capture -o coverage.info
	lcov --remove coverage.info '*13*' '*usr/include*' '*test*' -o filtered.info
	genhtml --output-directory report --legend filtered.info
	$(OPEN) report/index.html

cppcheck:
	clear
	cppcheck --enable=all --disable=unusedFunction --inconclusive --language=c++ --std=c++20 --force --verbose --error-exitcode=1 --check-level=exhaustive --suppress=missingIncludeSystem s21_*

clean:
	clear
	rm -rf *.out *.o *.a *.info *.gcda *.gcno test report

