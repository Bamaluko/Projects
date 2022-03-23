//
// Created by student on 15.04.2021.
//

#include "model/Car.h"

Car::Car(std::string registrationNumber, int price, int capacity, SegmentType segment): MotorVehicle(registrationNumber, price, capacity ), segment(segment)  {
    //konstruktor, który oprócz parametrów klasy Vehicle, przyjmuje jeszcze parametr typu  int capacity oraz SegmentType (parametr i jego deklarację można znaleźć w nagłówku klasy Car)
}

std::string Car::getVehicleInfo() { //klasa wykorzystuje metodę obiektu macierzystego i dodaje do outputu informację o rodzaju pojazdu nadpisując jednocześnie metodę klasy Vehicle
    return "Car: " + MotorVehicle::getVehicleInfo() + " segment: " + Car::getSegment();
}

std::string Car::getSegment() {  //metoda zwraca napis informujący o segmencie samochodu
    return std::to_string(segment);
}

double Car::getActualRentalPrice() {  //oblicza właściwą cenę wypożyczenia pojazdu na podstawie typu pojazdu i zwraca ją (double). Wykorzystana zostanie tu metoda klasy MotorVehicle
    return segment*MotorVehicle::getActualRentalPrice()/10; //Ponadto doliczony zostanie mnożnik zależny od segmentu (wartości przypisane segmentom w nagłówku klasy Car)
}

Car::~Car() {

}
