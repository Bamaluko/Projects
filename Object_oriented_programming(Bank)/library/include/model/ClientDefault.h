//
// Created by student on 26.04.2021.
//

#ifndef WARSZTATY1_CLIENTDEFAULT_H
#define WARSZTATY1_CLIENTDEFAULT_H
#include<iostream>
#include "ClientType.h"

class ClientDefault : public ClientType {
public:
    ~ClientDefault() override;

    double applyDiscount(double price) override;
    int getMaxVehicles() override;
    std::string getTypeInfo() override;
};

#endif //WARSZTATY1_CLIENTDEFAULT_H
