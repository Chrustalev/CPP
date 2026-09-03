CXX = g++
FLAGS = -Wall -Werror -Wextra -std=c++20
FLAGS_NCURS = -lncurses
TESTFLAGS = -lgtest -lgtest_main -lpthread

DIR_DOC = doc
DIR_BUILD = build
DIR_DIST = dist
DIR_TEST = test

TETRIS = tetris
SNAKE = snake

DIR_TETRIS_LOGIC = brick_game/${TETRIS}
DIR_SNAKE_LOGIC = brick_game/${SNAKE}
DIR_CLI := gui/cli

SRC_TETRIS_LOGIC = logic.c
SRC_SNAKE_LOGIC = logic.cpp
SRC_SNAKE_CONTROL = controller.cpp

SRC_COMMON = brick_game/common.cpp
SRC_CLI = cli.c
SRC_MAIN = main_cli.cpp

SRC_TESTSNAKE = ${DIR_TEST}/test_snake.cpp 
SRC_TESTTETRIS = ${DIR_TEST}/test_tetris.cpp 

OBJ_TETRIS_CLI = tetris_cli
OBJ_SNAKE_CLI = snake_cli
OBJ_TETRIS_DESKTOP = tetris_desktop
OBJ_SNAKE_DESKTOP = snake_desktop

OBJ_TESTSNAKE = test/test_snake
OBJ_TESTTETRIS = test/test_tetris

PATH_TETRIS_LOGIC = ${DIR_TETRIS_LOGIC}/${SRC_TETRIS_LOGIC}
PATH_SNAKE_LOGIC = ${DIR_SNAKE_LOGIC}/${SRC_SNAKE_LOGIC}
PATH_SNAKE_CONTROL = ${DIR_SNAKE_LOGIC}/${SRC_SNAKE_CONTROL}

PATH_TETRIS_MAIN = frontend/${TETRIS}/${SRC_MAIN}
PATH_SNAKE_MAIN = frontend/${SNAKE}/${SRC_MAIN}

PATH_CLI = ${DIR_CLI}/${SRC_CLI}

PATH_OBJ_TETRIS_CLI = ${DIR_BUILD}/${TETRIS}/${OBJ_TETRIS_CLI}
PATH_OBJ_SNAKE_CLI = ${DIR_BUILD}/${SNAKE}/${OBJ_SNAKE_CLI}
PATH_OBJ_TETRIS_DESKTOP = ${DIR_BUILD}/${TETRIS}/${OBJ_TETRIS_DESKTOP}
PATH_OBJ_SNAKE_DESKTOP = ${DIR_BUILD}/${SNAKE}/${OBJ_SNAKE_DESKTOP}

OPEN = x-www-browser


#test.

.PHONY: all compile install uninstall clean tetris_cli snake_cli tetris_desktop snake_desktop test test_snake test_tetris

all: clean compile

compile: tetris_cli tetris_desktop snake_cli snake_desktop

dist: compile
	mkdir -p ${DIR_DIST}
	tar -cf ${DIR_DIST}/BrickGame2.0.tar -C ${DIR_BUILD} ${TETRIS}/${OBJ_TETRIS_CLI} \
	${TETRIS}/${OBJ_TETRIS_DESKTOP} ${SNAKE}/${OBJ_SNAKE_CLI} ${SNAKE}/${OBJ_SNAKE_DESKTOP}
	@echo "-= Дистрибутив создан в ${DIR_DIST}/BrickGame2.0.tar =-"

install: compile
	sudo cp ${PATH_OBJ_TETRIS_CLI} /usr/local/bin/
	sudo cp ${PATH_OBJ_SNAKE_CLI} /usr/local/bin/
	sudo cp ${PATH_OBJ_TETRIS_DESKTOP} /usr/local/bin/
	sudo cp ${PATH_OBJ_SNAKE_DESKTOP} /usr/local/bin/
	@echo "-= Игры установлены в /usr/local/bin/ =-"

uninstall:
	sudo rm -f /usr/local/bin/${OBJ_TETRIS_CLI} 
	sudo rm -f /usr/local/bin/${OBJ_SNAKE_CLI}
	sudo rm -f /usr/local/bin/${OBJ_TETRIS_DESKTOP} 
	sudo rm -f /usr/local/bin/${OBJ_SNAKE_DESKTOP}
	sudo rm -f ${HOME}/snakeHighScore.txt
	sudo rm -f ${HOME}/tetrisHighScore.txt
	@echo "-= Игры удалены =-"

dvi: 
	clear
	doxygen
	@echo "-= Документация создана =-"
	$(OPEN) ${DIR_DOC}/html/index.html

tetris_cli:
	mkdir ${DIR_BUILD} -p
	mkdir ${DIR_BUILD}/${TETRIS} -p
	$(CXX) ${PATH_TETRIS_MAIN} ${PATH_TETRIS_LOGIC} ${SRC_COMMON} ${PATH_CLI} ${FLAGS} -o ${PATH_OBJ_TETRIS_CLI} ${FLAGS_NCURS}
	@echo "-= Игра Тетрис с консольным интерфейсом успешно скомпилирована =-"

