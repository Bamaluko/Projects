//
// Created by student on 26.04.2021.
//

#ifndef WARSZTATY1_CLIENTSILVER_H
#define WARSZTATY1_CLIENTSILVER_H
#include<iostream>
#include "ClientType.h"

class ClientSilver : public ClientType {
public:
    double applyDiscount(double price) override;
    int getMaxVehicles() override;
    std::string getTypeInfo() override;
};


#endif //WARSZTATY1_CLIENTSILVER_H
