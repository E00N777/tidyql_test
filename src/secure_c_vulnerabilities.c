#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

// Secure implementations for C-specific memory vulnerabilities

void secure_format_string_vulnerability() {
    printf("=== Secure Format String Fix ===\n");
    
    char user_input[100] = "User provided input: %x %x %x %x";
    
    // Fixed: using constant format string
    printf("%s", user_input); // Safe: format string is controlled
    printf("\n");
    
    printf("Format string vulnerability prevented!\n");
}

void secure_heap_corruption() {
    printf("=== Secure Heap Corruption Fix ===\n");
    
    // Fixed: proper bounds checking
    char* buffer1 = malloc(32);
    char* buffer2 = malloc(32);
    
    if (!buffer1 || !buffer2) {
        printf("Memory allocation failed\n");
        free(buffer1);
        free(buffer2);
        return;
    }
    
    strncpy(buffer1, "Buffer 1 data", 31);
    buffer1[31] = '\0';
    strncpy(buffer2, "Buffer 2 data", 31);
    buffer2[31] = '\0';
    
    printf("Before operation:\n");
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2);
    
    // Safe: bounds-checked copy
    const char* long_string = "This string is way too long and will corrupt heap metadata";
    strncpy(buffer1, long_string, 31);
    buffer1[31] = '\0';
    
    printf("After operation:\n");
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2); // This should not show corrupted data
    
    free(buffer1);
    free(buffer2);
    
    printf("Heap corruption vulnerability prevented!\n");
}

void secure_stack_smashing() {
    printf("=== Secure Stack Smashing Fix ===\n");
    
    char buffer[16];
    
    // Fixed: using fgets instead of gets
    printf("Enter text (max 15 characters): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input\n");
    }
    
    printf("Stack smashing vulnerability prevented!\n");
}

void secure_function_pointer_corruption() {
    printf("=== Secure Function Pointer Corruption Fix ===\n");
    
    // Function pointer with proper initialization
    void (*func_ptr)() = NULL;
    
    char buffer[8];
    
    // Safe: bounds-checked copy
    strncpy(buffer, "AAAAAAAA", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Function pointer remains NULL and safe
    if (func_ptr != NULL) {
        printf("Calling function pointer...\n");
        func_ptr();
    } else {
        printf("Function pointer is NULL (safe)\n");
    }
    
    printf("Function pointer corruption vulnerability prevented!\n");
}

void secure_race_condition_demo() {
    printf("=== Secure TOCTOU (Time-of-Check-Time-of-Use) Fix ===\n");
    
    // Simulate a secure file operation
    FILE* file = fopen("test_file.txt", "w");
    if (file) {
        fprintf(file, "Initial content");
        fclose(file);
    }
    
    // More secure approach: try to open directly
    FILE* file2 = fopen("test_file.txt", "r");
    if (file2) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), file2) != NULL) {
            printf("File content: %s\n", buffer);
        }
        fclose(file2);
    } else {
        printf("File does not exist or cannot be opened\n");
    }
    
    printf("TOCTOU race condition vulnerability mitigated!\n");
}

void run_secure_c_vulnerabilities() {
    printf("Running secure C-specific memory vulnerability tests...\n");
    printf("=======================================================\n");
    
    secure_format_string_vulnerability();
    printf("\n");
    
    secure_heap_corruption();
    printf("\n");
    
    // secure_stack_smashing(); // Commented out as it requires user input
    printf("Secure stack smashing test skipped (requires user input)\n");
    printf("\n");
    
    secure_function_pointer_corruption();
    printf("\n");
    
    secure_race_condition_demo();
    printf("\n");
    
    printf("=======================================================\n");
    printf("Secure C-specific vulnerability tests completed!\n");
}
