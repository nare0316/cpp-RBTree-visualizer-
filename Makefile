# Compiler and Flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/usr/local/include
LDFLAGS  := -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build

# Target Executable Name
TARGET   := rbtree

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default Rule
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile C++ Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Build Directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build and Execute
run: $(TARGET)
	./$(TARGET)

# Clean Target
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all run clean