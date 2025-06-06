# Compiler and basic flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g

# Target name
TARGET = Main.out

# Default target - builds the program
all: $(TARGET)

# Build the main program
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

# Valgrind memory check
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Test build
test:
	@echo "NOT YET IMPLEMENTED!"

# Clean up built files
clean:
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM

# Tell make these aren't file names
.PHONY: all clean valgrind test