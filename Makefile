# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Директории
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
INCLUDE_DIR = include

# Исходные файлы
SRC_FILES = $(SRC_DIR)/graph_coloring.c
TEST_FILES = $(TEST_DIR)/test_graph_coloring.c

# Объектные файлы
OBJ_FILES = $(BUILD_DIR)/graph_coloring.o
TEST_OBJ_FILES = $(BUILD_DIR)/test_graph_coloring.o

# Исполняемые файлы
TEST_EXEC = $(BUILD_DIR)/test_graph_coloring

# Цели по умолчанию
all: test

# Создание директории build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Компиляция основных объектных файлов
$(BUILD_DIR)/graph_coloring.o: $(SRC_DIR)/graph_coloring.c $(INCLUDE_DIR)/graph_coloring.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Компиляция тестовых объектных файлов
$(BUILD_DIR)/test_graph_coloring.o: $(TEST_DIR)/test_graph_coloring.c $(INCLUDE_DIR)/graph_coloring.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Сборка тестовой программы
$(TEST_EXEC): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

# Запуск тестов
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Пересборка
rebuild: clean all

# Отладочная сборка
debug: CFLAGS += -g -DDEBUG
debug: test

# Профилировочная сборка
profile: CFLAGS += -pg
profile: test

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all      - сборка по умолчанию (тесты)"
	@echo "  test     - сборка и запуск тестов"
	@echo "  debug    - сборка с отладочной информацией"
	@echo "  profile  - сборка с профилировкой"
	@echo "  clean    - очистка собранных файлов"
	@echo "  rebuild  - полная пересборка"
	@echo "  help     - эта справка"

.PHONY: all test debug profile clean rebuild help
