#include <iostream>
#include <string>
#include "UserManager.h"

// Helper function to print the current state of the database cleanly
void displayDatabaseState(UserManager& manager, const std::string& sectionName) {
    std::cout << "\n=========================================\n";
    std::cout << " DATABASE STATE: " << sectionName << "\n";
    std::cout << "=========================================\n";
    
    std::vector<User> users = manager.getAllUsers();
    if (users.empty()) {
        std::cout << "[Empty] No records found in the database.\n";
    } else {
        for (const auto& user : users) {
            std::cout << "ID: " << user.id << " | Name: " << user.username << "\n";
        }
    }
    std::cout << "=========================================\n\n";
}


int main() {

    // 1. Initialize the database file
    std::cout << "Initializing database engine...\n";
    UserManager manager("users.db");

    // Clear display at start
    displayDatabaseState(manager, "Initial Boot Up");

    // ----------------------------------------------------------------
    // 2. TESTING "CREATE" (Multiple Scenarios)
    // ----------------------------------------------------------------
    std::cout << "--- Executing CREATE Operations ---\n";
    
    // Batch adding normal users
    if (manager.createUser(1, "Alice"))   std::cout << "Successfully created Alice.\n";
    if (manager.createUser(2, "Bob"))     std::cout << "Successfully created Bob.\n";
    if (manager.createUser(3, "Charlie")) std::cout << "Successfully created Charlie.\n";
    if (manager.createUser(4, "Diana"))   std::cout << "Successfully created Diana.\n";

    // Testing Security: Attempting an SQL injection attack
    std::cout << "\nAttempting to inject malicious name string...\n";
    if (manager.createUser(5, "Hacker'; DROP TABLE users; --")) {
        std::cout << "Successfully neutralized and stored hacker input.\n";
    }

    // Testing Constraints: Attempting to insert a duplicate ID (Primary Key Conflict)
    std::cout << "\nAttempting to insert a duplicate ID (ID: 1)...\n";
    if (!manager.createUser(1, "Clone of Alice")) {
        std::cout << " Execution blocked: ID 1 already exists! (Database safety working correctly)\n";
    }

    displayDatabaseState(manager, "After Create Batch");

    // ----------------------------------------------------------------
    // 3. TESTING "UPDATE" (Multiple Scenarios)
    // ----------------------------------------------------------------
    std::cout << "--- Executing UPDATE Operations ---\n";

    // Update Bob to Robert
    if (manager.updateUser(2, "Robert")) {
        std::cout << "Updated ID 2: Name changed to Robert.\n";
    }

    // Update Diana to Diane
    if (manager.updateUser(4, "Diane")) {
        std::cout << "Updated ID 4: Name changed to Diane.\n";
    }

    // Testing Update on a non-existent ID
    std::cout << "\nAttempting to update a non-existent user (ID: 99)...\n";
    manager.updateUser(99, "Ghost User"); 
    // Note: In standard SQL, updating a row that doesn't exist executes successfully 
    // but affects 0 rows.

    displayDatabaseState(manager, "After Update Operations");

    // ----------------------------------------------------------------
    // 4. TESTING "DELETE" (Multiple Scenarios)
    // ----------------------------------------------------------------
    std::cout << "--- Executing DELETE Operations ---\n";

    // Delete Alice (ID 1)
    if (manager.deleteUser(1)) {
        std::cout << "Deleted User ID 1 (Alice).\n";
    }

    // Delete Charlie (ID 3)
    if (manager.deleteUser(3)) {
        std::cout << "Deleted User ID 3 (Charlie).\n";
    }

    displayDatabaseState(manager, "Final Database State");

    std::cout << "Program completed successfully. Closing connections.\n";
    return 0;
}


