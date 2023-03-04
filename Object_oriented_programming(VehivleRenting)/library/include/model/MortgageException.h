//
// Created by student on 28.05.2021.
//

#ifndef BANK_MORTGAGEEXCEPTION_H
#define BANK_MORTGAGEEXCEPTION_H

#include <stdexcept>

class MortgageException : public std::logic_error
{
public:
    explicit MortgageException(const std::string&);
    static const std::string exceptionId;
    static const std::string exceptionBeginTime;
    static const std::string exceptionDeadline;
    static const std::string exceptionBalance;
    static const std::string exceptionPercentage;
    static const std::string exceptionAddress;
    static const std::string exceptionAccount;
};

#endif //BANK_MORTGAGEEXCEPTION_H
