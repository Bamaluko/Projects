//
// Created by student on 29.04.2021.
//

#include "managers/VehicleManager.h"
#include "model/Car.h"
#include "model/Moped.h"
#include "model/Bicycle.h"

VehicleManager::VehicleManager(const VehicleRepoPtr &currentVehicles) : currentVehicles(currentVehicles) { //konstruktor przyjmujący wektor pojazdów z repozytorium

}

VehicleManager::~VehicleManager() { //destruktor

}

VehiclePtr VehicleManager::getVehicle(std::string plateNumber) { //getter wykorzystujący metodę findByPlateNumber zwraca wskaźnik na pojazd z podanym plateNumber
    return this->currentVehicles->findByPlateNumber(plateNumber);
}

VehiclePtr VehicleManager::registerBike(std::string plateNumber, int basePrice) {  //Funkcja przyjmuje parametry dla konstruktora obiektu klasy Bike i tworzy ten obiekt, jeśli nie
    if(this->currentVehicles->findByPlateNumber(plateNumber) != nullptr)    //istnieje i zwraca wskaźnik na niego. Jeśli już istnieje obiekt z takim plateNumber, zwrócony zostaje wskaźnik na ten obiekt.
        return this->currentVehicles->findByPlateNumber(plateNumber);
    else
    {
        VehiclePtr vehicle = std::make_shared<Bicycle>(plateNumber, basePrice);
        currentVehicles->add(vehicle);
        return vehicle;
    }
}

VehiclePtr VehicleManager::registerMoped(std::string plateNumber, int basePrice, int capacity) { //Funkcja przyjmuje parametry dla konstruktora obiektu klasy Moped i tworzy ten obiekt, jeśli nie
    if(this->currentVehicles->findByPlateNumber(plateNumber) != nullptr)                        //istnieje i zwraca wskaźnik na niego. Jeśli już istnieje obiekt z takim plateNumber, zwrócony zostaje wskaźnik na ten obiekt.
        return this->currentVehicles->findByPlateNumber(plateNumber);
    else
    {
        VehiclePtr vehicle = std::make_shared<Moped>(plateNumber, basePrice, capacity);
        currentVehicles->add(vehicle);
        return vehicle;
    }
}

VehiclePtr VehicleManager::registerCar(std::string plateNumber, int basePrice, int capacity, SegmentType segment) { //Funkcja przyjmuje parametry dla konstruktora obiektu klasy Car i tworzy ten obiekt, jeśli nie
    if(this->currentVehicles->findByPlateNumber(plateNumber) != nullptr)                                            //istnieje i zwraca wskaźnik na niego. Jeśli już istnieje obiekt z takim plateNumber, zwrócony zostaje wskaźnik na ten obiekt.
        return this->currentVehicles->findByPlateNumber(plateNumber);
    else
    {
        VehiclePtr vehicle = std::make_shared<Car>(plateNumber, basePrice, capacity, segment);
        currentVehicles->add(vehicle);
        return vehicle;
    }
}

void VehicleManager::unregisterVehicle(std::string plateNumber) {  //funkcja ustawia pojazd na archiwalny, uniemożliwiając jego wypożyczenie
    if(this->getVehicle(plateNumber) != nullptr)
    {
        this->getVehicle(plateNumber)->setArchive(true);
    }
}

std::vector<VehiclePtr> VehicleManager::findVehicles(VehiclePredicate predicate) const {  //funkcja znajduje pojazdy wedłóg predykatu korzystając z metody repozytorium
    return this->currentVehicles->findAll(predicate);
}

bool VehicleManager::findAll(VehiclePtr ptr) {
    return (!ptr->isArchive());
}

bool VehicleManager::testVehicleRentalPrice10AndHigher(VehiclePtr ptr) {  //przykładowy predykat
    if(!ptr->isArchive())
        return ptr->getActualRentalPrice()>=10;
    else
        return false;
}


