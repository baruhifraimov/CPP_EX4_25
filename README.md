# MyContainer - C++ Template Container with Custom Iterators

**Author:** baruh.ifraimov@gmail.com

## Project Overview

This project implements a generic template-based container class `MyContainer` in C++ with support for multiple custom iterator types. The container supports dynamic addition and removal of comparable elements (integers, doubles, strings, etc.) and provides six different iteration patterns.

## Features

### Core Container Operations
- **Dynamic Element Management**: Add and remove elements at runtime
- **Template Support**: Works with any comparable type (int, double, string, etc.)
- **Exception Handling**: Robust error handling with appropriate exceptions
- **Memory Safe**: No memory leaks (validated with valgrind)

### Six Iterator Types
1. **Order Iterator**: Traverses elements in insertion order
2. **AscendingOrder Iterator**: Traverses elements in sorted ascending order
3. **DescendingOrder Iterator**: Traverses elements in sorted descending order
4. **ReverseOrder Iterator**: Traverses elements in reverse insertion order
5. **SideCrossOrder Iterator**: Alternates between smallest and largest elements
6. **MiddleOutOrder Iterator**: Starts from middle, alternates left and right

## File Structure

```
CPP_EX4_25/
├── MyContainer.hpp   # Container implementation
├── main.cpp          # Showcase
├── test.cpp          # Test suite
├── doctest.h         # Testing framework header
├── makefile          # Makefile
└── README.md         # This documentation
```


### Iterator Classes

Each iterator class implements:
- **Constructor**: Takes container pointer and index
- **Copy Constructor**: Deep copy semantics
- **Destructor**: Automatic cleanup
- **Dereference Operators**: `operator*()` and `const operator*()`
- **Increment Operators**: Pre-increment `++it` and post-increment `it++`
- **Comparison Operators**: `operator==()` and `operator!=()`
- **Assignment Operator**: `operator=()`

## Exception Handling

The implementation provides comprehensive error handling:

### Container Operations
- **`remove()`**: Throws `std::invalid_argument` if element doesn't exist
- **Null Pointer**: All iterator constructors validate non-null container pointers

### Iterator Operations
- **Dereferencing**: Throws `std::out_of_range` when dereferencing end iterator
- **Increment**: Throws `std::out_of_range` when incrementing past end
- **Empty Container**: Handling of empty container edge cases

## Test Coverage

The test suite (`test.cpp`) provides comprehensive coverage on the next subjects:
1. Basic Operations Tests
2. Element Management Tests
3. Remove Operations Tests
4. Iterator Type Tests (All 6 Types)
5. Template Support Tests
6. Error Handling Tests
7. Edge Case Tests
---