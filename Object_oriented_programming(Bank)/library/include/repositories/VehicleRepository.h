//
// Created by student on 14.04.2021.
//

#ifndef WARSZTATY1_VEHICLEREPOSITORY_H
#define WARSZTATY1_VEHICLEREPOSITORY_H


#include <string>
#include <iostream>
#include <vector>
#include <model/typedefs.h>
#include "repositories/Repository.h"

class VehicleRepository : public Repository<Vehicle>
{

private:
    //std::vector<VehiclePtr> vehicleRepository{};
public:
    VehicleRepository();
    ~VehicleRepository();
    //void add(VehiclePtr);
    //void remove(VehiclePtr);
    //VehiclePtr get(unsigned int index);
    //std::string Raport() const;
    //int RepositorySize() const;
    static bool testVehiclePrise10OrHigher(VehiclePtr ptr);
    std::vector<VehiclePtr> findAll(VehiclePredicate predicate);
    VehiclePtr findByPlateNumber(std::string);
};

#endif //WARSZTATY1_VEHICLEREPOSITORY_H
