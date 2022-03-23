//
// Created by student on 15.04.2021.
//

#include "model/Bicycle.h"

Bicycle::Bicycle(std::string registrationNumber, int price )  //konstruktor nadpisujący konstruktor klasy Vehicle. Jest analogiczny do konstruktora klasy z której pochodzi klasa Bicycle
        : Vehicle(registrationNumber, price ){
}

std::string Bicycle::getVehicleInfo()   //klasa wykorzystuje metodę obiektu macierzystego i dodaje do outputu informację o rodzaju pojazdu nadpisując jednocześnie metodę klasy Vehicle
{
    return "BICYCLE: " + Vehicle::getVehicleInfo();
}

double Bicycle::getActualRentalPrice()  //oblicza właściwą cenę wypożyczenia pojazdu na podstawie typu pojazdu i zwraca ją (double)
{
    return Vehicle::BasePrice();
}

Bicycle::~Bicycle() = default;
