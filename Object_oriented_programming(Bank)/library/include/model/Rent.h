//
// Created by student on 07.04.2021.
//

#ifndef WARSZTATY1_RENT_H
#define WARSZTATY1_RENT_H

#include <string>
#include "model/Vehicle.h"
#include "model/Client.h"
#include <boost/date_time.hpp>
#include "model/typedefs.h"

class Client;

class Rent {

private:
    int id;
    ClientPtr client;
    VehiclePtr vehicle;
    boost::posix_time::ptime beginTime;
    boost::posix_time::ptime endTime;
    double rentCost;

public:

    Rent(const int &id, ClientPtr client, VehiclePtr vehicle, boost::posix_time::ptime beginTime);
    ~Rent();

    int const &getId() const;
    ClientPtr getClient() const;
    VehiclePtr  getVehicle() const;
    std::string getRentInfo();

    const boost::posix_time::ptime &getBeginTime() const;
    const boost::posix_time::ptime &getEndTime() const;

    void endRent(const boost::posix_time::ptime &endTime);
    int getRentDays();
    double getRentCost();
    std::string getInfo();


};


#endif //WARSZTATY1_RENT_H
