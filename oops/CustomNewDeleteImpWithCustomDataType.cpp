#include <iostream>
#include <cstdlib> 
#include <new>     

struct Node {
    int data;
    Node* next;
    Node() { data = 0; next = nullptr; }
    ~Node() {
        std::cout << "[Destructor] Cleaning up Node holding data: " << data << "\n";
    }
};

// ============================================================================
// CUSTOM ALLOCATION WITH CAST EXPLANATIONS
// ============================================================================
Node* custom_new_node_array(size_t count) {
    size_t headerSize = sizeof(size_t); 
    size_t totalMemoryNeeded = headerSize + (count * sizeof(Node));

    // malloc returns a blank 'void*' pointer. 
    void* rawMemory = std::malloc(totalMemoryNeeded);
    if (rawMemory == nullptr) return nullptr;

    /*
     * 1. WHY STATIC_CAST HERE?
     * 'rawMemory' is a 'void*' (meaning "pointer to unknown memory"). 
     * Converting a universal 'void*' to a specific typed pointer (size_t*) is a 
     * standard, safe, and well-understood conversion in C++. 
     * static_cast tells the compiler: "Map this generic memory slot to a size_t pointer."
     */
    *(static_cast<size_t*>(rawMemory)) = count;

    /*
     * 2. WHY THE NESTED CASTS HERE?
     * We need to advance our pointer forward past the 8-byte header.
     *
     * Step A: static_cast<char*>(rawMemory)
     * You cannot perform math on a 'void*' because the compiler doesn't know its size.
     * We use static_cast to turn 'void*' into 'char*' because a 'char' is exactly 1 byte.
     * Adding 'headerSize' (8) shifts the pointer forward exactly 8 bytes.
     *
     * Step B: reinterpret_cast<Node*>( ... )
     * Now we have a pointer pointing to raw character bytes, but we want to build a NODE.
     * A 'char' and a 'Node' have absolutely zero relationship to each other. 
     * static_cast would throw a compile-time error here. 
     * We MUST use reinterpret_cast to say: "Force-treat these raw byte addresses as a Node pointer."
     */
    Node* arrayStartPtr = reinterpret_cast<Node*>(static_cast<char*>(rawMemory) + headerSize);

    // Loop and construct elements
    for (size_t i = 0; i < count; i++) {
        ::new (&arrayStartPtr[i]) Node();
    }

    return arrayStartPtr;
}

// ============================================================================
// CUSTOM DEALLOCATION WITH CAST EXPLANATIONS
// ============================================================================
void custom_delete_node_array(Node* arrayPtr) {
    if (arrayPtr == nullptr) return;

    size_t headerSize = sizeof(size_t);

    /*
     * 3. WHY REINTERPRET_CAST TO CHAR* AND THEN STATIC_CAST TO VOID*?
     *
     * Step A: reinterpret_cast<char*>(arrayPtr)
     * 'arrayPtr' is a 'Node*'. We need to subtract 8 bytes to find our hidden header.
     * To do byte math, we must force the compiler to treat the 'Node*' as a simple 
     * byte-sized 'char*'. Since Node and char are unrelated, we use reinterpret_cast.
     * Subtracting 'headerSize' slides the pointer backward by 8 bytes.
     *
     * Step B: static_cast<void*>( ... )
     * Now that we are back at the absolute beginning of the memory block, we need to 
     * convert our pointer into a format that std::free() accepts. 
     * free() takes a universal 'void*'. Converting any pointer to a 'void*' is completely 
     * safe and standard, so we use static_cast to safely sanitize it back to a 'void*'.
     */
    void* rawMemoryStart = static_cast<void*>(reinterpret_cast<char*>(arrayPtr) - headerSize);

    /*
     * 4. WHY STATIC_CAST TO SIZE_T*?
     * 'rawMemoryStart' is currently a blank 'void*'. To read the integer count we stored,
     * we must cast it to a 'size_t*' so the compiler knows how to read the data. 
     * Going from 'void*' to a specific pointer type is safe, hence static_cast.
     */
    size_t count = *(static_cast<size_t*>(rawMemoryStart));

    // Clean up nodes in reverse order
    for (size_t i = count; i > 0; i--) {
        arrayPtr[i - 1].~Node();
    }

    std::free(rawMemoryStart);
}

int main() {
    size_t arraySize = 5;
    std::cout << "--- 1. Allocating Array of " << arraySize << " Nodes ---\n";
    Node* myArr = custom_new_node_array(arraySize);

    std::cout << "\n--- 2. Adding Values to Array ---\n";
    for (size_t i = 0; i < arraySize; i++) {
        myArr[i].data = (i + 1) * 10; // Fills array with 10, 20, 30, 40, 50
        std::cout << "Assigned " << myArr[i].data << " to element index [" << i << "]\n";
    }

    std::cout << "\n--- 3. Reading/Printing Values from Array ---\n";
    for (size_t i = 0; i < arraySize; i++) {
        std::cout << "Reading from index [" << i << "]: " << myArr[i].data << "\n";
    }

    std::cout << "\n--- 4. Deallocating Array (Triggering Destructors) ---\n";
    custom_delete_node_array(myArr);
    
    // Safely zero out the pointer so we don't accidentally access ghost memory
    myArr = nullptr; 

    std::cout << "\n--- 5. Final Status Check ---\n";
    if (myArr == nullptr) {
        std::cout << "SUCCESS: Array memory has been freed and pointer is set to NULL!\n";
    }

    return 0;
}