//
// Created by student on 18.05.2021.
//

#ifndef BANK_BRONZE_H
#define BANK_BRONZE_H

#include "AccountType.h"

class Bronze : public AccountType {
public:
    Bronze()=default;
    ~Bronze()=default;
    double getMaxLoan() override;
    int getMaxDeposits() override;
    double getLoanBonus() override;
    double getDepositBonus() override;
    std::string getType() override;
};


#endif //BANK_BRONZE_H
