//
// Created by student on 18.05.2021.
//

#ifndef BANK_GOLD_H
#define BANK_GOLD_H

#include "AccountType.h"

class Gold : public AccountType {
public:
    Gold()=default;
    ~Gold()=default;
    double getMaxLoan() override;
    int getMaxDeposits() override;
    double getLoanBonus() override;
    double getDepositBonus() override;
    std::string getType() override;
};


#endif //BANK_GOLD_H
