#include <iostream>
#include "../../library/include/model/Client.h"
#include "../../library/include/repositories/StorageContainer.h"
#include <vector>
#include <boost/date_time.hpp>
#include "../../library/include/model/typedefs.h"
#include "../../library/include/model/ClientDefault.h"
#include "../../library/include/managers/ClientManager.h"
#include "../../library/include/managers/VehicleManager.h"
#include "../../library/include/managers/RentManager.h"
using namespace std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

int main()
{

    ClientTypePtr default1(new ClientDefault);
    AddressPtr address1=std::make_shared <Address>((std::string)"Wroclaw", (std::string)"Piekna", (std::string)"23");
    ClientPtr client1=std::make_shared <Client>((std::string)"Adam", (std::string)"Adamski", (std::string)"1435435435", address1, default1);
    std::cout<<client1->getClientinfo()<<std::endl;

    ClientPtr client2=std::make_shared <Client>((std::string)"Jan", (std::string)"Janowski", (std::string)"3435423465", address1, default1);
    std::cout<<client2->getClientinfo()<<std::endl;

    std::cout<<"--Uruchomienie setterow--"<<std::endl;
    //client1->setFirstName((std::string)"");
    client1->setLastName((std::string)"Adamowski");
    std::cout<<client1->getClientinfo()<<std::endl;

    std::cout<<"--Eksperyment z adresem--"<<std::endl;


    AddressPtr address2=std::make_shared <Address>((std::string)"Poznan", (std::string)"Brzydka", (std::string)"25");
    ClientPtr client3=std::make_shared <Client>((std::string)"Stefan", (std::string)"Stefanski", (std::string)"6456546435", address2, default1);
    client3->setAdres(address2);
    std::cout<<client3->getClientinfo()<<std::endl;

    VehiclePtr vehicle1=std::make_shared <Bicycle>("ESI563" , 9);
    VehiclePtr vehicle2=std::make_shared <Bicycle>("ESI463" , 10);
    RentPtr rent1=std::make_shared <Rent>(243 , client1 , vehicle1, boost::posix_time::not_a_date_time);
    RentPtr rent2=std::make_shared <Rent>(244 , client1 , vehicle2, boost::posix_time::not_a_date_time);
    std::cout << "--Proba wypisania pelnej informacji o kliencie-- " << std::endl;
//    std::cout << client1.getFullClientinfo() << std::endl;

    StorageContainer storage1;
    cout<<"--Test po czwartym warsztacie--"<<endl;
    cout<<storage1.getRentRep()->Raport()<<endl;
    cout<<storage1.getVehRep()->Raport()<<endl;
    cout<<storage1.getClientRep()->Raport()<<endl;
    storage1.getRentRep()->add(rent1);
    cout<<"Po dodaniu wypozyczenia"<<endl;
    cout<<storage1.getRentRep()->Raport()<<endl;
    cout<<storage1.getVehRep()->Raport()<<endl;
    cout<<storage1.getClientRep()->Raport()<<endl;

    RentPtr testrent1;
    RentPtr testrent2;
    RentPtr testrent3;
    VehiclePtr testvehicle1;
    VehiclePtr testvehicle2;
    VehiclePtr testvehicle3;
    ClientPtr testclient1;
    ClientManager *cmanager;
    RentManager *rmanager;
    VehicleManager *vmanager;
    AddressPtr testaddress1;
    RentRepoPtr rentrepo1;
    testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
    testvehicle2=std::make_shared <Car>((std::string)"ESI658",  15, 2000, B);
    rentrepo1 = std::make_shared<RentRepository>();
    cmanager = new ClientManager(storage1.getClientRep() );
    vmanager = new VehicleManager(storage1.getVehRep());
    rmanager = new RentManager(storage1.getRentRep(), rentrepo1);

    cmanager->registerClient((std::string)"Grzegorz","Floryda", (std::string)"2435435412", testaddress1, default1);
    vmanager->registerBike("EZW234", 10);
    rmanager->rentVehicle(103, cmanager->getClient("2435435412"),testvehicle2,boost::posix_time::not_a_date_time);


    return 0;
}
