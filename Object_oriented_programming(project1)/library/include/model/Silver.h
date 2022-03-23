//
// Created by student on 18.05.2021.
//

#ifndef BANK_SILVER_H
#define BANK_SILVER_H

#include "AccountType.h"

class Silver : public AccountType {
public:
    Silver()=default;
    ~Silver()=default;
    double getMaxLoan() override;
    int getMaxDeposits() override;
    double getLoanBonus() override;
    double getDepositBonus() override;
    std::string getType() override;
};


#endif //BANK_SILVER_H
