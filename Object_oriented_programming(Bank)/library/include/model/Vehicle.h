//
// Created by student on 07.04.2021.
//

#ifndef WARSZTATY1_VEHICLE_H
#define WARSZTATY1_VEHICLE_H

#include <iostream>

class Vehicle {
private:
    std::string plateNumber;
    int basePrice;
    bool rented = false;
    bool archive = false;

public:

    Vehicle(const std::string &plateNumber, const int &basePrice);
    virtual ~Vehicle()=0;
    virtual double getActualRentalPrice()=0;

    const std::string &getPlateNumber() const;
    const int &BasePrice() const;
    //const std::string isRented() const;

    virtual std::string getVehicleInfo();

    void setPlateNumber(const std::string &plateNumber);
    void setBasePrice(const int &basePrice);

    bool isArchive() const;
    void setArchive(bool archive);
    std::string getInfo();

    //void setRented(bool rent);

};


#endif //WARSZTATY1_VEHICLE_H
