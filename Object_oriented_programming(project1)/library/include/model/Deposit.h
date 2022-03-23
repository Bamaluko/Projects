//
// Created by student on 21.05.2021.
//

#ifndef BANK_DEPOSIT_H
#define BANK_DEPOSIT_H

#include "Service.h"

class Deposit : public Service
{
private:
    bool capitalization;
public:
    Deposit(const std::string &id, pt::ptime beginTime, double balance, const AccountPtr &account, double percentage, bool capitalization);
    ~Deposit() override = default;

    void depositMoney(double money, pt::ptime time);//Do metody bedzie trzeba dodac nowy parametr, czas wplaty na UML
    void endService(const pt::ptime &endTime) override;
    double getBonus(pt::ptime time);
    double getDepositBalance(pt::ptime time);//Nowa metoda, ktora na podstawie balance i czasu, ktory uplynal, policzy nam wlasciwy balance, ktory sie zmienia przy kapitalizacji
    std::string getInfo() const override;
    double getFinalBalance() const override;
    std::string getServiceType() override;
};

#endif //BANK_DEPOSIT_H
