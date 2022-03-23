//
// Created by student on 21.05.2021.
//

#include <Deposit.h>
#include "Account.h"
#include "DepositException.h"

Deposit::Deposit(const std::string &id, pt::ptime beginTime, double balance, const AccountPtr &account, double percentage, bool capitalization) :
        Service(id, beginTime, balance, account, percentage), capitalization(capitalization)
{
    if(id.empty()) throw DepositException(DepositException::exceptionId);
    if (beginTime==boost::posix_time::not_a_date_time) throw DepositException(DepositException::exceptionNotADateTime);
    if(balance<0) throw DepositException(DepositException::exceptionBalance);
    if(account == nullptr) throw DepositException(DepositException::exceptionAccount);
    if(percentage<0 || percentage>1) throw DepositException(DepositException::exceptionPercentage);

}

void Deposit::endService(const pt::ptime &endTime) {
    this->getDepositBalance(endTime);
    this->getBonus(endTime);
    this->getAccount()->putMoneyIn(this->getDepositBalance(endTime) + this->getBonus(endTime));
//    this->setBalance(0);
    this->setEndTime(endTime);
}

double Deposit::getBonus(pt::ptime time) {
    int days;
    boost::posix_time::time_period period(getBeginTime(), time);
    long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();
    days=(int)(secs/86400);
    double bonus=0;
    if(capitalization)
    {
        while(days>365)
        {
            days -= 365;
        }
        bonus = this->getDepositBalance(time)*(double)(days)/365*this->getPercentage();
    }
    else
    {
        while(days>365)
        {
            bonus += this->getBalance()*this->getPercentage();
            days -= 365;
        }
        bonus += (((double)(days)/365)*this->getPercentage()*this->getBalance());

    }
    bonus *=100;//kolejne trzy linijki to proces zaokraglania tak, aby otrzymac grosze
    bonus=round(bonus);
    bonus=bonus/100;
    return bonus;
}

double Deposit::getDepositBalance(pt::ptime time) {
    double deposit = this->getBalance();
    if(capitalization)
    {
        int days;
        boost::posix_time::time_period period(getBeginTime(), time);
        long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();
        days=(int)(secs/86400);
        while(days>365)
        {
            deposit += deposit*this->getPercentage();
            days -= 365;
        }
    }
        return deposit;
}

void Deposit::depositMoney(double money, pt::ptime time) {
    this->getAccount()->putMoneyIn(this->getBonus(time));
    this->setBalance(this->getBalance()+money);
    this->setBeginTime(time);
}

std::string Deposit::getInfo() const {
    return "DEPOZYT: " + this->getId() + " O BALANSIE: " + std::to_string(this->getBalance()) + " I OPROCENTOWANIU : " + std::to_string(this->getPercentage());
}

double Deposit::getFinalBalance() const {
    return getBalance();
}

std::string Deposit::getServiceType() {
    return "Deposit";
}




