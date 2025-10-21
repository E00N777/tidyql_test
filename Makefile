# Compiler and flags
CXX = g++
CC = gcc
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g -O0
CFLAGS = -Wall -Wextra -Wpedantic -g -O0
CPPFLAGS = -Iinclude

# Source files
SRC_DIR = src
INCLUDE_DIR = include
TESTS_DIR = tests

# C++ sources
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

# C sources
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

# Combine all objects
OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS)

# Test sources
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Main executable
TARGET = memory_vulnerabilities

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile C++ source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile C source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile test files
$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with address sanitizer
debug: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
debug: clean $(TARGET)

.PHONY: all clean run debug
