//
// Created by student on 15.04.2021.
//

#include "model/MotorVehicle.h"

MotorVehicle::MotorVehicle(std::string registrationNumber, int price, int engineDisplacement) //konstruktor objektów. Oprócz pól uwzględnionych w klasie macierzystej mamy tu jeszcze
        : Vehicle(registrationNumber, price ), engineDisplacement(engineDisplacement){        // pole integer engineDisplacement
}

MotorVehicle::~MotorVehicle(){  //destruktor klasy (czysto wirtualny)
}

int MotorVehicle::getEngineDisplacement() //metoda zwraca wartość pola engineDisplacement obiektu
{
    return engineDisplacement;
}

std::string MotorVehicle::getVehicleInfo()  //metoda korzysta z metody klasy macierzystej getVehicleInfo i dodaje do niej informację o wartości engineDisplacement
{
    return Vehicle::getVehicleInfo() + ". Engine displacement: " + std::to_string(engineDisplacement);
}

double MotorVehicle::getActualRentalPrice() {  //metoda zwracająca właściwą cenę wypożyczenia pojazdu typu double po uwzględnieniu mnożnika naliczanego na podstawie wartości pola engineDisplacement
    double value;
    if(this->getEngineDisplacement() <= 1000)
        value = Vehicle::BasePrice();
    else if(this->getEngineDisplacement()<=2000)
        value = Vehicle::BasePrice()*(1+0.5*(this->getEngineDisplacement()-1000)/1000);
    else
        value = Vehicle::BasePrice()*1.5;

    return value;
}



