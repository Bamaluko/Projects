//
// Created by student on 21.05.2021.
//

#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <boost/date_time.hpp>
#include "typedefs.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Service
{
private:
    std::string id;
    pt::ptime beginTime;
    pt::ptime endTime = boost::posix_time::not_a_date_time;//wartosc domyslna dla end time, zostanie zmieniona w momencie zakonczenia pozyczki
    double balance;
    AccountPtr account;
    double percentage;

protected:
    void setBalance(double balance);
    void setPercentage(double percentage);
    void setEndTime(const pt::ptime &endTime);
    void setBeginTime(const pt::ptime &beginTime);//ustawianie beginTime jest potrzebne przy wplatach na depozyt, aby
    // nie naliczalo nam niewlasciwych odsetek, bonus bedzie wowczas zabrany na kont, a beginTime ustawiony na czas
    // wplaty na depozyt(tak, jak bysmy otworzyli nowy depozyt, tylko nie tracac starej kwoty na niego wplaconyej)

public:
    Service(const std::string &id, pt::ptime beginTime, double balance, const AccountPtr &account, double percentage);
    virtual ~Service() = default;
    double getBalance() const;
    double getPercentage() const;
    AccountPtr getAccount();
    virtual std::string getInfo() const = 0;
    virtual double getFinalBalance() const = 0;

    const std::string &getId() const;
    const pt::ptime &getBeginTime() const;
    const pt::ptime &getEndTime() const;
    virtual std::string getServiceType()=0;
    virtual void endService(const pt::ptime &endTime)=0;
};

#endif //BANK_SERVICE_H
