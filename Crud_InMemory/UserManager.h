#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>

struct User {
    int id;
    std::string username;
};

class UserManager{
    private:
    // This is a placeholder for the actual data storage mechanism
        std::vector<User> userdatabase;

    public:
        void createUser(int id, const std::string& username);
        User getUser(int id);
        void updateUser(int id, const std::string& newUsername);
        void deleteUser(int id);
};

#endif // USER_MANAGER_H
