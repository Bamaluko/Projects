//
// Created by student on 29.04.2021.
//

#ifndef WARSZTATY1_VEHICLEMANAGER_H
#define WARSZTATY1_VEHICLEMANAGER_H


#include "model/typedefs.h"
#include "repositories/VehicleRepository.h"
#include <vector>
#include <iostream>

class VehicleManager{
    VehicleRepoPtr currentVehicles;
public:
    VehicleManager(const VehicleRepoPtr &currentVehicles);
    ~VehicleManager();
    VehiclePtr getVehicle(std::string);
    VehiclePtr registerBike (std::string, int);
    VehiclePtr registerMoped (std::string, int, int);
    VehiclePtr registerCar (std::string, int, int, SegmentType);
    void unregisterVehicle(std::string);
    std::vector<VehiclePtr> findVehicles(VehiclePredicate) const;
    static bool findAll(VehiclePtr);
    static bool testVehicleRentalPrice10AndHigher(VehiclePtr);

};


#endif //WARSZTATY1_VEHICLEMANAGER_H
