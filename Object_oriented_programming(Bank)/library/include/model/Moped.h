//
// Created by student on 15.04.2021.
//

#ifndef WARSZTATY1_MOPED_H
#define WARSZTATY1_MOPED_H
#include "MotorVehicle.h"

class Moped : public MotorVehicle {
public:
    Moped( std::string registrationNumber ,int price, int capacity);
    virtual ~Moped();
    std::string getVehicleInfo() override;
    double getActualRentalPrice() override;
};


#endif //WARSZTATY1_MOPED_H
