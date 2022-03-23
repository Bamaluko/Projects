//
// Created by student on 28.05.2021.
//

#ifndef BANK_LONGTERMLOANEXCEPTION_H
#define BANK_LONGTERMLOANEXCEPTION_H

#include <stdexcept>

class LongTermLoanException : public std::logic_error
{
public:
    explicit LongTermLoanException(const std::string &arg);

    static const std::string exceptionId;
    static const std::string exceptionBeginTime;
    static const std::string exceptionAccount;
};

#endif //BANK_LONGTERMLOANEXCEPTION_H
