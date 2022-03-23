//
// Created by student on 14.04.2021.
//

#ifndef WARSZTATY1_STORAGECONTAINER_H
#define WARSZTATY1_STORAGECONTAINER_H
#include <iostream>
#include <string>
#include "ClientRepository.h"
#include "RentRepository.h"
#include "VehicleRepository.h"

class StorageContainer {

private:
    ClientRepoPtr clientRep;
    RentRepoPtr rentRep;
    VehicleRepoPtr vehRep;


public:

    StorageContainer();
    virtual ~StorageContainer();

    ClientRepoPtr getClientRep();
    RentRepoPtr getRentRep();
    VehicleRepoPtr getVehRep();

};


#endif //WARSZTATY1_STORAGECONTAINER_H
