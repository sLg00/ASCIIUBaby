# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -g
LDFLAGS := -lpng

# Directory structure
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := test
SCALE := 50

# Binary name
TARGET := $(BIN_DIR)/ascii_u_baby

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Test files
TEST_INPUT := $(TEST_DIR)/test_image.png
TEST_OUTPUT := $(TEST_DIR)/output_ascii.txt

# Default target
all: $(TARGET)

# Link binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Built binary: $(TARGET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $< -> $@"

# Test target
test: $(TARGET)
	@echo "Running test..."
	$(TARGET) -i $(TEST_INPUT) -o $(TEST_OUTPUT) -s $(SCALE)
	@echo "Test complete. ASCII art saved to: $(TEST_OUTPUT)"

# Clean target
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_OUTPUT)
	@echo "Cleaned build and test files."

# Phony targets
.PHONY: all clean test
