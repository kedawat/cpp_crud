#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
#include <sqlite3.h>

struct User {
    int id;
    std::string username;
};

class UserManager{
    private:
    // This is a placeholder for the actual data storage mechanism
        sqlite3* db;
        void createTable(); // Method to create the users table if it doesn't exist   
    
    public:
        UserManager(const std::string& dbPath);   // Constructor to initialize the database connection
        ~UserManager();    // Destructor to close the database connection   

        // CRUD operations
        void createUser(int id, const std::string& username);
        User getUser(int id);
        void getAllUsers();
        void updateUser(int id, const std::string& newUsername);
        void deleteUser(int id);
        void deleteAllUsers();
};

#endif // USER_MANAGER_H
