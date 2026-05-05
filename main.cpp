#include "CoreLogic.h"
#include "FileHandler.h"
#include <iostream>
#include <string>

int main() {
	
	std::vector<User> users;
	User testUser;
	testUser.username = "admin"
	testUser.password = "1234"
	users.push_back(testUser);

	bool loddedIn = false;
	do {

		std::string InputUsername;
		std::string InputPassword;
		std::cout << "Enter username: ";
		std::cin >> InputUsername;
		std::cout << "Enter password: ";
		std::cin >> InputPassword;
	
		for (int i = 0;users.size();i++) {
			if (InputUsername == user.username && InputPassword == user.password) {
				loggedIn = true;
				cout << "Login successful!" << endl;
				break;
			}
			if (!loggedIn)
				cout << "Invalid username or password. Please try again." << endl;
			}

	} while (!loggedIn);

	std::cout << "Welcome to the system!" << std::endl;

	return 0;

	}
	
	
}
