#include "CoreLogic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// HELPER FUNCTION

int getStatusPriority(std::string status) {

    if (status == "Pending") return 1;
    if (status == "In Transit") return 2;
    if (status == "Delivered") return 3;

    return 0;
}

// CREATE DELIVERY (C)

void createDelivery() {

    std::ofstream file("logistics.csv", std::ios::app);

    Delivery d;

    std::cout << "Tracking Number: ";
    getline(std::cin, d.trackingNumber);

    std::cout << "Sender Name: ";
    getline(std::cin, d.senderName);

    std::cout << "Receiver Name: ";
    getline(std::cin, d.receiverName);

    std::cout << "Origin: ";
    getline(std::cin, d.origin);

    std::cout << "Destination: ";
    getline(std::cin, d.destination);

    std::cout << "Status (Pending / In Transit / Delivered): ";
    getline(std::cin, d.status);

    file << "DELIVERY," << d.trackingNumber << ","
        << d.senderName << ","
        << d.receiverName << ","
        << d.origin << ","
        << d.destination << ","
        << d.status << "\n";

    file.close();

    std::cout << "Delivery created successfully!\n";
}

// READ ALL DELIVERIES (R)

void readDeliveries() {

    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "No records found.\n";
        return;
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');
        if (tag != "DELIVERY") continue;
        Delivery d;
        getline(ss, d.trackingNumber, ',');
        getline(ss, d.senderName, ',');
        getline(ss, d.receiverName, ',');
        getline(ss, d.origin, ',');
        getline(ss, d.destination, ',');
        getline(ss, d.status, ',');

        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << d.trackingNumber << "\n";
        std::cout << "Sender: " << d.senderName << "\n";
        std::cout << "Receiver: " << d.receiverName << "\n";
        std::cout << "Origin: " << d.origin << "\n";
        std::cout << "Destination: " << d.destination << "\n";
        std::cout << "Status: " << d.status << "\n";
    }

    file.close();
}

// SEARCH BY TRACKING (S) - LINEAR SEARCH

void searchByTracking() {

    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "No records found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter tracking number: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    bool found = false;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');
        if (tag != "DELIVERY") continue;
        Delivery d;
        getline(ss, d.trackingNumber, ',');
        getline(ss, d.senderName, ',');
        getline(ss, d.receiverName, ',');
        getline(ss, d.origin, ',');
        getline(ss, d.destination, ',');
        getline(ss, d.status, ',');

        if (d.trackingNumber == input) {

            std::cout << "\n=== DELIVERY FOUND ===\n";
            std::cout << "Tracking: " << d.trackingNumber << "\n";
            std::cout << "Sender: " << d.senderName << "\n";
            std::cout << "Receiver: " << d.receiverName << "\n";
            std::cout << "Origin: " << d.origin << "\n";
            std::cout << "Destination: " << d.destination << "\n";
            std::cout << "Status: " << d.status << "\n";

            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Delivery not found.\n";
    }

    file.close();
}

// SORT BY STATUS (T) - BUBBLE SORT

void sortByStatus() {

    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "No records found.\n";
        return;
    }

    std::vector<Delivery> deliveries;
    std::string line;

    // Load file into vector
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');
        if (tag != "DELIVERY") continue;
        Delivery d;
        getline(ss, d.trackingNumber, ',');
        getline(ss, d.senderName, ',');
        getline(ss, d.receiverName, ',');
        getline(ss, d.origin, ',');
        getline(ss, d.destination, ',');
        getline(ss, d.status, ',');

        deliveries.push_back(d);
    }

    file.close();

    // Bubble Sort
    for (int i = 0; i < (int)deliveries.size() - 1; i++) {

        for (int j = 0; j < (int)deliveries.size() - i - 1; j++) {

            if (getStatusPriority(deliveries[j].status) >
                getStatusPriority(deliveries[j + 1].status)) {

                std::swap(deliveries[j], deliveries[j + 1]);
            }
        }
    }

    // Display sorted results
    std::cout << "\n=== SORTED BY STATUS ===\n";

    for (auto &d : deliveries) {

        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << d.trackingNumber << "\n";
        std::cout << "Status: " << d.status << "\n";
    }
}

// UPDATE STATUS (U)

void updateDeliveryStatus() {

    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "No records found.\n";
        return;
    }

    std::vector<Delivery> deliveries;
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');
        if (tag != "DELIVERY") continue;
        Delivery d;
        getline(ss, d.trackingNumber, ',');
        getline(ss, d.senderName, ',');
        getline(ss, d.receiverName, ',');
        getline(ss, d.origin, ',');
        getline(ss, d.destination, ',');
        getline(ss, d.status, ',');

        deliveries.push_back(d);
    }

    file.close();

    std::string input;
    std::cout << "Enter tracking number to update: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool found = false;

    for (auto &d : deliveries) {

        if (d.trackingNumber == input) {

            std::cin.ignore();
            std::cout << "New status: ";
            getline(std::cin, d.status);

            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Delivery not found.\n";
        return;
    }

    std::ofstream out("logistics.csv");

    for (auto &d : deliveries) {

        out << "DELIVERY," << d.trackingNumber << ","
            << d.senderName << ","
            << d.receiverName << ","
            << d.origin << ","
            << d.destination << ","
            << d.status << "\n";
    }

    out.close();

    std::cout << "Status updated successfully!\n";
}

// DELETE DELIVERY (D)

void deleteDelivery() {

    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "No records found.\n";
        return;
    }

    std::vector<Delivery> deliveries;
    std::string line;

    while (getline(file, line)) {

        std::stringstream ss(line);
        std::string tag;
        getline(ss, tag, ',');
        if (tag != "DELIVERY") continue;

        Delivery d;

        getline(ss, d.trackingNumber, ',');
        getline(ss, d.senderName, ',');
        getline(ss, d.receiverName, ',');
        getline(ss, d.origin, ',');
        getline(ss, d.destination, ',');
        getline(ss, d.status, ',');

        deliveries.push_back(d);
    }

    file.close();

    std::string input;
    std::cout << "Enter tracking number to delete: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool removed = false;

    for (int i = 0; i < (int)deliveries.size(); i++) {

        if (deliveries[i].trackingNumber == input) {

            deliveries.erase(deliveries.begin() + i);
            removed = true;
            break;
        }
    }

    if (!removed) {
        std::cout << "Delivery not found.\n";
        return;
    }

    std::ofstream out("logistics.csv");

    for (auto &d : deliveries) {

        out << "DELIVERY," << d.trackingNumber << ","
            << d.senderName << ","
            << d.receiverName << ","
            << d.origin << ","
            << d.destination << ","
            << d.status << "\n";
    }
    out.close();

    std::cout << "Delivery deleted successfully!\n";
}

// LOAD FROM FILE (L) - reads logistics.csv and populates users and deliveries vectors on startup:

void loadFromFile(std::vector<User>& users, std::vector<Delivery>& deliveries) {
    std::ifstream file("logistics.csv");

    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
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