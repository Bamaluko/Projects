//
// Created by student on 04.05.2021.
//

#ifndef WARSZTATY1_ADDRESSEXCEPTION_H
#define WARSZTATY1_ADDRESSEXCEPTION_H


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



#endif //WARSZTATY1_ADDRESSEXCEPTION_H
