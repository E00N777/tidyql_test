# Memory Vulnerabilities Test Project

A C/C++ test project demonstrating various classic memory vulnerabilities.

## Vulnerabilities Included

1. **Buffer Overflow** - Stack-based and heap-based buffer overflows
2. **Use After Free** - Accessing memory after it has been freed
3. **Double Free** - Freeing the same memory block twice
4. **Memory Leaks** - Allocating memory without freeing it
5. **Dangling Pointers** - Pointers to freed memory
6. **Uninitialized Memory** - Using uninitialized variables
7. **Integer Overflow** - Arithmetic operations causing integer overflow

## Build Instructions

```bash
# Build the project
make

# Run all tests
./memory_vulnerabilities

# Run specific vulnerability tests
./memory_vulnerabilities --test buffer_overflow
./memory_vulnerabilities --test use_after_free
./memory_vulnerabilities --test double_free
./memory_vulnerabilities --test memory_leaks
./memory_vulnerabilities --test dangling_pointers
./memory_vulnerabilities --test uninitialized_memory
./memory_vulnerabilities --test integer_overflow
```

## Project Structure

- `src/` - Source code files
- `include/` - Header files
- `tests/` - Test files
- `Makefile` - Build configuration
