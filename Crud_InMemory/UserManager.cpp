#include "UserManager.h"
#include <iostream>
#include <algorithm>

void UserManager::createUser(int id, const std::string& username) {
    userdatabase.push_back({id, username});
    std::cout << "User with ID " << id << " created." << std::endl;
}

User UserManager::getUser(int id) {
    for (const auto& user : userdatabase) {
        if (user.id == id) {
            return user;
        }
    }
    throw std::runtime_error("User not found");
}

void UserManager::updateUser(int id, const std::string& newUsername) {
    for (auto& user : userdatabase) {
        if (user.id == id) {
            user.username = newUsername;
            std::cout << "User with ID " << id << " updated." << std::endl;
            return;
        }
    }
    throw std::runtime_error("User not found");
}

void UserManager::deleteUser(int id) {
    auto it = std::remove_if(userdatabase.begin(), userdatabase.end(), [&](const User& user) {
        return user.id == id;
    });
    if (it != userdatabase.end()) {
        std::cout << "User with ID " << id << " deleted." << std::endl;
        userdatabase.erase(it, userdatabase.end());
    } else {
        throw std::runtime_error("User not found");
    }
}