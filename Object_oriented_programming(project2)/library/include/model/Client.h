//
// Created by student on 21.03.2021.
//

#ifndef INTRODUCTIONPROJECT_CLIENT_H
#define INTRODUCTIONPROJECT_CLIENT_H
#include <string>
#include "model/Address.h"
#include "model/Rent.h"
#include <vector>
#include "model/typedefs.h"
#include "Client.h"
#include "ClientType.h"

class Rent;

class Client {

private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    AddressPtr address;
    ClientTypePtr clientType;
    bool archive = 0;
    //std::vector<RentPtr> currentRents;

public:

    Client(const std::string &firstName, const std::string &lastName, const std::string &personalId, AddressPtr address, ClientTypePtr clientType);
    ~Client();


    std::string  getClientinfo() const ;
    //std::string  getFullClientinfo() const;
    std::string const &getFirstName() const;
    std::string const &getLastName() const;
    std::string const &getPersonalID() const ;
    AddressPtr getAdres() const;
    //const std::vector<Rent *> &getCurrentRents() const;

    void setAdres(AddressPtr);
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    //void setCurrentRents(Rent *currentRents);
    //void removeRent(Rent *rent);

    int getMaxVehicles() const;
    double applyDiscount(double);
    void setClientType(ClientTypePtr);

    bool isInArchive() const;
    void setArchive(bool archive);
    std::string  getInfo() const ;
};


#endif //INTRODUCTIONPROJECT_CLIENT_H
