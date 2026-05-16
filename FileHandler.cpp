#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

// LOAD FROM FILE (L) - reads logistics.csv and populates users and deliveries vectors on startup:

void loadFromFile(std::vector<User>& users, std::vector<Delivery>& deliveries) {
    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines safely
        
        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');

        if (tag == "USER") {
            User u;
            getline(ss, u.username, ',');
            getline(ss, u.password, ',');
            users.push_back(u);
        } 
        else if (tag == "DELIVERY") {
            Delivery d;
            getline(ss, d.trackingNumber, ',');
            getline(ss, d.senderName, ',');
            getline(ss, d.receiverName, ',');
            getline(ss, d.origin, ',');
            getline(ss, d.destination, ',');
            getline(ss, d.status, ',');
            deliveries.push_back(d);
        }
    }
    file.close();
}

// SAVE TO FILE (S) — writes all users and deliveries back to logistics.csv on exit:

void saveToFile(const std::vector<User>& users, const std::vector<Delivery>& deliveries) {
    std::ofstream out("logistics.csv"); // Overwrites file

    for (const auto& u : users) {
        out << "USER," << u.username << "," << u.password << "\n";
    }

    for (const auto& d : deliveries) {
        out << "DELIVERY," << d.trackingNumber << ","
            << d.senderName << ","
            << d.receiverName << ","
            << d.origin << ","
            << d.destination << ","
            << d.status << "\n";
    }

    out.close();
}