//
// Created by student on 26.04.2021.
//

#ifndef WARSZTATY1_CLIENTPLATINUM_H
#define WARSZTATY1_CLIENTPLATINUM_H

#include<iostream>
#include "ClientType.h"
#include "typedefs.h"

class ClientPlatinum : public ClientType {
public:
    double applyDiscount(double price) override;
    int getMaxVehicles() override;
    std::string getTypeInfo() override;
};


#endif //WARSZTATY1_CLIENTPLATINUM_H
