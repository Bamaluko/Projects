//
// Created by student on 18.05.2021.
//

#ifndef BANK_ADDRESS_H
#define BANK_ADDRESS_H


#include <string>

class Address {
private:
    std::string city;
    std::string street;
    std::string houseNumber;
    std::string flatNumber;

public:
    Address(const std::string &city, const std::string &street, const std::string &houseNumber,
            const std::string &flatNumber);
    virtual ~Address() = default;

    const std::string &getCity() const;
    const std::string &getStreet() const;
    const std::string &getHouseNumber() const;
    const std::string &getFlatNumber() const;
    std::string getAddressInfo();

};


#endif //BANK_ADDRESS_H
