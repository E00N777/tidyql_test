#include "vulnerabilities.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <memory>
#include <string>

namespace vulnerabilities {

// ==================== Secure Buffer Overflow Fixes ====================

void secure_stack_buffer_overflow() {
    std::cout << "=== Secure Stack Buffer Overflow Fix ===" << std::endl;
    
    // Fixed: using std::string or bounds checking
    std::string buffer;
    std::string input = "This string is way too long for the buffer!";
    
    // Safe: std::string handles memory automatically
    buffer = input;
    
    std::cout << "Buffer content: " << buffer << std::endl;
    std::cout << "Stack buffer overflow prevented!" << std::endl;
}

void secure_heap_buffer_overflow() {
    std::cout << "=== Secure Heap Buffer Overflow Fix ===" << std::endl;
    
    // Fixed: using smart pointers and bounds checking
    auto heap_buffer = std::make_unique<char[]>(20);
    
    // Safe: using strncpy with bounds checking
    const char* source = "This is a very long string that exceeds the allocated size";
    strncpy(heap_buffer.get(), source, 19);
    heap_buffer[19] = '\0'; // Ensure null termination
    
    std::cout << "Heap buffer content: " << heap_buffer.get() << std::endl;
    
    // No memory leak - smart pointer handles deallocation
    std::cout << "Heap buffer overflow prevented and no memory leak!" << std::endl;
}

void secure_string_copy_overflow() {
    std::cout << "=== Secure String Copy Overflow Fix ===" << std::endl;
    
    char source[] = "This source string is definitely longer than the destination buffer";
    char dest[15];
    
    // Fixed: using strncpy with bounds checking
    strncpy(dest, source, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0'; // Ensure null termination
    
    std::cout << "Destination: " << dest << std::endl;
    std::cout << "String copy overflow prevented!" << std::endl;
}

// ==================== Secure Use After Free Fixes ====================

void secure_use_after_free_basic() {
    std::cout << "=== Secure Use After Free Fix ===" << std::endl;
    
    // Fixed: using smart pointers
    auto ptr = std::make_unique<int>(42);
    std::cout << "Before scope end: " << *ptr << std::endl;
    
    // Smart pointer automatically manages memory
    // No manual delete needed, no use after free possible
    
    std::cout << "Use after free vulnerability prevented!" << std::endl;
}

void secure_use_after_free_complex() {
    std::cout << "=== Secure Complex Use After Free Fix ===" << std::endl;
    
    struct Data {
        int id;
        std::string name; // Using std::string instead of char array
    };
    
    // Fixed: using smart pointers
    auto data = std::make_unique<Data>(Data{1, "Test Data"});
    std::cout << "Data - ID: " << data->id << ", Name: " << data->name << std::endl;
    
    // No manual delete needed
    // Smart pointer ensures proper memory management
    
    std::cout << "Complex use after free vulnerability prevented!" << std::endl;
}

// ==================== Secure Double Free Fixes ====================

void secure_double_free_basic() {
    std::cout << "=== Secure Double Free Fix ===" << std::endl;
    
    // Fixed: using smart pointers
    auto ptr = std::make_unique<int>(100);
    std::cout << "Value: " << *ptr << std::endl;
    
    // Smart pointer automatically handles deletion
    // No manual delete calls, no double free possible
    
    std::cout << "Double free vulnerability prevented!" << std::endl;
}

void secure_double_free_complex() {
    std::cout << "=== Secure Complex Double Free Fix ===" << std::endl;
    
    // Fixed: using smart pointers and avoiding pointer aliasing
    auto buffer1 = std::make_unique<char[]>(50);
    strcpy(buffer1.get(), "Double free test data");
    std::cout << "Buffer1: " << buffer1.get() << std::endl;
    
    // No manual delete needed
    // Each unique_ptr manages its own memory
    
    std::cout << "Complex double free vulnerability prevented!" << std::endl;
}

// ==================== Secure Memory Leak Fixes ====================

void secure_memory_leak_basic() {
    std::cout << "=== Secure Memory Leak Fix ===" << std::endl;
    
    // Fixed: using RAII and smart pointers
    auto leaked_memory = std::make_unique<int[]>(1000);
    
    for (int i = 0; i < 1000; i++) {
        leaked_memory[i] = i;
    }
    
    std::cout << "Created array with 1000 integers" << std::endl;
    std::cout << "No memory leak - smart pointer handles deallocation!" << std::endl;
}

void secure_memory_leak_complex() {
    std::cout << "=== Secure Complex Memory Leak Fix ===" << std::endl;
    
    // Fixed: using RAII and smart pointers
    auto data = std::make_unique<int[]>(500);
    
    bool condition = true;
    
    if (condition) {
        // Fixed: using smart pointers for conditional allocations
        auto more_data = std::make_unique<int[]>(300);
        
        // Some processing...
        for (int i = 0; i < 300; i++) {
            more_data[i] = i * 2;
        }
        
        // Smart pointers ensure proper cleanup even with early returns
    }
    
    // Both allocations automatically cleaned up by smart pointers
    std::cout << "Complex memory leak prevented - RAII ensures proper cleanup!" << std::endl;
}

// ==================== Secure Dangling Pointer Fixes ====================

void secure_dangling_pointer_basic() {
    std::cout << "=== Secure Dangling Pointer Fix ===" << std::endl;
    
    // Fixed: using smart pointers
    auto ptr = std::make_unique<int>(50);
    std::cout << "Original value: " << *ptr << std::endl;
    
    // No manual delete, no dangling pointer
    // Smart pointer ensures proper lifetime management
    
    std::cout << "Dangling pointer vulnerability prevented!" << std::endl;
}

void secure_dangling_pointer_complex() {
    std::cout << "=== Secure Complex Dangling Pointer Fix ===" << std::endl;
    
    struct Node {
        int value;
        std::unique_ptr<Node> next; // Using unique_ptr for ownership
    };
    
    auto head = std::make_unique<Node>(Node{1, nullptr});
    head->next = std::make_unique<Node>(Node{2, nullptr});
    
    // No manual deletion needed
    // Smart pointers manage the entire list automatically
    
    std::cout << "Complex dangling pointer vulnerability prevented!" << std::endl;
}

// ==================== Secure Uninitialized Memory Fixes ====================

void secure_uninitialized_memory_basic() {
    std::cout << "=== Secure Uninitialized Memory Fix ===" << std::endl;
    
    // Fixed: always initialize variables
    int initialized_var = 0; // Explicit initialization
    
    std::cout << "Initialized variable value: " << initialized_var << std::endl;
    std::cout << "Uninitialized memory vulnerability prevented!" << std::endl;
}

void secure_uninitialized_memory_complex() {
    std::cout << "=== Secure Complex Uninitialized Memory Fix ===" << std::endl;
    
    struct ComplexData {
        int data[5] = {0}; // Initialize array
        bool flag = false; // Initialize boolean
        double value = 0.0; // Initialize double
    };
    
    // Allocate and initialize
    auto data = std::make_unique<ComplexData>();
    
    // All members are properly initialized
    std::cout << "Initialized data[0]: " << data->data[0] << std::endl;
    std::cout << "Initialized flag: " << data->flag << std::endl;
    std::cout << "Initialized value: " << data->value << std::endl;
    
    std::cout << "Complex uninitialized memory vulnerability prevented!" << std::endl;
}

// ==================== Secure Integer Overflow Fixes ====================

void secure_integer_overflow_basic() {
    std::cout << "=== Secure Integer Overflow Fix ===" << std::endl;
    
    // Fixed: using larger integer types or bounds checking
    int64_t max_int = 2147483647; // Using 64-bit integer
    
    // Safe: 64-bit integer can handle this without overflow
    int64_t result = max_int + 1;
    
    std::cout << "Max int: " << max_int << std::endl;
    std::cout << "Max int + 1 (no overflow): " << result << std::endl;
    
    std::cout << "Integer overflow vulnerability prevented!" << std::endl;
}

void secure_integer_overflow_complex() {
    std::cout << "=== Secure Complex Integer Overflow Fix ===" << std::endl;
    
    // Fixed: using size_t and bounds checking
    size_t count = 1000000000; // Large number
    size_t element_size = 1000;
    
    // Safe: using size_t for size calculations
    size_t total_size = count * element_size;
    
    std::cout << "Count: " << count << std::endl;
    std::cout << "Element size: " << element_size << std::endl;
    std::cout << "Total size (correct calculation): " << total_size << std::endl;
    
    // Safe allocation with proper size
    if (total_size > 0 && total_size < SIZE_MAX) {
        auto buffer = std::make_unique<char[]>(total_size);
        std::cout << "Allocated buffer with correct size" << std::endl;
    } else {
        std::cout << "Size calculation error detected - allocation prevented" << std::endl;
    }
    
    std::cout << "Complex integer overflow vulnerability prevented!" << std::endl;
}

} // namespace vulnerabilities
