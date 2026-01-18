# Compiler and Flags
CC = gcc
# -I allows us to include sll.h from the neighboring directory
CFLAGS = -Wall -Wextra -g -I../singly_linked_list -I.

# Relative paths to source files
SLL_DIR = ../singly_linked_list
QUEUE_DIR = .

# Source files
# We need sll.c to provide the implementation of the list functions
SRCS = $(SLL_DIR)/sll.c $(QUEUE_DIR)/queue.c $(QUEUE_DIR)/test_queue.c
OBJS = $(SRCS:.c=.o)

# Name of the executable (inside the current folder)
TARGET = test_queue

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
	rm -f $(SLL_DIR)/*.o $(QUEUE_DIR)/*.o

.PHONY: clean_bin
clean_bin:
	rm -f $(TARGET)

.PHONY: clean_all
clean_all: clean clean_bin
