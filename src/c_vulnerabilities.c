#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>  // Windows equivalent for access()

// C-specific memory vulnerabilities

void format_string_vulnerability() {
    printf("=== Format String Vulnerability Test ===\n");
    
    char user_input[100] = "User provided input: %x %x %x %x";
    
    // Vulnerable: user-controlled format string
    printf(user_input); // This can leak stack contents
    printf("\n");
    
    printf("Format string vulnerability demonstrated!\n");
}

void heap_corruption() {
    printf("=== Heap Corruption Test ===\n");
    
    // Allocate some memory
    char* buffer1 = malloc(32);
    char* buffer2 = malloc(32);
    
    strcpy(buffer1, "Buffer 1 data");
    strcpy(buffer2, "Buffer 2 data");
    
    printf("Before corruption:\n");
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2);
    
    // Vulnerable: write beyond buffer1 boundaries
    strcpy(buffer1, "This string is way too long and will corrupt heap metadata");
    
    printf("After corruption:\n");
    printf("Buffer1: %s\n", buffer1);
    printf("Buffer2: %s\n", buffer2); // This might show corrupted data
    
    // This free might crash due to heap corruption
    free(buffer1);
    free(buffer2);
    
    printf("Heap corruption vulnerability demonstrated!\n");
}

void stack_smashing() {
    printf("=== Stack Smashing Test ===\n");
    
    char buffer[16];
    
    // Vulnerable: no bounds checking
    gets(buffer); // This function is dangerous and deprecated
    
    printf("You entered: %s\n", buffer);
    printf("Stack smashing vulnerability demonstrated!\n");
}

void function_pointer_corruption() {
    printf("=== Function Pointer Corruption Test ===\n");
    
    // Function pointer that could be corrupted
    void (*func_ptr)() = NULL;
    
    char buffer[8];
    int* int_ptr = (int*)buffer;
    
    // Vulnerable: buffer overflow that overwrites function pointer
    strcpy(buffer, "AAAAAAAA"); // Fill buffer
    
    // Try to call the function pointer (this will likely crash)
    if (func_ptr != NULL) {
        printf("Calling function pointer...\n");
        func_ptr(); // This would crash or execute arbitrary code
    } else {
        printf("Function pointer is NULL (not corrupted in this example)\n");
    }
    
    printf("Function pointer corruption vulnerability demonstrated!\n");
}

void race_condition_demo() {
    printf("=== TOCTOU (Time-of-Check-Time-of-Use) Vulnerability Test ===\n");
    
    // Simulate a file operation race condition
    FILE* file = fopen("test_file.txt", "w");
    if (file) {
        fprintf(file, "Initial content");
        fclose(file);
    }
    
    // Vulnerable: check and use pattern
    // Using 0 instead of F_OK for Windows compatibility
    if (access("test_file.txt", 0) == 0) {
        // Between this check and the fopen, the file could be modified
        // by another process (simulated here)
        printf("File exists, opening...\n");
        
        // Simulate race condition window
        // In real scenario, attacker could replace file here
        
        FILE* file2 = fopen("test_file.txt", "r");
        if (file2) {
            char buffer[100];
            fgets(buffer, sizeof(buffer), file2);
            printf("File content: %s\n", buffer);
            fclose(file2);
        }
    }
    
    printf("TOCTOU race condition vulnerability demonstrated!\n");
}

void run_c_vulnerabilities() {
    printf("Running C-specific memory vulnerability tests...\n");
    printf("================================================\n");
    
    format_string_vulnerability();
    printf("\n");
    
    heap_corruption();
    printf("\n");
    
    // stack_smashing(); // Commented out as it requires user input
    printf("Stack smashing test skipped (requires user input)\n");
    printf("\n");
    
    function_pointer_corruption();
    printf("\n");
    
    race_condition_demo();
    printf("\n");
    
    printf("================================================\n");
    printf("C-specific vulnerability tests completed!\n");
}
