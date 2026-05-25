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

void createDelivery(std::vector<Delivery>& logistics) {

    Delivery d;

    while(true) {
    std::cout << "Tracking Number: ";
    getline(std::cin, d.trackingNumber);
    if (d.trackingNumber.length() == 0 || d.trackingNumber.length() > 30) {
        std::cout << "Invalid! Must not be empty or longer than 30 characters.\n";
        continue;
    }
    bool duplicate = false;
    for (int i = 0; i < logistics.size(); i++) {
        if (logistics[i].trackingNumber == d.trackingNumber) {
            duplicate = true;
            break;
        }
    }
    if (duplicate) {
        std::cout << "Tracking number already exists! Please use a unique number.\n";
        continue;
    }
    break;
    }

    while(true) {
    std::cout << "Sender Name: ";
    getline(std::cin, d.senderName);
    if (d.senderName.length() > 0 && d.senderName.length() <= 51) break;
    std::cout << "Invalid! Sender name must not be empty or longer than 50 characters!\n";
    }

    while(true) {
    std::cout << "Receiver Name: ";
    getline(std::cin, d.receiverName);
    if (d.receiverName.length() > 0 && d.receiverName.length() <= 51) break;
    std::cout << "Invalid! Receiver name must not be empty or longer than 50 characters!!\n";
    }
    
    while(true) {
    std::cout << "Origin: ";
    getline(std::cin, d.origin);
    if (d.origin.length() > 0 && d.origin.length() <= 81) break;
    std::cout << "Invalid! Origin must not be empty or longer than 80 characters!\n";
    }

    while(true) {
    std::cout << "Destination: ";
    getline(std::cin, d.destination);
    if (d.destination.length() > 0 && d.destination.length() <= 81) break;
    std::cout << "Invalid! Destination must not be empty or longer than 80 characters!\n";
    }

    while(true) {
    std::cout << "Status (Pending / In Transit / Delivered): ";
    getline(std::cin, d.status);\
    for (int i = 0; i < d.status.length(); i++) {
    d.status[i] = tolower(d.status[i]);
    }
    if (!d.status.empty()) {
    d.status[0] = toupper(d.status[0]);
    for (int i = 1; i < d.status.length(); i++) {
        if (d.status[i-1] == ' ') {
            d.status[i] = toupper(d.status[i]);
        }
    }
}
    if (d.status == "Pending" || d.status == "In Transit" || d.status == "Delivered") break;
    std::cout << "Invalid! Please choose Pending, In Transit, or Delivered.\n";
    }

    logistics.push_back(d);

    std::cout << "Delivery created successfully!\n";
}

// READ ALL DELIVERIES (R)

void readDeliveries(const std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    for (int i = 0; i < logistics.size(); i++) {
        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << logistics[i].trackingNumber << "\n";
        std::cout << "Sender: " << logistics[i].senderName << "\n";
        std::cout << "Receiver: " << logistics[i].receiverName << "\n";
        std::cout << "Origin: " << logistics[i].origin << "\n";
        std::cout << "Destination: " << logistics[i].destination << "\n";
        std::cout << "Status: " << logistics[i].status << "\n";
    }
}

// SEARCH BY TRACKING (S) - LINEAR SEARCH

void searchByTracking(const std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    std::string input;
    std::cout << "Enter tracking number: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool found = false;
    for (int i = 0; i < logistics.size(); i++) {
        if (logistics[i].trackingNumber == input) {
            std::cout << "\n=== DELIVERY FOUND ===\n";
            std::cout << "Tracking: " << logistics[i].trackingNumber << "\n";
            std::cout << "Sender: " << logistics[i].senderName << "\n";
            std::cout << "Receiver: " << logistics[i].receiverName << "\n";
            std::cout << "Origin: " << logistics[i].origin << "\n";
            std::cout << "Destination: " << logistics[i].destination << "\n";
            std::cout << "Status: " << logistics[i].status << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Delivery not found.\n";
    }
}

// SORT BY STATUS (T) - BUBBLE SORT

void sortByStatus(std::vector<Delivery> logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    // Bubble Sort
    for (int i = 0; i < (int)logistics.size() - 1; i++) {
        for (int j = 0; j < (int)logistics.size() - i - 1; j++) {
            if (getStatusPriority(logistics[j].status) >
                getStatusPriority(logistics[j + 1].status)) {
                std::swap(logistics[j], logistics[j + 1]);
            }
        }
    }

    // Display sorted results
    std::cout << "\n=== SORTED BY STATUS ===\n";
    for (int i = 0; i < logistics.size(); i++) {
        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << logistics[i].trackingNumber << "\n";
        std::cout << "Status: " << logistics[i].status << "\n";
    }
}

// UPDATE STATUS (U)

void updateDeliveryStatus(std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter tracking number to update: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool found = false;

    for (int i = 0; i < logistics.size(); i++) {
        if (logistics[i].trackingNumber == input) {
            while(true) {
        std::cout << "New status (Pending / In Transit / Delivered): ";
        getline(std::cin, logistics[i].status);
        for (int j = 0; j < logistics[i].status.length(); j++) {
        logistics[i].status[j] = tolower(logistics[i].status[j]);
        }
        if (!logistics[i].status.empty()) {
        logistics[i].status[0] = toupper(logistics[i].status[0]);
        for (int j = 1; j < logistics[i].status.length(); j++) {
            if (logistics[i].status[j-1] == ' ') {
                logistics[i].status[j] = toupper(logistics[i].status[j]);
            }
            }
        }

        if (logistics[i].status == "Pending" || 
            logistics[i].status == "In Transit" || 
            logistics[i].status == "Delivered") break;
    
    std::cout << "Invalid! Please choose Pending, In Transit, or Delivered.\n";
}
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Delivery not found.\n";
        return;
    }

    std::cout << "Status updated successfully!\n";
}

// DELETE DELIVERY (D)

void deleteDelivery(std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    std::string input;
    std::cout << "Enter tracking number to delete: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool removed = false;

    for (int i = 0; i < (int)logistics.size(); i++) {
        if (logistics[i].trackingNumber == input) {
            logistics.erase(logistics.begin() + i);
            removed = true;
            break;
        }
    }

    if (!removed) {
        std::cout << "Delivery not found.\n";
        return;
    }

    std::cout << "Delivery deleted successfully!\n";
}