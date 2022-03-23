//
// Created by student on 18.05.2021.
//

#ifndef BANK_ACCOUNTTYPE_H
#define BANK_ACCOUNTTYPE_H


#include <string>

class AccountType {
public:
    virtual ~AccountType() = default;
    virtual double getMaxLoan()=0;
    virtual int getMaxDeposits()=0;
    virtual double getLoanBonus()=0;
    virtual double getDepositBonus()=0;
    virtual std::string getType()=0;
};


#endif //BANK_ACCOUNTTYPE_H
