CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lQt6Core -lQt6Gui -lQt6Widgets

RM = rm -rf

TARGET = 3d_viewer

SRC = $(wildcard model/*.cpp controller/*.cpp)
OBJS = $(SRC:.cpp=.o) $(wildcard model/*.o)  # Добавили все .o файлы из папки model
LIBS = -lgtest -lm $(LDFLAGS)

BUILD_DIR = build
TEST_DIR = tests

.PHONY: all build run clean delete tests

all: build

build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@$(CPP) $(CPPFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC) $(LIBS)
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR).
	@echo -- Use '"make run"' to start the program.

run:
	@./$(BUILD_DIR)/$(TARGET)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

delete:
	rm -f settings.txt

tests: $(OBJS)
	$(CPP) $(CPPFLAGS) tests/main_test.cpp  $^ -o viewer_test $(LIBS)
	./viewer_test
