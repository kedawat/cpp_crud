#include "UserManager.h"
#include <iostream>
#include <algorithm>
#include <vector>

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

bool UserManager::createUser(int id, const std::string& username) {
    // Use a prepared statement to prevent SQL injection
    std::string sql = "INSERT INTO users (id, username) VALUES (?, ?);";
    
    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    // compile the SQL template into a statement object
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Bind the parameters to the statement
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    
    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting user: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        std::cout << "User with ID " << id << " created." << std::endl;
        sqlite3_finalize(stmt);
        return true;
    }
}

User UserManager::getUser(int id) {
    std::string sql = "SELECT id, username FROM users WHERE id = ?;";
    
    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Database error");
    }
    else {
        std::cout << "Prepared statement for retrieving user." << std::endl;
    }

    // Bind the parameter to the statement
    sqlite3_bind_int(stmt, 1, id);

    char* errMsg = nullptr;
    User user{0, ""};
    std::cout << "--- User Details ---" << std::endl;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.id = sqlite3_column_int(stmt, 0);
        user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::cout << "id: " << user.id << "  username: " << user.username << std::endl;
    } else {
        std::cerr << "Error retrieving user: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        throw std::runtime_error("Database error");
    }
    if (user.id == 0) {
        throw std::runtime_error("User not found");
    }
    sqlite3_finalize(stmt);
    return user;
}

std::vector<User> UserManager::getAllUsers() {
    const char* sql = "SELECT id, username FROM users;";
    char* errMsg = nullptr;
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return {};
    }
    
    std::vector<User> users;

    std::cout << "--- All Users ---" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        User user;
        user.id = sqlite3_column_int(stmt, 0);
        user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        users.push_back(user);
        std::cout << "id: " << user.id << "  username: " << user.username << std::endl;
    }
    sqlite3_finalize(stmt);
    return users;
}

bool UserManager::updateUser(int id, const std::string& newUsername) {
    std::string sql = "UPDATE users SET username = ? WHERE id = ?;";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error updating user: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        std::cout << "User with ID " << id << " updated." << std::endl;
        sqlite3_finalize(stmt);
        return true;
    }
}

bool UserManager::deleteUser(int id) {
    std::string sql = "DELETE FROM users WHERE id = ?;";
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }   

    sqlite3_bind_int(stmt, 1, id);

    char* errMsg = nullptr;

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error deleting user: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        std::cout << "User with ID " << id << " deleted." << std::endl;
        sqlite3_finalize(stmt);
        return true;
    } 
}

bool UserManager::deleteAllUsers() {
    const char* sql = "DELETE FROM users;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error deleting all users: " << errMsg << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_free(errMsg);
        return false;
    } else {
        std::cout << "All users deleted." << std::endl;
    }
    sqlite3_finalize(stmt);
    return true;
}
