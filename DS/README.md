# Data Structures

Implementations of common data structures in C and C++.

## Files

| File | Language | Description |
|------|----------|-------------|
| `LinkedList.c` | C | Singly linked list using structs and functions (`malloc`/`free`) |
| `LinkedListC++.cpp` | C++ | Singly linked list using structs with constructors (`new`/`delete`) |
| `LinkedListClass.cpp` | C++ | Singly linked list using a class with encapsulation and destructor |
| `CircularLinkedList.cpp` | C++ | Circular linked list using a class with insert, delete, and traversal |

## Operations Implemented

- **Insert** — Append a node at the end of the list
- **Delete** — Remove the first occurrence of a value
- **Print** — Display all elements in the list
- **Memory cleanup** — Free allocated memory (destructor in class version, explicit function in C++ version)

## Compilation

```bash
# C version
gcc LinkedList.c -o LinkedList

# C++ versions
g++ LinkedListC++.cpp -o LinkedListCpp
g++ LinkedListClass.cpp -o LinkedListClass
g++ CircularLinkedList.cpp -o CircularLinkedList
```
