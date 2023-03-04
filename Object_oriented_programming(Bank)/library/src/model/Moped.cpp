//
// Created by student on 15.04.2021.
//

#include "model/Moped.h"

Moped::Moped(std::string registrationNumber, int price, int capacity):MotorVehicle(registrationNumber, price, capacity) { //konstruktor, który oprócz parametrów klasy Vehicle, przyjmuje
                                                                                                                          //jeszcze pole int capacity
}

std::string Moped::getVehicleInfo() { //klasa wykorzystuje metodę obiektu macierzystego i dodaje do outputu informację o rodzaju pojazdu nadpisując jednocześnie metodę klasy Vehicle
    return "Moped: " + MotorVehicle::getVehicleInfo();
}

double Moped::getActualRentalPrice() { //oblicza właściwą cenę wypożyczenia pojazdu na podstawie typu pojazdu i zwraca ją (double). Wykorzystana zostanie tu metoda klasy MotorVehicle
    return MotorVehicle::getActualRentalPrice();
}

Moped::~Moped() {

}
