CPP = g++  # Компилятор C++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lQt6Core -lQt6Gui -lQt6Widgets

RM = rm -rf

TARGET = 3d_viewer
BUILD_DIR = build
SAVE_DIR = saved_images

SRC = $(wildcard model/*.cpp controller/*.cpp model/s21_matrix/*.cpp)
OBJS = $(SRC:.cpp=.o) $(wildcard model/*.o)  # Добавили все .o файлы из папки model

LIBS = -lgtest -lm $(LDFLAGS) 
# Добавим флаг только для тестов
CPPFLAGS_TEST = -DUNIT_TESTS $(CPPFLAGS)

# Переменные для сборки тестов и основной программы
MAIN_SRC = main.cpp  # Основной исходный файл
TEST_SRC = tests/main_test.cpp  # Исходный файл для тестов 

.PHONY: all build run clean delete tests

# Главная цель для сборки
all: build

# Сборка основной программы
build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cd $(BUILD_DIR) && qmake ../.
	@cd $(BUILD_DIR) && make
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR).
	@echo -- Use '"make run"' to start the program.

# Запуск программы
run:
	@./$(BUILD_DIR)/$(TARGET)

# Правила для компиляции исходников
%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

# Очистка сборки
clean:
	@$(RM) $(BUILD_DIR)
	@find model controller -type f -name "*.o" -exec rm -f {} \;
	@echo -- Clean complete.


# Сборка и запуск тестов
tests: $(OBJS)
	$(CPP) $(CPPFLAGS_TEST) $(TEST_SRC) $(OBJS) -o viewer_test $(LIBS)
	./viewer_test

# Удаление временных файлов
delete:
	@$(RM) settings.txt
	@if [ -d "$(SAVE_DIR)" ]; then \
		$(RM) $(SAVE_DIR); \
	fi
	@echo -- Delete complete. The settings file and saved images have been deleted.
