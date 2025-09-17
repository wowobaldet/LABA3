# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 --coverage
LDFLAGS = --coverage -lboost_unit_test_framework

# Имена файлов
SOURCES = TEST.cpp
TARGET = test_runner
REPORT_DIR = coverage_report

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Основные цели
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск тестов
test: $(TARGET)
	./$(TARGET) --log_level=test_suite

# Генерация отчета о покрытии
coverage: test
  # Сбор информации о покрытии
	geninfo --ignore-errors mismatch --rc geninfo_unexecuted_blocks=1 . -o coverage.info
  # Фильтрация системных файлов
	lcov --remove coverage.info \
		'/usr/include/*' \
		--output-file filtered.info
  
  # Генерация HTML отчета
	genhtml filtered.info --output-directory $(REPORT_DIR) --ignore-errors inconsistent
	@echo "=========================================="
	@echo "Отчет о покрытии сгенерирован!"
	@echo "Откройте: $(REPORT_DIR)/index.html в браузере"
	@echo "=========================================="

# Просмотр отчета
view-coverage: coverage
	xdg-open $(REPORT_DIR)/index.html 2>/dev/null || \
	open $(REPORT_DIR)/index.html 2>/dev/null || \
	echo "Откройте $(REPORT_DIR)/index.html вручную"

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS) *.gcda *.gcno *.info
	rm -rf $(REPORT_DIR)

# Справка
help:
	@echo "Доступные команды:"
	@echo "  make all      - Сборка тестового запускателя"
	@echo "  make test     - Запуск тестов"
	@echo "  make coverage - Генерация отчета о покрытии"
	@echo "  make clean    - Очистка сгенерированных файлов"
	@echo "  make help     - Показать эту справку"

.PHONY: all test coverage view-coverage clean help
