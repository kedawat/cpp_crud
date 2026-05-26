#include "UserManager.h"
#include <iostream>
#include <algorithm>

UserManager::UserManager(const std::string& dbPath) {
    // Initialize the SQLite database connection
    if (sqlite3_open(dbPath.c_str(), &db ) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else {
        std::cout << "Database connection established." << std::endl;
        createTable(); // Ensure the users table exists
    }
}

UserManager::~UserManager() {
    // Close the SQLite database connection
    if (db) {
        sqlite3_close(db);
        std::cout << "Database connection closed." << std::endl;
    }
}

void UserManager::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table 'users' created or already exists." << std::endl;
        deleteAllUsers(); // Clear existing data for a clean slate
    }
}

void UserManager::createUser(int id, const std::string& username) {
    std::string sql = "INSERT INTO users (id, username) VALUES (" + std::to_string(id) + ", '" + username + "');";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error inserting user: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "User with ID " << id << " created." << std::endl;
    }
}

static int getUserCallback(void* data, int argc, char** argv, char** colName) {
    User* user = static_cast<User*>(data);
    if (argv[0]) user->id = std::stoi(argv[0]);
    if (argv[1]) user->username = argv[1];
    std::cout << "id: " << user->id << "  username: " << user->username << std::endl;
    return 0;
}

User UserManager::getUser(int id) {
    std::string sql = "SELECT id, username FROM users WHERE id = " + std::to_string(id) + ";";
    char* errMsg = nullptr;
    User user{0, ""};
    std::cout << "--- User Details ---" << std::endl;
    if (sqlite3_exec(db, sql.c_str(), getUserCallback, &user, &errMsg) != SQLITE_OK) {
        std::cerr << "Error retrieving user: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        throw std::runtime_error("Database error");
    }
    if (user.id == 0) {
        throw std::runtime_error("User not found");
    }
    return user;
}

static int printAllUsersCallback(void* data, int argc, char** argv, char** colName) {
    for (int i = 0; i < argc; i++) {
        std::cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "  ";
    }
    std::cout << std::endl;
    return 0;
}

void UserManager::getAllUsers() {
    const char* sql = "SELECT id, username FROM users;";
    char* errMsg = nullptr;
    std::cout << "--- All Users ---" << std::endl;
    if (sqlite3_exec(db, sql, printAllUsersCallback, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error retrieving users: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void UserManager::updateUser(int id, const std::string& newUsername) {
    std::string sql = "UPDATE users SET username = '" + newUsername + "' WHERE id = " + std::to_string(id) + ";";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error updating user: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "User with ID " << id << " updated." << std::endl;
    }
}

void UserManager::deleteUser(int id) {
    std::string sql = "DELETE FROM users WHERE id = " + std::to_string(id) + ";";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error deleting user: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "User with ID " << id << " deleted." << std::endl;
    }
}

void UserManager::deleteAllUsers() {
    const char* sql = "DELETE FROM users;";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error deleting all users: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "All users deleted." << std::endl;
    }
}

