//
// Created by student on 07.04.2021.
//

#include "model/Vehicle.h"
#include "model/VehicleException.h"

Vehicle::Vehicle(const std::string &plateNumber, const int &basePrice) : plateNumber(plateNumber), basePrice(basePrice) {  //konstruktor dla obiektów klasy vehicle. Jest on ndapisywany
    if(basePrice<0)                                                                                                        //przez konstruktoey obiektów klas pochodnych (Bike, Car, Moped)
        throw VehicleException(VehicleException::exceptionPrice);                                //Polami wspólnymi wszystkich obiektów potomnych klasy Vehicle są napis plateNumber
    if(plateNumber.empty())                                                                      //oraz liczba int basePrice
        throw VehicleException(VehicleException::exceptionPlateNumber);

}

Vehicle::~Vehicle() = default;

const std::string &Vehicle::getPlateNumber() const {  //getter zwracający wartość pola plateNumber (napis)
    return plateNumber;
}

const int &Vehicle::BasePrice() const {  //getter zwracający wartość pola basePrice (int)
    return basePrice;
}

void Vehicle::setPlateNumber(const std::string &plateNumber1) {   //setter dla plateNumber. Podanie pustego napisu poskutkuje wyjątkiem
    if(plateNumber1.empty())
        throw VehicleException(VehicleException::exceptionPlateNumber);
    Vehicle::plateNumber = plateNumber1;
}

void Vehicle::setBasePrice(const int &basePrice1) {  //setter dla basePrice. Podanie wartości niedodatniej poskutkuje wyjątkiem
    if(basePrice1 <= 0)
        throw VehicleException(VehicleException::exceptionPrice);
    Vehicle::basePrice = basePrice1;
}

std::string Vehicle::getVehicleInfo() {
    return plateNumber + " " + std::to_string(basePrice) + " " ;// metoda zwraca napis zbiorowo informujący o wartościach pól klasy vehicle
}

bool Vehicle::isArchive() const {  //Metoda zwraca wartosć bool informującą o tym, czy obiekt jest archiwizowany
    return archive;
}

void Vehicle::setArchive(bool archive1) {  //metoda wykorzystywana pośrednio przez managera do przenoszenia obiektu do/z archiwum
    Vehicle::archive = archive1;
}

std::string Vehicle::getInfo() {  //funkcja pośrednicząca dla metody getVehicleInfo
    return this->getVehicleInfo();
}


//const std::string Vehicle::isRented() const {
//    if(rented)
//        return "RENTED";
//    else
//        return "AVAILABLE";
//}

//void Vehicle::setRented(bool rent) {
//    if (rent)
//        Vehicle::rented = true;
//    else
//        Vehicle::rented = false;
//}




