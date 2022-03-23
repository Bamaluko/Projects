//
// Created by student on 15.04.2021.
//

#ifndef WARSZTATY1_MOTORVEHICLE_H
#define WARSZTATY1_MOTORVEHICLE_H
#include <iostream>
#include <string>
#include "Vehicle.h"

class MotorVehicle : public Vehicle
{
private:
    int engineDisplacement;
public:
    MotorVehicle(std::string registrationNumber, int price, int engineDisplacement);
    virtual ~MotorVehicle()=0 ;
    int getEngineDisplacement();
    std::string getVehicleInfo() override;

    double getActualRentalPrice() override;
};


#endif //WARSZTATY1_MOTORVEHICLE_H
