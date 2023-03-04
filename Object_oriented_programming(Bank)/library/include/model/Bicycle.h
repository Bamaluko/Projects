//
// Created by student on 15.04.2021.
//

#ifndef WARSZTATY1_BICYCLE_H
#define WARSZTATY1_BICYCLE_H


#include "Vehicle.h"
#include <iostream>
#include <string>

class Bicycle : public Vehicle
{
public:
    Bicycle( std::string registrationNumber ,int price);
    virtual ~Bicycle();
    std::string getVehicleInfo() override;
    double getActualRentalPrice() override;
};


#endif //WARSZTATY1_BICYCLE_H