snake_cli:
	mkdir ${DIR_BUILD} -p
	mkdir ${DIR_BUILD}/${SNAKE} -p
	$(CXX) ${PATH_SNAKE_MAIN} ${PATH_SNAKE_LOGIC} ${PATH_SNAKE_CONTROL} ${SRC_COMMON} ${PATH_CLI} ${FLAGS} -o ${PATH_OBJ_SNAKE_CLI} ${FLAGS_NCURS}
	@echo "-= Игра Змейка с консольным интерфейсом успешно скомпилирована =-"


snake_desktop:
	mkdir ${DIR_BUILD} -p
	mkdir ${DIR_BUILD}/${SNAKE} -p
	cd ${DIR_BUILD}/${SNAKE} && qmake6 "../../frontend/snake/snake_desktop.pro"
	cd ${DIR_BUILD}/${SNAKE} && make
	@echo "-= Игра Змейка с десктопным интерфейсом успешно скомпилирована =-"

tetris_desktop:
	mkdir ${DIR_BUILD} -p
	mkdir ${DIR_BUILD}/${TETRIS} -p
	cd ${DIR_BUILD}/${TETRIS} && qmake6 "../../frontend/tetris/tetris_desktop.pro"
	cd ${DIR_BUILD}/${TETRIS} && sed -i 's/(CC)/(CXX)/g' Makefile
	cd ${DIR_BUILD}/${TETRIS} && sed -i 's/(CFLAGS)/(CXXFLAGS)/g' Makefile
	cd ${DIR_BUILD}/${TETRIS} && make
	@echo "-= Игра Тетрис с десктопным интерфейсом успешно скомпилирована =-"

test: test_snake test_tetris
test_snake: clean
	$(CXX) ${SRC_TESTSNAKE} ${PATH_SNAKE_LOGIC} ${PATH_SNAKE_CONTROL} ${SRC_COMMON} ${FLAGS} ${TESTFLAGS} -o ${OBJ_TESTSNAKE}
	./${OBJ_TESTSNAKE}
	@echo "-= Работа тестов логики игры змейка =-"


test_tetris: clean
	$(CXX) ${SRC_TESTTETRIS} ${PATH_TETRIS_LOGIC} ${SRC_COMMON} ${FLAGS} ${TESTFLAGS} -o ${OBJ_TESTTETRIS}
	./${OBJ_TESTTETRIS}
	@echo "-= Работа тестов логики игры тетрис =-"

coverage_tetris: FLAGS += --coverage
coverage_tetris: TESTFLAGS += --coverage
coverage_tetris: clean test_tetris
	@echo "-= Генерация отчета покрытия unit тестами логики игры тетрис =-"
	mkdir -p test/coverage
	gcovr --root . --html --html-details -o test/coverage/index.html --exclude test
	$(OPEN) ${DIR_TEST}/coverage/index.html

coverage_snake: FLAGS += --coverage
coverage_snake: TESTFLAGS += --coverage
coverage_snake: clean test_snake
	@echo "-= Генерация отчета покрытия unit тестами логики игры змейка =-"
	mkdir -p test/coverage
	gcovr --root . --html --html-details -o test/coverage/index.html --exclude test
	$(OPEN) ${DIR_TEST}/coverage/index.html

clang:
	clang-format -n --style Google brick_game/common*
	clang-format -n --style Google brick_game/tetris/*
	clang-format -n --style Google brick_game/snake/*
	clang-format -n --style Google gui/cli/*
	clang-format -n --style Google gui/desktop/*
	clang-format -n --style Google frontend/snake/*.cpp
	clang-format -n --style Google frontend/tetris/*.cpp

valgrind_snake:
	valgrind --tool=memcheck --leak-check=yes ./test/test_snake

valgrind_tetris:
	valgrind --tool=memcheck --leak-check=yes ./test/test_tetris

cppcheck:
	cppcheck brick_game/common.cpp --enable=all --disable=unusedFunction --inconclusive --language=c++ --std=c20 --force --verbose --error-exitcode=1 --suppress=missingIncludeSystem
	cppcheck brick_game/tetris/ --enable=all --disable=unusedFunction --inconclusive --language=c --std=c11 --force --verbose --error-exitcode=1 --suppress=missingIncludeSystem
	cppcheck brick_game/snake/*.cpp --enable=all --disable=unusedFunction --inconclusive --language=c++ --std=c20 --force --verbose --error-exitcode=1 --suppress=missingIncludeSystem


clean:
	clear
	rm -rf *.out *.o *.a ${DIR_BUILD} ${DIR_DIST} ${DIR_DOC} ${DIR_TEST}/*.gcda ${DIR_TEST}/*.gcno ${DIR_TEST}/coverage ${OBJ_TESTSNAKE} ${OBJ_TESTTETRIS}

