# Specify the compiler to use
CC = gcc

# Specify the target binary
TARGET = test

MAIN = test.c 
# HEADERS = lab1_IO.h

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

run:
	./$(TARGET)

# zip command will remove executables and input/output data files then zip 
# 	the contents according to the specified submission requirements
# zip:
# 	rm -rf $(OBJECTS) serialtester.o 
# 	rm -rf $(TARGET) serialtester matrixgen
# 	rm -rf data_input data_output
# 	zip $(ARCHIVE_NAME).zip ../Code ../Members
