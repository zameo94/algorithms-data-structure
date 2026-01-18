# Compiler and Flags
CC = gcc
# -I allows us to include sll.h from the neighboring directory
CFLAGS = -Wall -Wextra -g -I../singly_linked_list -I.

# Relative paths to source files
SLL_DIR = ../singly_linked_list
STACK_DIR = .

# Source files
# We need sll.c to provide the implementation of the list functions
SRCS = $(SLL_DIR)/sll.c $(STACK_DIR)/stack.c $(STACK_DIR)/test_stack.c
OBJS = $(SRCS:.c=.o)

# Name of the executable (inside the current folder)
TARGET = test_stack

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation step (converts .c to .o)
# The object files for SLL will be created in the SLL directory
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup: Removes object files and the test executable
.PHONY: clean
clean:
	rm -f $(SLL_DIR)/*.o $(STACK_DIR)/*.o

.PHONY: clean_bin
clean_bin:
	rm -f $(TARGET)

.PHONY: clean_all
clean_all: clean clean_bin
