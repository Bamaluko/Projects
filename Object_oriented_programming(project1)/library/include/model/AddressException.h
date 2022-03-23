//
// Created by student on 27.05.2021.
//

#ifndef BANK_ADDRESSEXCEPTION_H
#define BANK_ADDRESSEXCEPTION_H


#include <stdexcept>

using namespace std;

class AddressException : public logic_error
{
public:
    explicit AddressException(const string&);
    static const string exceptionStreet;
    static const string exceptionNumber;
    static const string exceptionCity;
};


#endif //BANK_ADDRESSEXCEPTION_H
