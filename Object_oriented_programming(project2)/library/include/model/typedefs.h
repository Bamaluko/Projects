//
// Created by student on 14.04.2021.
//

//#ifndef WARSZTATY1_TYPEDEFS_H
//#define WARSZTATY1_TYPEDEFS_H
#include "Rent.h"
#include "Client.h"
#include "Address.h"
#include "Vehicle.h"
#include "Moped.h"
#include "Bicycle.h"
#include "Car.h"
#include "ClientType.h"
#include "repositories/ClientRepository.h"
#include "repositories/VehicleRepository.h"
#include "repositories/RentRepository.h"
#include <memory>
#include<functional>

class Client;
class Address;
class Rent;
class Vehicle;
class ClientType;
class ClientRepository;
class VehicleRepository;
class RentRepository;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;

typedef std::shared_ptr<ClientType> ClientTypePtr;

typedef std::shared_ptr<ClientRepository> ClientRepoPtr;
typedef std::shared_ptr<VehicleRepository> VehicleRepoPtr;
typedef std::shared_ptr<RentRepository> RentRepoPtr;


//typedef Client *ClientPtr;
//typedef Address *AddressPtr;
//typedef Rent *RentPtr;
//typedef Vehicle *VehiclePtr;

//typedef bool (*ClientPredicate)(ClientPtr);
//typedef bool (*RentPredicate)(RentPtr);
//typedef bool (*VehiclePredicate)(VehiclePtr);
typedef std::function<bool(RentPtr)> RentPredicate;
typedef std::function<bool(VehiclePtr)> VehiclePredicate;
typedef std::function<bool(ClientPtr)> ClientPredicate;
//#endif //WARSZTATY1_TYPEDEFS_H
