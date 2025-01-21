CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17

RM = rm -rf

TARGET = 3d_viewer

BUILD_DIR = build
SAVE_DIR = saved_images

ALL_SRC = $(wildcard *.cpp *.h  */*.cpp */*.h */*/*.cpp */*/*.h)

.PHONY: all build run clean delete clang

all: build

build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		mkdir $(BUILD_DIR); \
	fi
	@cd $(BUILD_DIR) && qmake ../.
	@cd $(BUILD_DIR) && make
	@clear
	@echo -- Build complete. Build directory: $(BUILD_DIR).
	@echo -- Use '"make run"' to start the program.

run:
	@./$(BUILD_DIR)/$(TARGET)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -cpp $< -o $@

clean:
	@$(RM) $(BUILD_DIR)
	@echo -- Clean complete.

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
	@echo -- File is formatted according to the style.
