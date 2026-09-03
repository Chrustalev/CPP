# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -Wpedantic
INCLUDES = -I./include -I./include/detail -I.
TESTFLAGS = -lgtest -lgtest_main -lpthread

BUILD_DIR = build
TEST_SRC_DIR = test/src
TEST_MAIN = test/main_test.cpp

TEST_SOURCES = $(wildcard $(TEST_SRC_DIR)/*.cpp) $(TEST_MAIN)
TEST_OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))

TEST_EXEC = $(BUILD_DIR)/s21_containers_tests

# -------------------------------------------------------------------
# ПРАВИЛА СБОРКИ
# -------------------------------------------------------------------
all: test

$(TEST_EXEC): $(TEST_OBJECTS)
	@echo "Линковка тестов..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(TESTFLAGS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Компиляция: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# -------------------------------------------------------------------
# PHONY ЦЕЛИ (команды)
# -------------------------------------------------------------------
.PHONY: all test build clean rebuild help

build: $(TEST_EXEC)

test: build
	@echo "Запуск тестов..."
	@./$(TEST_EXEC)

clean:
	@echo "Очистка build директории..."
	@rm -rf $(BUILD_DIR)

rebuild: clean test

help:
	@echo "Доступные команды:"
	@echo "  make        - Собрать и запустить тесты (аналогично make test)"
	@echo "  make test   - Собрать и запустить тесты"
	@echo "  make build  - Только собрать тесты (без запуска)"
	@echo "  make clean  - Удалить build директорию"
	@echo "  make rebuild- Полная пересборка (clean + test)"
	@echo "  make help   - Показать эту справку"

# -------------------------------------------------------------------
# ДОПОЛНИТЕЛЬНЫЕ РЕЖИМЫ ТЕСТИРОВАНИЯ
# -------------------------------------------------------------------

.PHONY: test_valgrind test_sanitize coverage

test_valgrind: build
	@echo "Запуск тестов с Valgrind..."
	@valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          --error-exitcode=1 \
	          ./$(TEST_EXEC)

test_sanitize: CXXFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
test_sanitize: clean $(TEST_EXEC)
	@echo "Запуск тестов с санитайзерами..."
	@ASAN_OPTIONS=detect_leaks=1 ./$(TEST_EXEC)

coverage: CXXFLAGS += --coverage
coverage: TESTFLAGS += --coverage
coverage: clean $(TEST_EXEC)
	@echo "Запуск тестов для сбора покрытия..."
	@./$(TEST_EXEC)
	@echo "Генерация отчета покрытия..."
	@mkdir -p $(BUILD_DIR)/coverage
	@gcovr --root . \
	       --exclude=".*test.*" \
	       --exclude=".*build.*" \
	       --exclude=".*/usr/.*" \
	       --html-details $(BUILD_DIR)/coverage/index.html \
	       --print-summary
	@echo "Отчет: $(BUILD_DIR)/coverage/index.html"