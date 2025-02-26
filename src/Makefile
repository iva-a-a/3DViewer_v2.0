CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -coverage
RM = rm -rf

# Определяем переменную для операционной системы
OS := $(shell uname)

# Устанавливаем флаги в зависимости от операционной системы
ifeq ($(OS),Linux)
    FLAGS_TEST = -fPIC -I/usr/include/x86_64-linux-gnu/qt6 \
	-I/usr/include/x86_64-linux-gnu/qt6/QtCore \
	-I/usr/include/x86_64-linux-gnu/qt6/QtGui \
	-I/usr/include/x86_64-linux-gnu/qt6/QtWidgets
    LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lQt6Core -lQt6Gui -lQt6Widgets

	LIBS = -lgtest -lm -lsubunit -pthread $(LDFLAGS)
endif

ifeq ($(OS),Darwin)
    FLAGS_TEST = -I. -I/opt/homebrew/lib/QtCore.framework/Headers \
	-I/opt/homebrew/include \
	-I/opt/homebrew/lib/QtGui.framework/Headers \
	-I/opt/homebrew/lib/QtWidgets.framework/Headers \
	-I/opt/homebrew/Cellar/googletest/1.16.0/include \
	-I/opt/homebrew/Cellar/googletest/1.16.0

    LDFLAGS = -F/opt/homebrew/lib -framework QtWidgets \
	-framework QtGui -framework AppKit \
	-framework ImageIO -framework Metal \
	-framework QtCore -framework IOKit \
	-framework DiskArbitration \
	-framework AGL \
	-framework OpenGL \
	-L/opt/homebrew/Cellar/googletest/1.16.0/lib

	LIBS = -lm  -lgtest -lgtest_main -pthread $(LDFLAGS)
endif

CPPFLAGS_TEST = -DUNIT_TESTS $(FLAGS_TEST)

TARGET = 3d_viewer

BUILD_DIR = build
INSTALL_DIR = install
SAVE_IMAGE_DIR = saved_images
SAVE_GIF_DIR = saved_screencasts
GCOV_DIR = gcov_report

ALL_SRC = $(wildcard *.cpp *.h  */*.cpp */*.h */*/*.cpp */*/*.h)

TEST_SRC = tests/main_test.cpp
SRC_TEST = $(wildcard model/*.cpp controller/*.cpp model/matrix/*.cpp)
OBJS_TEST = $(SRC_TEST:.cpp=.o)

VERSION = 2.0

.PHONY: all install uninstall clean dvi dist tests build run delete clang gcov_report

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
	@$(RM) viewer_test
	@$(RM) $(GCOV_DIR)
	@find model controller -type f -name "*.o" -exec rm -f {} \;
	@find . -name "*.gcda" -exec rm -f {} \;
	@find . -name "*.gcno" -exec rm -f {} \;
	@find . -name "*.gcov" -exec rm -f {} \;
	@echo -- Clean complete.

dvi:
	@doxygen
	@clear
	@open doxygen/html/index.html || xdg-open doxygen/html/index.html || echo "Please open doxygen/html/index.html manually."
	@echo -- Dvi complete.

dist:
	@if [ ! -d "$(TARGET)-$(VERSION)" ]; then \
		mkdir $(TARGET)-$(VERSION); \
	fi
	@cp -r controller model view Makefile $(TARGET)-$(VERSION)
	@tar -czf $(TARGET)-$(VERSION).tar.gz $(TARGET)-$(VERSION)
	@$(RM) $(TARGET)-$(VERSION)
	@echo -- Dist complete. Archive name '"$(TARGET)-$(VERSION).tar.gz"'.

tests: $(OBJS_TEST)
	@$(CPP) $(CPPFLAGS) $(CPPFLAGS_TEST) $(TEST_SRC) $(OBJS_TEST) -o viewer_test $(LIBS)
	./viewer_test

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) $(CPPFLAGS_TEST) -c $< -o $@

build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cd $(BUILD_DIR) && qmake6 ../.
	@cd $(BUILD_DIR) && make
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR).

run:
	@./$(INSTALL_DIR)/$(TARGET)

gcov_report: CPPFLAGS_TEST += $(GCOV_FLAGS)
gcov_report: tests
	@mkdir -p $(GCOV_DIR)
	@gcovr -r . --html --html-details -o $(GCOV_DIR)/index.html
	@echo -- Gcov HTML report generated in $(GCOV_DIR)/index.html.
	@xdg-open $(GCOV_DIR)/index.html || open $(GCOV_DIR)/index.html || echo "Please open $(GCOV_DIR)/index.html manually."

delete:
	@$(RM) settings.txt
	@if [ -d "$(SAVE_IMAGE_DIR)" ]; then \
		$(RM) $(SAVE_IMAGE_DIR); \
	fi
	@if [ -d "$(SAVE_GIF_DIR)" ]; then \
		$(RM) $(SAVE_GIF_DIR); \
	fi
	@echo -- Delete complete. The settings file and saved images have been deleted.

clang:
	@cp ./../materials/linters/.clang-format ./
	@clang-format -i $(ALL_SRC)
	@rm -f .clang-format
	@echo -- Files is formatted according to the style.
