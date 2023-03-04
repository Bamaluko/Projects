//
// Created by student on 18.05.2021.
//

#include <AddressException.h>
#include "model/Address.h"

Address::Address(const std::string &city, const std::string &street, const std::string &houseNumber,
                 const std::string &flatNumber) : city(city), street(street), houseNumber(houseNumber),
                                                  flatNumber(flatNumber) {
    if(city.empty()) throw AddressException(AddressException::exceptionCity);
    if(street.empty()) throw AddressException(AddressException::exceptionStreet);
    if(houseNumber.empty()) throw AddressException(AddressException::exceptionNumber);
}

const std::string &Address::getCity() const {
    return city;
}

const std::string &Address::getStreet() const {
    return street;
}

const std::string &Address::getHouseNumber() const {
    return houseNumber;
}

const std::string &Address::getFlatNumber() const {
    return flatNumber;
}

std::string Address::getAddressInfo() {
    return Address::getCity() + " " + Address::getStreet() + " " + Address::getHouseNumber() + " " + Address::getFlatNumber();
}



