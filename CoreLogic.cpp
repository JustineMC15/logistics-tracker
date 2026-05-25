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

    std::cout << "Sender Name: ";
    getline(std::cin, d.senderName);

    std::cout << "Receiver Name: ";
    getline(std::cin, d.receiverName);

    // LALAMOVE STYLE PICKUP/DROPOFF
    int pickupIndex = selectLocation("PICKUP");
    int dropoffIndex = selectLocation("DROPOFF");

    d.origin = locations[pickupIndex].name;
    d.destination = locations[dropoffIndex].name;

    // status
    while (true) {
        std::cout << "Status (Pending / In Transit / Delivered): ";
        getline(std::cin, d.status);

        if (d.status == "Pending" ||
            d.status == "In Transit" ||
            d.status == "Delivered") {
            break;
        }

        std::cout << "Invalid status.\n";
    }

    logistics.push_back(d);

    std::cout << "Delivery created successfully!\n";

    double dist = getDistanceFromHQ(d.origin);
    if (dist != -1.0) {
        std::cout << "Pickup distance from HQ: " << dist << " km\n";
    }
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

        double dist = getDistanceFromHQ(d.origin);
        if (dist != -1.0) {
            std::cout << "Distance from HQ: " << dist << " km\n";
        }
    }
}

// =====================
// SEARCH
// =====================

void searchByTracking(const std::vector<Delivery>& logistics) {

    std::string input;
    std::cout << "Enter tracking number: ";
    std::cin >> input;
    std::cin.ignore();

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

void sortByStatus(std::vector<Delivery> logistics) {

    std::sort(logistics.begin(), logistics.end(),
        [](const Delivery& a, const Delivery& b) {

            double da = getDistanceFromHQ(a.origin);
            double db = getDistanceFromHQ(b.origin);

            if (da == -1.0) da = 9999;
            if (db == -1.0) db = 9999;

            return da < db;
        });

    std::cout << "\nSorted by distance from HQ.\n";
}

// =====================
// UPDATE STATUS
// =====================

void updateDeliveryStatus(std::vector<Delivery>& logistics) {

    std::string input;
    std::cout << "Enter tracking number: ";
    std::cin >> input;
    std::cin.ignore();

    for (auto &d : logistics) {
        if (d.trackingNumber == input) {

            while (true) {
                std::cout << "New status: ";
                getline(std::cin, d.status);

                if (d.status == "Pending" ||
                    d.status == "In Transit" ||
                    d.status == "Delivered") {
                    break;
                }

                std::cout << "Invalid.\n";
            }

            std::cout << "Updated.\n";
            return;
        }
    }

    std::cout << "Not found.\n";
}

// =====================
// DELETE
// =====================

void deleteDelivery(std::vector<Delivery>& logistics) {

    std::string input;
    std::cout << "Enter tracking number: ";
    std::cin >> input;

    for (int i = 0; i < logistics.size(); i++) {
        if (logistics[i].trackingNumber == input) {
            logistics.erase(logistics.begin() + i);
            std::cout << "Deleted.\n";
            return;
        }
    }

    std::cout << "Not found.\n";
}