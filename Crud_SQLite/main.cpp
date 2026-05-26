#include <iostream>
#include <string>
#include "UserManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    UserManager userManager("users.db");
    

    userManager.createUser(1, "Alice");
    userManager.createUser(2, "Bob");
    userManager.getUser(1);
    userManager.getUser(2);
    userManager.updateUser(1, "AliceUpdated");
    userManager.deleteUser(2);

    userManager.getAllUsers();
    
    return 0;
}

