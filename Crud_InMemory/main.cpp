#include <iostream>
#include <string>
#include "UserManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    UserManager userManager;
    userManager.createUser(1, "Alice");
    userManager.createUser(2, "Bob");
    userManager.updateUser(1, "AliceUpdated");
    userManager.deleteUser(2);
    return 0;
}

