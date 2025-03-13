# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++11 -O2

# Target executable
TARGET := main

# Source file
SRC := main.cpp

# Object file
OBJ := main.o

# Default target (compiles the program)
all: $(TARGET)

# Compile the program
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile source file into object file
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets (these don't correspond to actual files)
.PHONY: all run clean
