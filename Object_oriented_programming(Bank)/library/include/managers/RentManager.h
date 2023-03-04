//
// Created by student on 29.04.2021.
//

#ifndef WARSZTATY1_RENTMANAGER_H
#define WARSZTATY1_RENTMANAGER_H

#include "model/typedefs.h"

class RentManager {
    RentRepoPtr currentRents;
    RentRepoPtr archivedRents;

public:
    RentManager(const RentRepoPtr &currentRents, const RentRepoPtr &archivedRents);
    ~RentManager();

    std::vector<RentPtr> getAllClientRents(const ClientPtr&);
    RentPtr getVehicleRent(VehiclePtr);
    std::vector<RentPtr> findRents(RentPredicate);
    static bool rentIdValue100AndHigher(RentPtr);
    static bool findAll(RentPtr);
    double checkClientRentBalance(ClientPtr);
    RentPtr rentVehicle(int , ClientPtr , VehiclePtr , boost::posix_time::ptime);
    void returnVehicle(VehiclePtr, boost::posix_time::ptime);
    void changeClientType(ClientPtr);
};


#endif //WARSZTATY1_RENTMANAGER_H
