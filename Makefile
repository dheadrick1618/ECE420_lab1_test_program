# Specify the compiler to use
CC = gcc

# Specify the target binary
TARGET = test

MAIN = test.c 

# Specify the object files that make up the target
OBJECTS = test.o 

# Specify the compiler flags
CFLAGS = -Wall -g -std=c99

# Default target
all: $(TARGET)

# Rule to build the target binary
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lm

# Rule to build the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean target
clean:
	rm -f $(TARGET) $(OBJECTS)
