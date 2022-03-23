//
// Created by student on 28.05.2021.
//

#include "Mortgage.h"
#include "MortgageException.h"

Mortgage::Mortgage(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance,
                   const AccountPtr &account, double percentage, const AddressPtr &houseAddress) :
        Loan(id, beginTime, deadline, balance, account, percentage), houseAddress(houseAddress)
{
    if(id.empty()) throw MortgageException(MortgageException::exceptionId);
    if(beginTime == pt::not_a_date_time) throw MortgageException(MortgageException::exceptionBeginTime);
    if( (beginTime >= deadline) || (deadline == pt::not_a_date_time)) throw MortgageException(MortgageException::exceptionDeadline);
    if(balance <= 0) throw MortgageException(MortgageException::exceptionBalance);
    if( (percentage < 0) || (percentage > 1) ) throw MortgageException(MortgageException::exceptionPercentage);
    if(houseAddress == nullptr) throw MortgageException(MortgageException::exceptionAddress);
    if(account == nullptr) throw MortgageException(MortgageException::exceptionAccount);
    this->setBalance(balance + balance*percentage);
}

const AddressPtr &Mortgage::getHouseAddress() const
{
    return houseAddress;
}

void Mortgage::endService(const pt::ptime &endTime)
{
    if(endTime<=this->getDeadline())
        this->setEndTime(endTime);
    else
    {
        int days;
        pt::time_period period(getDeadline(), endTime);
        long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();
        days=(int)(secs/86400);
        this->setBalance(days*20);
        this->setDeadline(endTime + boost::posix_time::hours(720));
    }
}
