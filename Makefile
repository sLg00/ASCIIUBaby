# Compiler and flags
CC := gcc
CFLAGS := -I/opt/homebrew/opt/libpng/include/libpng16 -Wall -Wextra -Iinclude -g
LDFLAGS := -lpng -L/opt/homebrew/opt/libpng/lib -lpng16

# Directory structure
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := tests
SCALE := 50

# Final binary
TARGET := $(BIN_DIR)/ascii_u_baby

# Testing binaries
UNIT_TEST_BIN := $(BIN_DIR)/unit_tests
INT_TEST_BIN := $(BIN_DIR)/integration_tests

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

# Test targets
test_unit: $(UNIT_TEST_BIN)
	@echo "Running unit tests..."
	$(UNIT_TEST_BIN)

test_integration: $(INT_TEST_BIN)
	@echo "Running integration tests..."
	$(INT_TEST_BIN)

$(UNIT_TEST_BIN): $(TEST_DIR)/test_main.c $(filter-out $(SRC_DIR)/main.c, $(SRCS))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(INT_TEST_BIN): $(TEST_DIR)/test_integration.c $(filter-out $(SRC_DIR)/main.c, $(SRCS))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Clean target
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@rm -f $(TEST_DIR)/output_ascii.txt
	@echo "Cleaned build and test files."

# Phony targets
.PHONY: all clean test test_unit test_integration
