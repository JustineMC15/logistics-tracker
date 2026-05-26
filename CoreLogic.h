#ifndef CORELOGIC_H
#define CORELOGIC_H

#include <string>
#include <vector>

// =====================
// STRUCTS
// =====================

struct User {
    std::string username;
    std::string password;
};

struct Delivery {
    std::string trackingNumber;
    std::string senderName;
    std::string receiverName;
    std::string origin;
    std::string destination;
    std::string status;
    double distance;
};

// =====================
// CORE FUNCTIONS
// =====================

// CREATE
void createDelivery(std::vector<Delivery>& logistics);
// READ
void readDeliveries(const std::vector<Delivery>& logistics);

// UPDATE
void updateDeliveryStatus(std::vector<Delivery>& logistics);

// DELETE
void deleteDelivery(std::vector<Delivery>& logistics);

// SEARCH (linear search by tracking number)
void searchByTracking(const std::vector<Delivery>& logistics);

// SORT (bubble sort by status)
void sortByDistance(std::vector<Delivery>& logistics);

// =====================
// FILE HANDLING FUNCTIONS
// =====================

// LOAD FROM FILE (L) - reads logistics.csv and populates users and deliveries vectors on startup:
void loadFromFile(std::vector<User>& users, std::vector<Delivery>& deliveries);

// SAVE TO FILE (S) — writes all users and deliveries back to logistics.csv on exit:
void saveToFile(const std::vector<User>& users, const std::vector<Delivery>& deliveries);

// helper
int getStatusPriority(std::string status);

#endif