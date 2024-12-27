CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17

RM = rm -rf

TARGET = 3d_viewer

BUILD_DIR = build

.PHONY: all build clean

all: clean build

build:
	@mkdir $(BUILD_DIR)
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
	$(RM) $(BUILD_DIR)