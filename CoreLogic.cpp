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

// HELPER: GET DISTANCE FROM OLOPSC HeadQuarter (New Gen Building) 

double getDistanceFromHQ(const std::string& location) {
    //landmarks and barangays within Marikina City
    std::string landmarks[] = {
        "Concepcion Uno Market",
        "Marikina Heights Ayala Mall",
        "Rancho Estate",
        "Riverbanks Center",
        "Marikina Sports Center",
        "SM City Marikina",
        "Fortune Factory",
        "S&R Marikina",
        "Parang Playground and Market",
        "C&B Circle Mall"
    };

    double distances[] = {
        3.2,  // Concepcion Uno Market 
        2.1,  // Marikina Heights Ayala Mall
        2.8,  // Rancho Estate
        6.2,  // Riverbanks Center 
        3.5,  // Marikina Sports Center 
        5.8,  // SM City Marikina 
        2.5,  // Fortune Factory
        4.5,  // S&R Marikina
        2.1,  // Parang Playground and Market 
        2.3   // C&B Circle Mall
    };

    for (int i = 0; i < 10; i++) {
        if (location == landmarks[i]) {
            return distances[i];
        }
    }

    return -1.0; // Return -1 if landmark is not  found in the zone 
}

// CREATE DELIVERY (C)

void createDelivery(std::vector<Delivery>& logistics) {

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

    logistics.push_back(d);

    std::cout << "Delivery created successfully!\n";
    
    // Check and print HQ distance references upon creation
    double originDist = getDistanceFromHQ(d.origin);
    double destDist = getDistanceFromHQ(d.destination);
    
    if (originDist != -1.0) {
        std::cout << "[HQ Link] Origin is " << originDist << " km from OLOPSC New Gen Building.\n";
    }
    if (destDist != -1.0) {
        std::cout << "[HQ Link] Destination is " << destDist << " km from OLOPSC New Gen Building.\n";
    }
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
        
        // Show distance if the location matches to the landmarks
        double destDist = getDistanceFromHQ(logistics[i].destination);
        if (destDist != -1.0) {
            std::cout << "Distance from OLOPSC HQ: " << destDist << " km\n";
        }
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
            
            double destDist = getDistanceFromHQ(logistics[i].destination);
            if (destDist != -1.0) {
                std::cout << "Distance from OLOPSC HQ: " << destDist << " km\n";
            }
            
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
            std::cout << "New status: ";
            getline(std::cin, logistics[i].status);
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