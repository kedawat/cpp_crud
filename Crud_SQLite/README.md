# CRUD Application with SQLite (C++)

A simple command-line CRUD (Create, Read, Update, Delete) application in C++ that manages user records using an SQLite database.

## What It Does

- Creates an SQLite database file (`users.db`) and a `users` table with `id` and `username` columns.
- Supports the following operations:
  - **Create** – Insert a new user with an ID and username.
  - **Read** – Retrieve and display a single user by ID, or list all users.
  - **Update** – Change the username of an existing user.
  - **Delete** – Remove a user by ID, or delete all users.

## Prerequisites

- **MinGW-w64** (g++ compiler)
- **SQLite3** development library installed (headers and `.a`/`.dll` files)
  - If using MSYS2: `pacman -S mingw-w64-ucrt-x86_64-sqlite3`
- **Make** (mingw32-make or GNU make)

## Project Structure

```
Crud_SQLite/
├── main.cpp          # Entry point – demonstrates CRUD operations
├── UserManager.h     # UserManager class declaration and User struct
├── UserManager.cpp   # UserManager class implementation (SQLite queries)
├── Makefile          # Build instructions
└── README.md
```

## How to Build and Run

1. Open a terminal in the `Crud_SQLite` directory.

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
Database connection established.
Table 'users' ready.
User with ID 1 created.
User with ID 2 created.
--- User Details ---
id: 1  username: Alice
--- User Details ---
id: 2  username: Bob
User with ID 1 updated.
User with ID 2 deleted.
--- All Users ---
id: 1  username: AliceUpdated
Database connection closed.
```

## Notes

- The database file `users.db` is created in the working directory.
- Each run clears and recreates user data as demonstrated in `main.cpp`.
- All SQL queries use **prepared statements** (`sqlite3_prepare_v2` with parameter binding) to prevent SQL injection.

---

## Changelog

### v1.1 – SQL Injection Prevention
- Replaced raw string concatenation in SQL queries with prepared statements (`sqlite3_prepare_v2`).
- All user inputs are now bound via `sqlite3_bind_*` functions, preventing SQL injection attacks.
- Affected methods: `createUser`, `getUser`, `getAllUsers`, `updateUser`, `deleteUser`, `deleteAllUsers`.
- Updated `main.cpp` demo to include security test cases (SQL injection attempt, duplicate key handling) and improved output formatting.

### v1.0 – Initial Release
- Basic CRUD operations with SQLite.
- SQL queries used string concatenation (not safe for production).
