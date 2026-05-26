#include "CoreLogic.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <cctype>

int main() {
    system("cls");
    std::ifstream testFile("logistics.csv");
    if (!testFile.is_open()) {
        std::cout << "SYSTEM ERROR: Database file not found. Creating new file...\n";
    } else {
        std::cout << "Database loaded successfully.\n";
    }
    testFile.close();

    std::vector<User> users;
    std::vector<Delivery> deliveries;
    loadFromFile(users, deliveries);
    // Auto-create admin if no users exist
    if (users.empty()) {
    User admin;
    admin.username = "admin";
    admin.password = "1234";
    users.push_back(admin);
    std::cout << "No accounts exist, default admin account created.\n";
    }
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
        std::cout << "Press Enter to continue...";
        std::cin.get();
        system("cls");

        // MAIN MENU LOOP
        do {
            system("cls");
            std::cout << "\n=== Logistics Tracker ===\n";
            std::cout << "[C] Create Delivery\n";
            std::cout << "[R] Read Deliveries\n";
            std::cout << "[U] Update Status\n";
            std::cout << "[D] Delete Delivery\n";
            std::cout << "[S] Search\n";
            std::cout << "[T] Sort\n";
            std::cout << "[L] Logout\n";
            std::cout << "[E] Exit\n";
            std::cout << "[A] Add User\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;
            choice = toupper(choice);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (choice) {
                case 'C': createDelivery(deliveries); break;
                case 'R': readDeliveries(deliveries); break;
                case 'U': updateDeliveryStatus(deliveries); break;
                case 'D': deleteDelivery(deliveries); break;
                case 'S': {std::string pin;
                std::cout << "Enter PIN: ";
                std::cin >> pin;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (pin == "1234") searchByTracking(deliveries);
                else std::cout << "Invalid PIN.\n";break;}
                case 'T': {std::string pin;
                std::cout << "Enter PIN: ";
                std::cin >> pin;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (pin == "1234") sortByStatus(deliveries);
                else std::cout << "Invalid PIN.\n";break;}
                case 'L': loggedIn = false;
                system("cls");
                break;
                case 'E': saveToFile(users, deliveries); std::cout << "Exiting...\n"; break;
                case 'A': {
                    User u;
                    while (true) {
                        std::cout << "Enter new username: ";
                        std::getline(std::cin, u.username);
                        if (u.username.empty()) {
                            std::cout << "Username cannot be empty.\n";
                            continue;
                        }
                        bool duplicate = false;
                        for (int i = 0; i < users.size(); i++) {
                            if (users[i].username == u.username) {
                                duplicate = true;
                                break;
                            }
                        }
                        if (duplicate) {
                            std::cout << "Username already exists! Try another.\n";
                            continue;
                        }
                        break;
                    }
                    while (true) {
                        std::cout << "Enter new password: ";
                        std::getline(std::cin, u.password);
                        if (u.password.empty()) {
                            std::cout << "Password cannot be empty.\n";
                            continue;
                        }
                        std::string confirm;
                        std::cout << "Confirm password: ";
                        std::getline(std::cin, confirm);
                        if (u.password != confirm) {
                            std::cout << "Passwords do not match. Try again.\n";
                            continue;
                        }
                        break;
                    }
                    users.push_back(u);
                    std::cout << "User registered successfully!\n";
                    break;
                }
                default: std::cout << "Invalid choice.\n";
            }

            if (choice != 'E' && loggedIn) {
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }

        } while (choice != 'E' && loggedIn);

    } while (choice != 'E');

    return 0;
}
