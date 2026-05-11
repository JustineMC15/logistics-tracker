#ifndef CORELOGIC_H
#define CORELOGIC_H

#include <string>
#include <vector>

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
    std::string status; // "Pending", "In Transit", "Delivered"
};

#endif