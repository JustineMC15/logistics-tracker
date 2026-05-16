#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "CoreLogic.h"
#include <vector>

// =====================
// FILE HANDLING FUNCTIONS
// =====================

// LOAD FROM FILE (L) - reads logistics.csv and populates users and deliveries vectors on startup
void loadFromFile(std::vector<User>& users, std::vector<Delivery>& deliveries);

// SAVE TO FILE (S) - writes all users and deliveries back to logistics.csv on exit
void saveToFile(const std::vector<User>& users, const std::vector<Delivery>& deliveries);

#endif 