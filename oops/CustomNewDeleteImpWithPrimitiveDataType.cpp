#include <iostream>
#include <cstdlib> // For malloc() and free()

// ============================================================================
// 1. CUSTOM NEW FOR AN INTEGER ARRAY
// ============================================================================
int* custom_new_int_array(size_t count) {
    // Step A: Calculate the exact bytes needed
    // For 10 integers on a standard system: 10 * 4 bytes = 40 bytes
    size_t totalBytesNeeded = count * sizeof(int);

    // Step B: Grab raw bytes from the OS heap
    // This attaches the standard OS hidden block-size header automatically
    void* rawMemory = std::malloc(totalBytesNeeded);
    
    if (rawMemory == nullptr) {
        std::cout << "Failed to allocate memory for int array!\n";
        return nullptr;
    }

    // Step C: Convert the raw memory address into an integer pointer and return it
    // NOTE: There are NO constructors to run because 'int' is a primitive type!
    return static_cast<int*>(rawMemory);
}

// ============================================================================
// 2. CUSTOM DELETE FOR AN INTEGER ARRAY
// ============================================================================
void custom_delete_int_array(int* arrayPtr) {
    if (arrayPtr == nullptr) return;

    // NOTE: Since 'int' has no destructor, we do NOT need to loop through the array.
    // We don't need an array cookie. We just hand the pointer directly to free().
    //
    // free() automatically looks backward, reads the OS hidden size header, 
    // and reclaims all 40 bytes instantly.
    std::free(arrayPtr);
}

// ============================================================================
// MAIN EXECUTION
// ============================================================================
int main() {
    std::cout << "--- Allocating Integer Array of Size 10 ---\n";
    // This replaces: int* myArr = new int[10];
    int* myArr = custom_new_int_array(10);

    // Populating the array normally
    for (int i = 0; i < 10; i++) {
        myArr[i] = (i + 1) * 5; // 5, 10, 15, 20...
    }

    // Printing elements to verify it works
    std::cout << "myArr[0] = " << myArr[0] << "\n";
    std::cout << "myArr[5] = " << myArr[5] << "\n";

    std::cout << "\n--- Deallocating Integer Array ---\n";
    // This replaces: delete[] myArr;
    custom_delete_int_array(myArr);
    
    myArr = nullptr;
    std::cout << "Memory freed successfully!\n";

    return 0;
}