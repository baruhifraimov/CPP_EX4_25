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

# Test build and run
test: test.cpp
	$(CXX) $(CXXFLAGS) -o test.out test.cpp
	./test.out

# Build test executable only
test-build: test.cpp
	$(CXX) $(CXXFLAGS) -o test.out test.cpp

# Main target (for README requirement: make Main)
Main: $(TARGET)
	./$(TARGET)

# Clean up built files
clean:
	@rm -f $(TARGET)
	@rm -rf $(TARGET).dSYM
	@rm -f test.out
	@rm -rf test.out.dSYM

# Tell make these aren't file names
.PHONY: all clean valgrind test test-build Main