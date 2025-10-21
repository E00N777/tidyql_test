#include "vulnerabilities.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <memory>

namespace vulnerabilities {

// ==================== Buffer Overflow Vulnerabilities ====================

void stack_buffer_overflow() {
    std::cout << "=== Stack Buffer Overflow Test ===" << std::endl;
    
    // Vulnerable: fixed-size buffer that can be overflowed
    char buffer[10];
    
    // This will cause stack buffer overflow
    strcpy(buffer, "This string is way too long for the buffer!");
    
    std::cout << "Buffer content: " << buffer << std::endl;
    std::cout << "Stack buffer overflow occurred!" << std::endl;
}

void heap_buffer_overflow() {
    std::cout << "=== Heap Buffer Overflow Test ===" << std::endl;
    
    // Vulnerable: heap allocation with potential overflow
    char* heap_buffer = new char[20];
    
    // This will cause heap buffer overflow
    strcpy(heap_buffer, "This is a very long string that exceeds the allocated size");
    
    std::cout << "Heap buffer content: " << heap_buffer << std::endl;
    
    // Memory leak - buffer not freed (intentional for demonstration)
    // delete[] heap_buffer; // This line is commented to show the vulnerability
    std::cout << "Heap buffer overflow occurred and memory leak created!" << std::endl;
}

void string_copy_overflow() {
    std::cout << "=== String Copy Overflow Test ===" << std::endl;
    
    char source[] = "This source string is definitely longer than the destination buffer";
    char dest[15];
    
    // Vulnerable: using unsafe string copy
    strcpy(dest, source);
    
    std::cout << "Destination: " << dest << std::endl;
    std::cout << "String copy overflow occurred!" << std::endl;
}

// ==================== Use After Free Vulnerabilities ====================

void use_after_free_basic() {
    std::cout << "=== Basic Use After Free Test ===" << std::endl;
    
    int* ptr = new int(42);
    std::cout << "Before free: " << *ptr << std::endl;
    
    delete ptr; // Free the memory
    
    // Vulnerable: using pointer after free
    std::cout << "After free (use after free): " << *ptr << std::endl;
    
    std::cout << "Use after free vulnerability demonstrated!" << std::endl;
}

void use_after_free_complex() {
    std::cout << "=== Complex Use After Free Test ===" << std::endl;
    
    struct Data {
        int id;
        char name[20];
    };
    
    Data* data = new Data{1, "Test Data"};
    std::cout << "Data before free - ID: " << data->id << ", Name: " << data->name << std::endl;
    
    delete data;
    
    // Allocate new object in the same memory location
    int* new_data = new int[10];
    new_data[0] = 999;
    
    // Vulnerable: accessing freed memory through old pointer
    std::cout << "Accessing freed memory (use after free): " << data->id << std::endl;
    
    delete[] new_data;
    std::cout << "Complex use after free vulnerability demonstrated!" << std::endl;
}

// ==================== Double Free Vulnerabilities ====================

void double_free_basic() {
    std::cout << "=== Basic Double Free Test ===" << std::endl;
    
    int* ptr = new int(100);
    std::cout << "Value: " << *ptr << std::endl;
    
    delete ptr; // First free
    
    // Vulnerable: double free
    delete ptr; // Second free - this causes undefined behavior
    
    std::cout << "Double free vulnerability demonstrated!" << std::endl;
}

void double_free_complex() {
    std::cout << "=== Complex Double Free Test ===" << std::endl;
    
    char* buffer1 = new char[50];
    char* buffer2 = buffer1; // Aliasing pointers
    
    strcpy(buffer1, "Double free test data");
    std::cout << "Buffer1: " << buffer1 << std::endl;
    
    delete[] buffer1;
    
    // Vulnerable: freeing same memory through different pointer
    delete[] buffer2; // Double free through aliased pointer
    
    std::cout << "Complex double free vulnerability demonstrated!" << std::endl;
}

// ==================== Memory Leak Vulnerabilities ====================

void memory_leak_basic() {
    std::cout << "=== Basic Memory Leak Test ===" << std::endl;
    
    // Vulnerable: allocating memory without freeing it
    int* leaked_memory = new int[1000];
    
    for (int i = 0; i < 1000; i++) {
        leaked_memory[i] = i;
    }
    
    std::cout << "Created array with 1000 integers" << std::endl;
    std::cout << "Memory leak created - allocated memory not freed!" << std::endl;
    
    // Intentionally not calling: delete[] leaked_memory;
}

void memory_leak_complex() {
    std::cout << "=== Complex Memory Leak Test ===" << std::endl;
    
    // Vulnerable: memory leak in conditional branches
    int* data = new int[500];
    
    bool condition = true; // This could be dynamic in real scenarios
    
    if (condition) {
        // Allocate more memory
        int* more_data = new int[300];
        
        // Some processing...
        for (int i = 0; i < 300; i++) {
            more_data[i] = i * 2;
        }
        
        // Early return or exception could cause leak
        // return; // If we return here, more_data leaks
        
        // But we continue and intentionally don't free more_data
    }
    
    // Only free the first allocation
    delete[] data;
    
    std::cout << "Complex memory leak created - conditional allocation not freed!" << std::endl;
}

// ==================== Dangling Pointer Vulnerabilities ====================

void dangling_pointer_basic() {
    std::cout << "=== Basic Dangling Pointer Test ===" << std::endl;
    
    int* ptr = new int(50);
    std::cout << "Original value: " << *ptr << std::endl;
    
    delete ptr; // Free the memory
    
    // ptr is now a dangling pointer
    // Vulnerable: using dangling pointer
    *ptr = 100; // Writing through dangling pointer
    std::cout << "Modified through dangling pointer: " << *ptr << std::endl;
    
    std::cout << "Dangling pointer vulnerability demonstrated!" << std::endl;
}

void dangling_pointer_complex() {
    std::cout << "=== Complex Dangling Pointer Test ===" << std::endl;
    
    struct Node {
        int value;
        Node* next;
    };
    
    Node* head = new Node{1, nullptr};
    head->next = new Node{2, nullptr};
    
    // Create a reference to the second node
    Node* middle = head->next;
    
    // Delete the entire list
    delete head->next;
    delete head;
    
    // middle is now a dangling pointer
    // Vulnerable: accessing through dangling pointer
    std::cout << "Accessing through dangling pointer: " << middle->value << std::endl;
    
    std::cout << "Complex dangling pointer vulnerability demonstrated!" << std::endl;
}

// ==================== Uninitialized Memory Vulnerabilities ====================

void uninitialized_memory_basic() {
    std::cout << "=== Basic Uninitialized Memory Test ===" << std::endl;
    
    int uninitialized_var;
    
    // Vulnerable: using uninitialized variable
    std::cout << "Uninitialized variable value: " << uninitialized_var << std::endl;
    
    std::cout << "Uninitialized memory vulnerability demonstrated!" << std::endl;
}

void uninitialized_memory_complex() {
    std::cout << "=== Complex Uninitialized Memory Test ===" << std::endl;
    
    struct ComplexData {
        int data[5];
        bool flag;
        double value;
    };
    
    // Allocate but don't initialize
    ComplexData* data = new ComplexData;
    
    // Vulnerable: using uninitialized struct members
    std::cout << "Uninitialized data[0]: " << data->data[0] << std::endl;
    std::cout << "Uninitialized flag: " << data->flag << std::endl;
    std::cout << "Uninitialized value: " << data->value << std::endl;
    
    delete data;
    std::cout << "Complex uninitialized memory vulnerability demonstrated!" << std::endl;
}

// ==================== Integer Overflow Vulnerabilities ====================

void integer_overflow_basic() {
    std::cout << "=== Basic Integer Overflow Test ===" << std::endl;
    
    int max_int = 2147483647; // Maximum value for 32-bit signed int
    
    // Vulnerable: integer overflow
    int overflowed = max_int + 1;
    
    std::cout << "Max int: " << max_int << std::endl;
    std::cout << "Max int + 1 (overflow): " << overflowed << std::endl;
    
    std::cout << "Integer overflow vulnerability demonstrated!" << std::endl;
}

void integer_overflow_complex() {
    std::cout << "=== Complex Integer Overflow Test ===" << std::endl;
    
    // Vulnerable: integer overflow in memory allocation calculation
    int count = 1000000000; // Large number
    int element_size = 1000;
    
    // This calculation can overflow
    int total_size = count * element_size;
    
    std::cout << "Count: " << count << std::endl;
    std::cout << "Element size: " << element_size << std::endl;
    std::cout << "Total size (may be incorrect due to overflow): " << total_size << std::endl;
    
    // Attempt allocation with potentially incorrect size
    if (total_size > 0) {
        char* buffer = new char[total_size]; // This could allocate wrong amount
        std::cout << "Allocated buffer with potentially incorrect size" << std::endl;
        delete[] buffer;
    }
    
    std::cout << "Complex integer overflow vulnerability demonstrated!" << std::endl;
}

} // namespace vulnerabilities
