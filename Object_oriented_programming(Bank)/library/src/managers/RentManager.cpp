//
// Created by student on 29.04.2021.
//

#include <model/ClientDefault.h>
#include <model/ClientBronze.h>
#include <model/ClientSilver.h>
#include <model/ClientGold.h>
#include <model/ClientPlatinum.h>
#include <model/ClientDiamond.h>
#include "managers/RentManager.h"

RentManager::RentManager(const RentRepoPtr &currentRents, const RentRepoPtr &archivedRents) : currentRents(
        currentRents), archivedRents(archivedRents) {} //kosntruktor przyjmujacy wektor obiektów Rent

RentManager::~RentManager() {

}

std::vector<RentPtr> RentManager::getAllClientRents(const ClientPtr& ptr) {  //metoda zwracająca wszystkie wypożecznia (w wektorze) klienta podanego w parametrze
    std::vector<RentPtr> vector = {};
    for(unsigned int i=0; i < this->currentRents->RepositorySize(); i++)
    {
        if(this->currentRents->get(i)->getClient() == ptr)
            vector.push_back(this->currentRents->get(i));
    }
    return vector;
}

RentPtr RentManager::getVehicleRent(VehiclePtr ptr) {  //metoda przyjmuje obiekt klasy Vehicle i zwraca (jeśli jest) wskaźnik na wypożyczenie z tym pojazdem, jeśli nie ma zwróci nullptr
    for(unsigned int i=0; i < this->currentRents->RepositorySize(); i++)
    {
        if(this->currentRents->get(i)->getVehicle() == ptr)
            return this->currentRents->get(i);
    }
    return nullptr;
}

std::vector<RentPtr> RentManager::findRents(RentPredicate predicate) {  //metoda wykorzystuje metode findAll repozytorium Rent by odnaleźć wybrane obiekty według predykatu i zwrócić je w wektorze
    return this->currentRents->findAll(predicate);
}

bool RentManager::rentIdValue100AndHigher(RentPtr rent) {  //przykładowy predykat
    return rent->getId()>=100;
}

bool RentManager::findAll(RentPtr) {  //predykat do wyszukiwania wszystkich obiektów
    return true;
}

double RentManager::checkClientRentBalance(ClientPtr ptr) { //metoda sprawdza ile za wszystkie wypożyczenia zapłacił dotąd klient
    std::vector<RentPtr> vector;
    for(unsigned int i=0; i < this->archivedRents->RepositorySize(); i++)
    {
        if(this->archivedRents->get(i)->getClient() == ptr)
            vector.push_back(this->archivedRents->get(i));
    }
    double balance=0;
    for(unsigned int i=0; i < vector.size(); i++ )
    {
        balance+=vector.at(i)->getRentCost();
    }
    return balance;
}

RentPtr RentManager::rentVehicle(int id, ClientPtr client, VehiclePtr vehicle, boost::posix_time::ptime beginTime) { //metoda tworzy nowe aktywne wypożyczenia przyjmując parametry dla konstruktora
    bool canCreate=true;                                       //rent pod warunkiem, że pojazd nie jest wypożyczony ani w archiwum. Ponadto klient musi mieć możliwosc wypożyczenia pojazdu
    if(client->isInArchive() || vehicle->isArchive())          //wynikającą z klasy mu przypisanej i taki pojazd musi być znany menadżerowi pojazdów
    {
        canCreate=false;
    }

    else if((unsigned int)client->getMaxVehicles()<=RentManager::getAllClientRents(client).size() || RentManager::getVehicleRent(vehicle)!=nullptr)
    {
        canCreate=false;

    }

    if(canCreate)
    {
        RentPtr rent = std::make_shared<Rent>(id, client, vehicle, beginTime);
        this->currentRents->add(rent);
        return rent;
    }
    else
        return nullptr;

}

void RentManager::returnVehicle(VehiclePtr ptr, boost::posix_time::ptime time) {  //metoda zwraca pojazd (końzcy wypożyczenie), archiwizuje wypożyczenie, i podlicza od razu balans
    if(RentManager::getVehicleRent(ptr)!=nullptr)   //klienta i ustawia jego status na tej podstawie (ClientType)
    {
        ClientPtr client =  RentManager::getVehicleRent(ptr)->getClient();
        RentManager::getVehicleRent(ptr)->endRent(time);
        archivedRents->add(RentManager::getVehicleRent(ptr));
        currentRents->remove(RentManager::getVehicleRent(ptr));
        RentManager::changeClientType(client);


    }

}

void RentManager::changeClientType(ClientPtr ptr) {             //zmienienie klasy klienta przy podliczaniu balansu na podstawie wysokości dokonanych dotychczas wpłat
    double balance = RentManager::checkClientRentBalance(ptr);
    ClientTypePtr clienttype;
    if(balance<=100)
        clienttype = ClientTypePtr (new ClientDefault);
    else if(balance<=200)
        clienttype = ClientTypePtr (new ClientBronze);
    else if(balance<=400)
        clienttype = ClientTypePtr (new ClientSilver);
    else if(balance<=800)
        clienttype = ClientTypePtr (new ClientGold);
    else if(balance<=1600)
        clienttype = ClientTypePtr (new ClientPlatinum);
    else
        clienttype = ClientTypePtr (new ClientDiamond);

    ptr->setClientType(clienttype);

}
