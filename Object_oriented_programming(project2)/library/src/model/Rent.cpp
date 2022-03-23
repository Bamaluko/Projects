//
// Created by student on 07.04.2021.
//

#include "model/Rent.h"
#include "model/Vehicle.h"
#include "model/Client.h"
#include <vector>
#include <boost/date_time.hpp>
#include "model/typedefs.h"
#include "model/RentException.h"

Rent::Rent(const int &id, ClientPtr client, VehiclePtr vehicle, boost::posix_time::ptime beginTime) : id(id), client(client), vehicle(vehicle), beginTime(beginTime) {

//    Rent::client->setCurrentRents(this);
//    this->getVehicle()->setRented(1);
    if(client == nullptr)
        throw RentException(RentException::exceptionClientNullPtr);   //konstruktor klasy Rent. Przyjmuje jako parametry wskaźniki współdzielone na obiekty typu client, vehicle, integer id,
    if(vehicle == nullptr)                                            //czas wypożyczenia typu boost::posix_time::ptime. Wskaźniki nie mogą być puste, a id mniejsze od 0. Jeśli jako czas
        throw RentException(RentException::exceptionVehicleNullPtr);  //przekazany zostanie boost::posix_time::not_a_date_time to ustawi się zcas na czas aktualny
    rentCost=0;
    if(id<0)
        throw RentException(RentException::exceptionID);
    if(beginTime == boost::posix_time::not_a_date_time)
        this->beginTime = boost::posix_time::second_clock::local_time();
    else
        this->beginTime = beginTime;
}

Rent::~Rent() {

}

const int &Rent::getId() const { //getter zwracający wartość pola id
    return id;
}

ClientPtr Rent::getClient() const {  //getter zwracający wartość pola client (wskaźnik na obiekt)
    return client;
}

VehiclePtr Rent::getVehicle() const { //getter zwracający wartość pola vehicle (wskaźnik na obiekt)
    return vehicle;
}

std::string Rent::getRentInfo() {  //metoda zwróci napis zawierający informacje o wszystkich polach obiektu Rent. Wykorzystane są także informacje o polach przypisanyc obiektów vehicle i client
    std::stringstream ss;
    std::stringstream sss;
    ss << this->getBeginTime();
    sss <<this->getEndTime();
    std::string s1 = ss.str();
    std::string s2 = sss.str();

    return std::to_string(id) + " " + client->getClientinfo() + " " + vehicle->getVehicleInfo() + " " + s1 + " " + s2;
}

const boost::posix_time::ptime &Rent::getBeginTime() const {  //getter zwracający czas rozpoczęcia wypożyczenia
    return beginTime;
}

const boost::posix_time::ptime &Rent::getEndTime() const { //getter zwracający czas zakończenia wypożyczenia
    return endTime;
}

void Rent::endRent(const boost::posix_time::ptime &endTime1) { //metoda kończąca wypożyczenie. Przyjmuje podany czas zakończenia wypożyczenia. Jeśli parametr to boost::posix_time::not_a_date_time
    if (endTime1 == boost::posix_time::not_a_date_time) {      //to ustawiony zostanie czas aktualny. W przeciwnym wypadku ustawiany jest czas podany w parametrze, chyba, że jest on wcześniejszy niż
        if (this->endTime == boost::posix_time::not_a_date_time) {   //czas beginTime. Wówczas to on jest ustawiany na endTime
            this->endTime = boost::posix_time::second_clock::local_time();
        }
    }
    else{
        boost::posix_time::time_period period(this->getBeginTime(), this->getEndTime());
        if (this->endTime == boost::posix_time::not_a_date_time) {
            if (endTime1 >= this->getBeginTime())
                this->endTime = endTime1;
            else
                this->endTime = beginTime;
        }
    }
    if(getRentDays()>0)
    {
        rentCost=(getRentDays()*this->getVehicle()->getActualRentalPrice()) - (this->getClient()->applyDiscount(this->getVehicle()->getActualRentalPrice()*this->getRentDays()));
    }  //następnie na podstawie metody getDays zwraca się czas trwania wypożyczenia, na podstawie którego oblicza się cenę korzystając z metod współpracujaćych klas

    else  //chyba, że ilość dni wynosi 0. Wówczas wypożyczenie jest anulowane
        rentCost=0;


//    vehicle->setRented(0);
//    client->removeRent(this);
}

int Rent::getRentDays() {  //metoda zlicza liczbę sekund, która upłunęła od rozpoczęcia do zakończenia wypożyczenia i przelicza ją na ilość dnii. Każdy dzień jest naliczany co 24h
    int days;
    boost::posix_time::time_period period(this->getBeginTime(), this->getEndTime());  //pierwszy dzień jest naliczany juz od upłynięcia minuty od wypożyczenia
    long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();  //do tego czasu można anulować wypożyczenie bez kosztów
    if(this->endTime == boost::posix_time::not_a_date_time)
        days=0;
    else if(secs <= 60)
        days=0;

    else {
        days=(int)(secs/(86400)+1);
    }
    return days;

}

double Rent::getRentCost() {  //getter zwraca wartość obliczonego w metodzie endRent kosztu wypożyczenia
    return rentCost;
}

std::string Rent::getInfo() {  //metoda pośrednicząca dla metody getRentInfo
    return this->getRentInfo();
}














