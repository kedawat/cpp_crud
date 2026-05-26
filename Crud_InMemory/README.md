# CRUD Application - In-Memory (C++)

A simple command-line CRUD (Create, Read, Update, Delete) application in C++ that manages user records using an in-memory `std::vector`.

## What It Does

- Stores user data (ID and username) in a vector — no database or file persistence.
- Supports the following operations:
  - **Create** – Add a new user with an ID and username.
  - **Read** – Retrieve a user by ID.
  - **Update** – Change the username of an existing user.
  - **Delete** – Remove a user by ID.
- Data is lost when the program exits.

## Prerequisites

- **MinGW-w64** (g++ compiler)
- **Make** (mingw32-make or GNU make)

## Project Structure

```
Crud_InMemory/
├── main.cpp          # Entry point – demonstrates CRUD operations
├── UserManager.h     # UserManager class declaration and User struct
├── UserManager.cpp   # UserManager class implementation (vector-based)
├── Makefile          # Build instructions
└── README.md
```

## How to Build and Run

1. Open a terminal in the `Crud_InMemory` directory.

2. Build the project:
   ```
   make
   ```

3. Run the executable:
   ```
   ./main
   ```

4. Clean build artifacts:
   ```
   make clean
   ```

## Example Output

```
Hello, World!
User with ID 1 created.
User with ID 2 created.
User with ID 1 updated.
User with ID 2 deleted.
```

## Notes

- This is a basic in-memory implementation meant for learning CRUD concepts in C++.
- No data persistence — everything resets on each run.
- See the `Crud_SQLite` sibling project for a version with database persistence.
