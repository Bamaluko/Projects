//
// Created by student on 28.05.2021.
//

#ifndef BANK_MORTGAGE_H
#define BANK_MORTGAGE_H

#include "Loan.h"

class Mortgage : public Loan
{
private:
    AddressPtr houseAddress; // Adres domu na który wzięta jest hipoteka
    void endService(const pt::ptime &endTime) override;
public:
    Mortgage(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance,
             const AccountPtr &account, double percentage, const AddressPtr &houseAddress);
    ~Mortgage() override = default;

    const AddressPtr &getHouseAddress() const;
};

#endif //BANK_MORTGAGE_H
