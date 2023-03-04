//
// Created by student on 26.04.2021.
//

#ifndef WARSZTATY1_CLIENTGOLD_H
#define WARSZTATY1_CLIENTGOLD_H
#include<iostream>
#include "ClientType.h"
#include "typedefs.h"

class ClientGold : public ClientType {
public:
    double applyDiscount(double price) override;
    int getMaxVehicles() override;
    std::string getTypeInfo() override;
};


#endif //WARSZTATY1_CLIENTGOLD_H
