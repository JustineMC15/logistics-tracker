#include "CoreLogic.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <vector>

int main() {

    std::vector<User> users;
    User testUser;
    testUser.username = "admin";
    testUser.password = "1234";
    users.push_back(testUser);

    bool loggedIn = false;

    do {
        std::string inputUsername;
        std::string inputPassword;

        std::cout << "Enter username: ";
        std::cin >> inputUsername;
        std::cout << "Enter password: ";
        std::cin >> inputPassword;

        for (int i = 0; i < users.size(); i++) {
            if (inputUsername == users[i].username && 
                inputPassword == users[i].password) {
                loggedIn = true;
                break;
            }
        }

        if (!loggedIn) {
            std::cout << "Invalid username or password. Try again.\n";
        }

    } while (!loggedIn);

    std::cout << "Login successful! Welcome.\n";

    // Main menu placeholder
    char choice;
    do {
        std::cout << "\n=== Logistics Tracker ===\n";
        std::cout << "[C] Create Delivery\n";
        std::cout << "[R] Read Deliveries\n";
        std::cout << "[U] Update Status\n";
        std::cout << "[D] Delete Delivery\n";
        std::cout << "[S] Search\n";
        std::cout << "[T] Sort\n";
        std::cout << "[L] Logout\n";
        std::cout << "[E] Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        choice = toupper(choice);

        switch (choice) {
            case 'C': ; break;
            case 'R': ; break;
            case 'U': ; break;
            case 'D': ; break;
            case 'S': ; break;
            case 'T': ; break;
            case 'L': ; break;
            case 'E': ; break;
            default: std::cout << "Invalid choice.\n";
        }

    } while (choice != 'E');

    return 0;
}