#include "CoreLogic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cctype>

// =====================
// MARIKINA LOCATION SYSTEM (HQ = OLOPSC)
// =====================

struct Location {
    std::string name;
    double distanceFromHQ;
};

std::vector<Location> locations = {
    {"OLOPSC New Gen Building (HQ)", 0.0},
    {"Concepcion Uno Market", 3.2},
    {"Marikina Heights Ayala Mall", 2.1},
    {"Rancho Estate", 2.8},
    {"Riverbanks Center", 6.2},
    {"Marikina Sports Center", 3.5},
    {"SM City Marikina", 5.8},
    {"Fortune Factory", 2.5},
    {"S&R Marikina", 4.5},
    {"Parang Playground and Market", 2.1},
    {"C&B Circle Mall", 2.3}
};

// =====================
// HELPERS
// =====================

int getStatusPriority(std::string status) {
    if (status == "Pending") return 1;
    if (status == "In Transit") return 2;
    if (status == "Delivered") return 3;
    return 0;
}

std::string generateTrackingNumber(int id) {
    std::ostringstream oss;
    oss << "TRK" << std::setfill('0') << std::setw(3) << id;
    return oss.str();
}

double getDistanceFromHQ(const std::string& location) {
    for (auto &l : locations) {
        if (l.name == location) {
            return l.distanceFromHQ;
        }
    }
    return -1.0;
}

int selectLocation(const std::string& label) {
    int choice;

    std::cout << "\nSelect " << label << " location:\n";

    for (int i = 0; i < locations.size(); i++) {
        std::cout << i << ". " << locations[i].name
                  << " (" << locations[i].distanceFromHQ << " km)\n";
    }

    while (true) {
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice >= 0 && choice < locations.size()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        std::cout << "Invalid choice. Try again.\n";
    }
}

// =====================
// CREATE DELIVERY
// =====================

void createDelivery(std::vector<Delivery>& logistics) {

    Delivery d;

    // Tracking number (auto-safe option)
    std::cout << "Tracking Number (leave blank for auto): ";
    getline(std::cin, d.trackingNumber);

    if (d.trackingNumber.empty()) {
        d.trackingNumber = generateTrackingNumber(logistics.size() + 1);
    }

    // check duplicate
    for (auto &x : logistics) {
        if (x.trackingNumber == d.trackingNumber) {
            std::cout << "Duplicate tracking number!\n";
            return;
        }
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

    // LALAMOVE STYLE PICKUP/DROPOFF
    int pickupIndex = selectLocation("PICKUP");
    int dropoffIndex = selectLocation("DROPOFF");

    d.origin = locations[pickupIndex].name;
    d.destination = locations[dropoffIndex].name;
    d.distance = locations[pickupIndex].distanceFromHQ;

    // status
    // Readded
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

// =====================
// READ DELIVERY
// =====================

void readDeliveries(const std::vector<Delivery>& logistics) {

    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    for (auto &d : logistics) {
        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << d.trackingNumber << "\n";
        std::cout << "Sender: " << d.senderName << "\n";
        std::cout << "Receiver: " << d.receiverName << "\n";
        std::cout << "Pickup: " << d.origin << "\n";
        std::cout << "Dropoff: " << d.destination << "\n";
        std::cout << "Status: " << d.status << "\n";
    }
}

// =====================
// SEARCH
// =====================

void searchByTracking(const std::vector<Delivery>& logistics) {

    if (logistics.empty()) {
    std::cout << "No records found.\n";
    return;
    }

    std::string input;
    while (true) {
    std::cout << "Enter tracking number: ";
    std::getline(std::cin, input);
    
    // Trim whitespace
    while (!input.empty() && (input[0] == ' ' || input[0] == '\r' || input[0] == '\n')) {
        input.erase(input.begin());
    }
    while (!input.empty() && (input.back() == ' ' || input.back() == '\r' || input.back() == '\n')) {
        input.pop_back();
    }
    
    if (!input.empty()) break;
    std::cout << "Tracking number cannot be empty.\n";
    }

    for (auto &d : logistics) {
        if (d.trackingNumber == input) {
            std::cout << "\nFOUND:\n";
            std::cout << d.trackingNumber << "\n";
            std::cout << d.senderName << " -> " << d.receiverName << "\n";
            std::cout << d.origin << " -> " << d.destination << "\n";
            std::cout << d.status << "\n";
            return;
        }
    }

    std::cout << "Not found.\n";
}

// =====================
// SORT (NOW BY DISTANCE, STILL COMPATIBLE NAME)
// =====================

void sortByDistance(std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    // Selection Sort by distance
    for (int i = 0; i < logistics.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < logistics.size(); j++) {
            if (logistics[j].distance < logistics[minIndex].distance) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(logistics[i], logistics[minIndex]);
        }
    }

    // Display sorted results
    std::cout << "\n=== SORTED BY DISTANCE FROM HQ ===\n";
    for (int i = 0; i < logistics.size(); i++) {
        std::cout << "\n----------------------\n";
        std::cout << "Tracking: " << logistics[i].trackingNumber << "\n";
        std::cout << "Pickup: " << logistics[i].origin << "\n";
        std::cout << "Status: " << logistics[i].status << "\n";
    }
}

// =====================
// UPDATE STATUS
// =====================

void updateDeliveryStatus(std::vector<Delivery>& logistics) {
    if (logistics.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    std::string input;
    while (true) {
    std::cout << "Enter tracking number: ";
    std::getline(std::cin, input);
    
    // Trim whitespace
    while (!input.empty() && (input[0] == ' ' || input[0] == '\r' || input[0] == '\n')) {
        input.erase(input.begin());
    }
    while (!input.empty() && (input.back() == ' ' || input.back() == '\r' || input.back() == '\n')) {
        input.pop_back();
    }
    
    if (!input.empty()) break;
    std::cout << "Tracking number cannot be empty.\n";
}
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

// =====================
// DELETE
// =====================

void deleteDelivery(std::vector<Delivery>& logistics) {

    std::string input;
    while (true) {
    std::cout << "Enter tracking number: ";
    std::getline(std::cin, input);
    
    // Trim whitespace
    while (!input.empty() && (input[0] == ' ' || input[0] == '\r' || input[0] == '\n')) {
        input.erase(input.begin());
    }
    while (!input.empty() && (input.back() == ' ' || input.back() == '\r' || input.back() == '\n')) {
        input.pop_back();
    }
    
    if (!input.empty()) break;
    std::cout << "Tracking number cannot be empty.\n";
}

    for (int i = 0; i < logistics.size(); i++) {
        if (logistics[i].trackingNumber == input) {
            logistics.erase(logistics.begin() + i);
            std::cout << "Deleted.\n";
            return;
        }
    }

    std::cout << "Not found.\n";
}