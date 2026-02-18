# Compiler selection
CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -g

# Targets
TARGETS := main child

# Default target
all: $(TARGETS)

# Build main executable
main: main.c
	$(CC) $(CFLAGS) -o $@ $<

# Build child executable
child: child.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean
clean:
	rm -f $(TARGETS) *.o
	rm -f *.txt

.PHONY: all clean
