//
// Created by student on 21.03.2021.
//

#include "model/Client.h"
#include "model/ClientException.h"
#include <iostream>
#include "model/Address.h"
#include "model/Rent.h"
#include "model/ClientType.h"
#include "model/ClientDefault.h"
#include <vector>


Client::~Client() {
}

std::string  Client::getClientinfo() const { //metoda zwraca napis zawierający informacje o atrybutach obiektu
    return firstName + " " + lastName + " " + personalID + " " + address->getAddress() + " " + clientType->getTypeInfo() + " Max vehicles: " +
    std::to_string(Client::getMaxVehicles());
 }

std::string const &Client::getFirstName() const { //metoda zwraca atrybut firstName obiektu
    return firstName;
}

std::string const &Client::getLastName() const { //metoda zwraca atrybut lastName obiektu
    return lastName;
}

std::string const &Client::getPersonalID() const { //metoda zwraca atrybut personalID obiektu
    return personalID;
}

AddressPtr Client::getAdres() const  {
    return address;
}

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalId1, AddressPtr address, ClientTypePtr clientType)  : firstName(
        firstName), lastName(lastName), personalID(personalId1), address(address), clientType(clientType), archive(false) {
    if (firstName.empty()) throw ClientException(ClientException::exceptionFirstName);
    if (lastName.empty()) throw ClientException(ClientException::exceptionLastName);
    if (personalId1.empty()) throw ClientException(ClientException::exceptionPersonalID);                     //konstruktor dla obiektu klasy Client. Sprawdza jednocześnie, czy
    if (address == nullptr) throw ClientException(ClientException::exceptionAddress);                         //poadne dane są poprawne, jeśli nie, to wyrzuca wyjątek. Parametry to
    if (clientType == nullptr) throw ClientException(ClientException::exceptionClientType);                   // niepusty napis firstName, lastName, personalID, wskaźnik wspóldzielony
}                                                                                                             // na obiekt klasy Address, klasy clientType


void Client::setFirstName(const std::string &firstName1) {
    if (firstName1.empty()) throw ClientException(ClientException::exceptionFirstName);   //setter firstName. Nie można ustawić firstName na pusty napis (wyrzucony zostanie wyjątek)
    Client::firstName = firstName1;
}

void Client::setLastName(const std::string &lastName1) {
    if (lastName1.empty()) throw ClientException(ClientException::exceptionLastName);    //setter lastName. Nie można ustawić lastName na pusty napis (wyrzucony zostanie wyjątek)
    Client::lastName = lastName1;
}

void Client::setAdres(AddressPtr address1) {
    if (address1 == nullptr) throw ClientException(ClientException::exceptionAddress);   //setter Address. Nie można ustawić Address na nullptr (wyrzucony zostanie wyjątek)
    Client::address = address1;
}

int Client::getMaxVehicles() const {        //metoda zwraca liczbę maksymalnych pojazdów, które może wypozyczyć klient. Informacje są pobierane z klasy ClientType przypisanej klientowi
    return clientType->getMaxVehicles();
}

double Client::applyDiscount(double discount)  //metoda zwraca zniżkę,która obliczana jest w metodzie odpowiadającej klientowi klasy ClientType
{
    return clientType->applyDiscount(discount);
}

void Client::setClientType(ClientTypePtr clientType1) {   //ustawienie typu klienta, proces zautomatyzowany, metoda wywoływana bezpośrednio tylko w ramach testów
    Client::clientType = clientType1;
}

bool Client::isInArchive() const {  //metoda zwróci wartość pola isArchive
    return archive;
}

void Client::setArchive(bool archive1) {  //metoda zmienia stan klienta (zarchiwizowany/niezarchiwizowany). Metoda wykorzystywana pośredni przez managera
    Client::archive = archive1;
}


std::string Client::getInfo() const {  //metoda pośrednizcąca dla metody getClientInfo
    return this->getClientinfo();
}




//const std::vector<Rent *> &Client::getCurrentRents() const {
//    return currentRents;
//}
//
//void Client::setCurrentRents(Rent *currentRents) {
//    Client::currentRents.push_back(currentRents);
//}

//std::string Client::getFullClientinfo() const {
//    std::string string;
//    string=this->getClientinfo() + " | Rent IDs:";
//    for (unsigned int i = 0; i < currentRents.size(); i++)
//    {
//        string += " " + std::to_string(currentRents.at(i)->getId());
//    }
//    return  string;
//}

//void Client::removeRent(Rent *rent) {
//    for (unsigned int i = 0; i < currentRents.size(); i++)
//    {
//        if(currentRents.at(i) == rent)
//        {
//            currentRents.erase(currentRents.begin() + i);
//        }
//    }
//
//}











