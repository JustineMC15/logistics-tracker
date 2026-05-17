#include "CoreLogic.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <limits>

int main() {
    std::ifstream testFile("logistics.csv");
    if (!testFile.is_open()) {
        std::cout << "SYSTEM ERROR: Database file not found. Creating new file...\n";
    } else {
        std::cout << "Database loaded successfully.\n";
    }
    testFile.close();

    std::vector<User> users;
    std::vector<Delivery> deliveries;
    User testUser;
    testUser.username = "admin";
    testUser.password = "1234";
    users.push_back(testUser);

    bool loggedIn = false;
    char choice;

    do {
        loggedIn = false;

        // LOGIN LOOP
        do {
            std::string inputUsername;
            std::string inputPassword;
            std::cout << "Enter username: ";
            std::getline(std::cin, inputUsername);
            std::cout << "Enter password: ";
            std::getline(std::cin, inputPassword);
            if (inputUsername.empty() || inputPassword.empty()) {
                std::cout << "Username and password cannot be empty. Try again.\n";
                continue;
            }
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

        // MAIN MENU LOOP
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (choice) {
                case 'C': createDelivery(deliveries); break;
                case 'R': readDeliveries(deliveries); break;
                case 'U': updateDeliveryStatus(deliveries); break;
                case 'D': deleteDelivery(deliveries); break;
                case 'S': searchByTracking(deliveries); break;
                case 'T': sortByStatus(deliveries); break;
                case 'L': loggedIn = false; break;
                case 'E': saveToFile(users, deliveries); std::cout << "Exiting...\n"; break;
                default: std::cout << "Invalid choice.\n";
            }

        } while (choice != 'E' && loggedIn);

    } while (choice != 'E');

    return 0;
}

