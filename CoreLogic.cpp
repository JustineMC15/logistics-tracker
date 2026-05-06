#ifndef CORELOGIC_H
#define CORELOGIC_H

#include <string>
#include <vector>

struct User {
    std::string username;
    std::string password;
    std::vector<int> cart; // stores trackingNumbers or package IDs
};

struct Delivery {
    std::string trackingNumber;
    std::string senderName;
    std::string receiverName;
    std::string origin;
    std::string destination;
    std::string status; // "In Cart", "Processing", "In Transit", "Delivered"
};

#endif