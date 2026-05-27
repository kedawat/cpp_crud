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
        bool createUser(int id, const std::string& username);
        User getUser(int id);
        std::vector<User> getAllUsers();
        bool updateUser(int id, const std::string& newUsername);
        bool deleteUser(int id);
        bool deleteAllUsers();
};

#endif // USER_MANAGER_H
