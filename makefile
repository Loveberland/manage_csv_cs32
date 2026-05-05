# เขียนด้วย Gemini เพราะกูเขียน makefile ไม่เป็น

# --- Compiler and Flags ---
CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP

# --- Target Names & Directories ---
TARGET = manage_csv_cs32
TEST_TARGET = run_test
OUT_DIR = out

# --- Source and Object Files ---
SRCS = $(wildcard *.c)
MAIN_SRCS = $(filter-out tchoice.c, $(SRCS))

# Use patsubst to change .c to .o AND prepend the OUT_DIR/ path
OBJS = $(patsubst %.c, $(OUT_DIR)/%.o, $(MAIN_SRCS))

# Dependency files will also go into the out/ directory
DEPS = $(OBJS:.o=.d)

# --- Phony Targets ---
.PHONY: all clean run test

all: $(TARGET)

# --- Build Rules ---

# Rule to create the output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each .c file into the out/ directory
# The '| $(OUT_DIR)' is an order-only dependency ensuring the folder exists first
$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include the generated dependency files
-include $(DEPS)

# --- Utility Rules ---

run: $(TARGET)
	./$(TARGET)

test: tchoice.c choice.c
	$(CC) -Wall -Wextra tchoice.c choice.c -o $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up the output directory and executables
clean:
	rm -rf $(OUT_DIR) $(TARGET) $(TEST_TARGET) *.out

