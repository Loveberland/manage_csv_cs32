# เขียนด้วย gemini เพราะกูเขียน makefile ไม่เป็น

# Set the C compiler
CC = gcc
# Set compiler flags and auto-dependencies
CFLAGS = -Wall -Wextra -O2 -MMD -MP

# Set the main executable name
TARGET = manage_csv_cs32
# Set the output directory for object files
OUT_DIR = out

# Get all .c files except tests
SRCS = $(filter-out t_choice.c t_time_manager.c, $(wildcard *.c))
# Define object file paths
OBJS = $(patsubst %.c, $(OUT_DIR)/%.o, $(SRCS))
# Define dependency file paths
DEPS = $(OBJS:.o=.d)

# Declare non-file targets
.PHONY: all run test_choice test_time clean

# Default target builds the main executable
all: $(TARGET)

# Target to create output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Target to link objects into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Target to compile .c files into .o files
$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include the generated dependency files
-include $(DEPS)

# Target to build and run the main program
run: $(TARGET)
	./$(TARGET)

# Target for the choice module test
test_choice: t_choice.c choice.c
	$(CC) $(CFLAGS) $^ -o $@
	./$@

# Target for the time_manager module test
test_time: t_time_manager.c time_manager.c
	$(CC) $(CFLAGS) $^ -o $@
	./$@

# Target to clean up the workspace
clean:
	rm -rf $(OUT_DIR) $(TARGET) test_choice test_time *.out

