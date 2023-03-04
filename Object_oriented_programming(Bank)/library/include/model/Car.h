//
// Created by student on 15.04.2021.
//

#ifndef WARSZTATY1_CAR_H
#define WARSZTATY1_CAR_H


#include "Vehicle.h"
#include "MotorVehicle.h"
#include <iostream>
#include <string>

enum SegmentType {A=10, B=11, C=12, D=13, E=15};

class Car :  public MotorVehicle
{
private:
    SegmentType segment;
public:
    Car( std::string registrationNumber ,int price, int capacity, SegmentType segment);
    virtual ~Car();
    std::string getVehicleInfo() override;
    std::string getSegment();
    double getActualRentalPrice() override;
};



#endif //WARSZTATY1_CAR_H
