#include "vulnerabilities.h"
#include <iostream>
#include <string>
#include <map>
#include <functional>

void print_usage() {
    std::cout << "Usage: memory_vulnerabilities [--test TEST_NAME]" << std::endl;
    std::cout << "Available tests:" << std::endl;
    std::cout << "  buffer_overflow" << std::endl;
    std::cout << "  use_after_free" << std::endl;
    std::cout << "  double_free" << std::endl;
    std::cout << "  memory_leaks" << std::endl;
    std::cout << "  dangling_pointers" << std::endl;
    std::cout << "  uninitialized_memory" << std::endl;
    std::cout << "  integer_overflow" << std::endl;
    std::cout << "  all (default)" << std::endl;
}

void run_all_tests() {
    std::cout << "Running all memory vulnerability tests..." << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Buffer overflow tests
    vulnerabilities::stack_buffer_overflow();
    std::cout << std::endl;
    vulnerabilities::heap_buffer_overflow();
    std::cout << std::endl;
    vulnerabilities::string_copy_overflow();
    std::cout << std::endl;
    
    // Use after free tests
    vulnerabilities::use_after_free_basic();
    std::cout << std::endl;
    vulnerabilities::use_after_free_complex();
    std::cout << std::endl;
    
    // Double free tests
    vulnerabilities::double_free_basic();
    std::cout << std::endl;
    vulnerabilities::double_free_complex();
    std::cout << std::endl;
    
    // Memory leak tests
    vulnerabilities::memory_leak_basic();
    std::cout << std::endl;
    vulnerabilities::memory_leak_complex();
    std::cout << std::endl;
    
    // Dangling pointer tests
    vulnerabilities::dangling_pointer_basic();
    std::cout << std::endl;
    vulnerabilities::dangling_pointer_complex();
    std::cout << std::endl;
    
    // Uninitialized memory tests
    vulnerabilities::uninitialized_memory_basic();
    std::cout << std::endl;
    vulnerabilities::uninitialized_memory_complex();
    std::cout << std::endl;
    
    // Integer overflow tests
    vulnerabilities::integer_overflow_basic();
    std::cout << std::endl;
    vulnerabilities::integer_overflow_complex();
    std::cout << std::endl;
    
    std::cout << "=========================================" << std::endl;
    std::cout << "All tests completed!" << std::endl;
    std::cout << "WARNING: This program demonstrates memory vulnerabilities." << std::endl;
    std::cout << "Do not use this code in production environments!" << std::endl;
}

void run_specific_test(const std::string& test_name) {
    std::map<std::string, std::function<void()>> test_map = {
        {"buffer_overflow", []() {
            vulnerabilities::stack_buffer_overflow();
            vulnerabilities::heap_buffer_overflow();
            vulnerabilities::string_copy_overflow();
        }},
        {"use_after_free", []() {
            vulnerabilities::use_after_free_basic();
            vulnerabilities::use_after_free_complex();
        }},
        {"double_free", []() {
            vulnerabilities::double_free_basic();
            vulnerabilities::double_free_complex();
        }},
        {"memory_leaks", []() {
            vulnerabilities::memory_leak_basic();
            vulnerabilities::memory_leak_complex();
        }},
        {"dangling_pointers", []() {
            vulnerabilities::dangling_pointer_basic();
            vulnerabilities::dangling_pointer_complex();
        }},
        {"uninitialized_memory", []() {
            vulnerabilities::uninitialized_memory_basic();
            vulnerabilities::uninitialized_memory_complex();
        }},
        {"integer_overflow", []() {
            vulnerabilities::integer_overflow_basic();
            vulnerabilities::integer_overflow_complex();
        }}
    };
    
    auto it = test_map.find(test_name);
    if (it != test_map.end()) {
        std::cout << "Running " << test_name << " tests..." << std::endl;
        std::cout << "=========================================" << std::endl;
        it->second();
        std::cout << "=========================================" << std::endl;
        std::cout << test_name << " tests completed!" << std::endl;
    } else {
        std::cout << "Unknown test: " << test_name << std::endl;
        print_usage();
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Memory Vulnerabilities Test Program" << std::endl;
    std::cout << "===================================" << std::endl;
    
    if (argc == 1) {
        // No arguments, run all tests
        run_all_tests();
    } else if (argc == 3 && std::string(argv[1]) == "--test") {
        // Run specific test
        run_specific_test(argv[2]);
    } else {
        print_usage();
        return 1;
    }
    
    return 0;
}
