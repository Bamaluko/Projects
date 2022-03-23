//
// Created by student on 28.05.2021.
//

#ifndef BANK_DEPOSITEXCEPTION_H
#define BANK_DEPOSITEXCEPTION_H


#include <stdexcept>

using namespace std;

class DepositException : public logic_error
{
public:
    explicit DepositException(const string&);
    static const string exceptionId;
    static const string exceptionNotADateTime;
    static const string exceptionBalance;
    static const string exceptionAccount;
    static const string exceptionPercentage;
};


#endif //BANK_DEPOSITEXCEPTION_H
