#ifndef VULNERABILITIES_H
#define VULNERABILITIES_H

#include <string>
#include <vector>

// Function declarations for different vulnerability demonstrations
namespace vulnerabilities {

// Buffer overflow vulnerabilities
void stack_buffer_overflow();
void heap_buffer_overflow();
void string_copy_overflow();

// Use after free vulnerabilities
void use_after_free_basic();
void use_after_free_complex();

// Double free vulnerabilities
void double_free_basic();
void double_free_complex();

// Memory leak vulnerabilities
void memory_leak_basic();
void memory_leak_complex();

// Dangling pointer vulnerabilities
void dangling_pointer_basic();
void dangling_pointer_complex();

// Uninitialized memory vulnerabilities
void uninitialized_memory_basic();
void uninitialized_memory_complex();

// Integer overflow vulnerabilities
void integer_overflow_basic();
void integer_overflow_complex();

// Helper functions
void run_all_tests();
void run_specific_test(const std::string& test_name);

} // namespace vulnerabilities

#endif // VULNERABILITIES_H
