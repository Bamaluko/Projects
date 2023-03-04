//
// Created by student on 27.05.2021.
//

#ifndef BANK_ACCOUNTEXCEPTION_H
#define BANK_ACCOUNTEXCEPTION_H

#include <stdexcept>

class AccountException : public std::logic_error
{
public:
    explicit AccountException(const std::string&);
    static const std::string exceptionFirstName;
    static const std::string exceptionLastName;
    static const std::string exceptionPersonalID;
    static const std::string exceptionAddress;
    static const std::string exceptionSetBalance;
};


#endif //BANK_ACCOUNTEXCEPTION_H
