CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
RM = rm -rf

#CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -fPIC -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets
#LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lQt6Core -lQt6Gui -lQt6Widgets

LIBS = -lgtest -lm
#$(LDFLAGS)
CPPFLAGS_TEST = -DUNIT_TESTS $(CPPFLAGS)

TARGET = 3d_viewer

BUILD_DIR = build
INSTALL_DIR = install
SAVE_DIR = saved_images

ALL_SRC = $(wildcard *.cpp *.h  */*.cpp */*.h */*/*.cpp */*/*.h)

TEST_SRC = tests/main_test.cpp  # Исходный файл для тестов
SRC = $(wildcard model/*.cpp controller/*.cpp model/s21_matrix/*.cpp)
OBJS = $(SRC:.cpp=.o) $(wildcard model/*.o)  # Добавили все .o файлы из папки model

VERSION = 2.0

.PHONY: all install uninstall clean dvi dist tests build run delete clang

all: install

install: build
	@mkdir -p $(INSTALL_DIR)
	@cp -p $(BUILD_DIR)/$(TARGET) $(INSTALL_DIR)
	@echo -- Install complete. Install directory: $(INSTALL_DIR)
	@echo -- Use '"make run"' to start the program.

uninstall:
	@$(RM) $(INSTALL_DIR)
	@echo -- Uninstall complete.

clean:
	@$(RM) $(BUILD_DIR)
	@$(RM) *.tar.gz
	@$(RM) doxygen
	@find model controller -type f -name "*.o" -exec rm -f {} \;
	@echo -- Clean complete.

dvi:
	doxygen
	open doxygen/html/index.html

dist:
	@if [ ! -d "$(TARGET)-$(VERSION)" ]; then \
		mkdir $(TARGET)-$(VERSION); \
	fi
	@cp -r controller model view Makefile $(TARGET)-$(VERSION)
	@tar -czf $(TARGET)-$(VERSION).tar.gz $(TARGET)-$(VERSION)
	@$(RM) $(TARGET)-$(VERSION)
	@echo -- Dist complete. Archive name '"$(TARGET)-$(VERSION).tar.gz"'.

tests: $(OBJS)
	$(CPP) $(CPPFLAGS_TEST) $(TEST_SRC) $(OBJS) -o viewer_test $(LIBS)
	./viewer_test

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -cpp $< -o $@

build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cd $(BUILD_DIR) && qmake ../.
	@cd $(BUILD_DIR) && make
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR).

run:
	@./$(INSTALL_DIR)/$(TARGET)

delete:
	@$(RM) settings.txt
	@if [ -d "$(SAVE_DIR)" ]; then \
		$(RM) $(SAVE_DIR); \
	fi
	@echo -- Delete complete. The settings file and saved images have been deleted.

clang:
	@cp ./../materials/linters/.clang-format ./
	@clang-format -i $(ALL_SRC)
	@rm -f .clang-format
	@echo -- Files is formatted according to the style.