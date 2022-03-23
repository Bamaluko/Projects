//
// Created by student on 06.04.2021.
//

#include "model/Address.h"
#include "model/AddressException.h"


Address::Address(const std::string &city, const std::string &street, const std::string &number) : city(city), street(street), number(number) {
    if (street.empty()) throw AddressException(AddressException::exceptionStreet); //konstruktor obiektu klasy Address. Przyjmuje niepuste napisy: "street, city, number
    if (number.empty()) throw AddressException(AddressException::exceptionNumber);
    if (city.empty()) throw AddressException(AddressException::exceptionCity);

}

Address::~Address() { //destruktor obiektów klasy Address

}

const std::string &Address::getCity() const{  //getter zwracający wartość pola city
    return city;
}

const std::string &Address::getStreet() const { //getter zwracający wartość pola street
    return street;
}

const std::string &Address::getNumber() const { //getter zwracający wartość pola number
    return number;
}

std::string Address::getAddress() {  //getter zwracający zbiórczo informację o wartości pól klasy dla danego obiektu
    return city + " " + street + " " + number;
}


void Address::setCity(const std::string &city1) {  //setter dla pola city. Przekazany jako parametr nie może być pusty (wówczas wyrzucony zostanie wyjątek)
    if(!city1.empty())
       Address::city = city1;
    else throw AddressException(AddressException::exceptionCity);
}

void Address::setStreet(const std::string &street1) { //setter dla pola street. Przekazany jako parametr nie może być pusty (wówczas wyrzucony zostanie wyjątek)
    if(!street1.empty())
        Address::street = street1;
    else throw AddressException(AddressException::exceptionStreet);
}

void Address::setNumber(const std::string &number1) { //setter dla pola number. Przekazany jako parametr nie może być pusty (wówczas wyrzucony zostanie wyjątek)
    if(!number1.empty())
       Address::number = number1;
    else throw AddressException(AddressException::exceptionNumber);
}

std::string Address::getInfo() {  //metoda pośrednicząca dla metody getAddressInfo
    return this->getAddress();
}
