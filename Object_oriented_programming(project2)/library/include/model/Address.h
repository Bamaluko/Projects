//
// Created by student on 06.04.2021.
//

#ifndef WARSZTATY1_ADDRESS_H
#define WARSZTATY1_ADDRESS_H
#include <string>

class Address {

private:
    std::string city;
    std::string street;
    std::string number;

public:

    Address(const std::string &city, const std::string &street, const std::string &number);
    ~Address();
    const std::string &getCity() const;
    const std::string &getStreet() const;
    const std::string &getNumber() const;
    std::string getAddress();

    void setCity(const std::string &city);
    void setStreet(const std::string &street);
    void setNumber(const std::string &number);
    std::string getInfo();

};


#endif //WARSZTATY1_ADDRESS_H
