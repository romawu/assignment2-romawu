# Compiler selection
CC := $(CROSS_COMPILE)gcc

# Target and sources
TARGET := writer
SRC := writer.c
OBJ := $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build the writer application
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean