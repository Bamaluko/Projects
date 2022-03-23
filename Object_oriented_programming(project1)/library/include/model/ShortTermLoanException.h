//
// Created by student on 28.05.2021.
//

#ifndef BANK_SHORTTERMLOANEXCEPTION_H
#define BANK_SHORTTERMLOANEXCEPTION_H

#include <stdexcept>

class ShortTermLoanException : public std::logic_error
{
public:
    explicit ShortTermLoanException(const std::string&);
    static const std::string exceptionId;
    static const std::string exceptionBeginTime;
    static const std::string exceptionDeadline;
    static const std::string exceptionBalance;
    static const std::string exceptionPercentage;
    static const std::string exceptionAccount;
    static const std::string exceptionTooLongPeriod;
};

#endif //BANK_SHORTTERMLOANEXCEPTION_H
