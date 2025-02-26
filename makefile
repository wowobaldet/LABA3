CC = g++
CFLAGS = -Wall -Wextra --coverage
LDFLAGS = --coverage
SOURCES =	TEST.cpp	
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = tests
REPORT_DIR = coverage_report

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(EXECUTABLE)
	./$(EXECUTABLE)	--log_level=test_suite

coverage: test
	lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
	genhtml coverage.info --output-directory $(REPORT_DIR) --ignore-errors inconsistent
	@echo "Отчёт о покрытии доступен в папке $(REPORT_DIR). Откройте index.html в браузере."

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR)