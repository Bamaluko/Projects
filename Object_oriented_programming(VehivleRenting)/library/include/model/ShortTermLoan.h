//
// Created by student on 22.05.2021.
//

#ifndef BANK_SHORTTERMLOAN_H
#define BANK_SHORTTERMLOAN_H

#include "Loan.h"

class ShortTermLoan : public Loan
{
private:
    void endService(const pt::ptime &endTime) override;
public:
    ShortTermLoan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance,
                  const AccountPtr &account, double percentage);
    ~ShortTermLoan() override = default;
};

#endif //BANK_SHORTTERMLOAN_H
