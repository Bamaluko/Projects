//
// Created by student on 28.05.2021.
//

#ifndef BANK_LONGTERMLOAN_H
#define BANK_LONGTERMLOAN_H

#include "Loan.h"

enum LongTermLoanType
{
    SHORT, // 10 years
    MEDIUM_SHORT, // 15 years
    MEDIUM, // 20 years
    LONG, // 25 years
    VERY_LONG // 30 years
};

class LongTermLoan : public Loan
{
private:
    LongTermLoanType longTermType;
    void endService(const pt::ptime &endTime) override;
public:
//    LongTermLoan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance,
//                 const AccountPtr &account, double percentage, LongTermLoanType longTermType);
    LongTermLoan(const std::string &id, const pt::ptime &beginTime, const AccountPtr &account,
                 LongTermLoanType longTermType);
    ~LongTermLoan() override = default;
};

#endif //BANK_LONGTERMLOAN_H
