//
// Created by student on 14.04.2021.
//

#include "repositories/StorageContainer.h"
#include "model/Client.h"
#include "model/Vehicle.h"
#include "model/Address.h"
#include "model/Rent.h"
#include "model/Bicycle.h"
#include "model/typedefs.h"
#include "model/ClientDefault.h"

StorageContainer::StorageContainer(){  //klasa pomocnicza tworząca zbiór repozytoriów do testów. Nie jest istotna z punktu widzenia dzialania programu
    //AddressPtr testaddress1;
    //ClientPtr  testclient1;
    //VehiclePtr testvehicle1;
    //RentPtr testrent1;
    int testid = 1;
    AddressPtr testaddress1=std::make_shared <Address>("Wroclaw", "Piekna", "23");
    ClientTypePtr defaultclient(new ClientDefault);
    ClientPtr testclient1=std::make_shared <Client>((std::string)"Adam", (std::string)"Adamski", (std::string)"1435435435", testaddress1, defaultclient);
    VehiclePtr testvehicle1=std::make_shared <Bicycle>((std::string)"EPD237",  10);
    RentPtr testrent1=std::make_shared <Rent>(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
    ClientRepoPtr clientrepo = std::make_shared<ClientRepository>();
    RentRepoPtr rentrepo = std::make_shared<RentRepository>();
    VehicleRepoPtr vehiclerepo = std::make_shared<VehicleRepository>();
    vehiclerepo->add(testvehicle1);
    clientrepo->add(testclient1);
    rentrepo->add(testrent1);
    vehRep=vehiclerepo;
    rentRep=rentrepo;
    clientRep=clientrepo;

}

StorageContainer::~StorageContainer() {

}

ClientRepoPtr StorageContainer::getClientRep() {
    return clientRep;
}

RentRepoPtr StorageContainer::getRentRep(){
    return rentRep;
}

VehicleRepoPtr StorageContainer::getVehRep() {
    return vehRep;
}
