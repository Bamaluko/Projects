//
// Created by student on 28.05.2021.
//

#include "LongTermLoan.h"
#include "LongTermLoanException.h"

LongTermLoan::LongTermLoan(const std::string &id, const pt::ptime &beginTime, const AccountPtr &account,
                           LongTermLoanType longTermType)
                           : Loan(id, beginTime, pt::not_a_date_time, 0, account, 0), longTermType(longTermType)
{
    if(id.empty()) throw LongTermLoanException(LongTermLoanException::exceptionId);
    if(beginTime == pt::not_a_date_time) throw LongTermLoanException(LongTermLoanException::exceptionBeginTime);
    if(account == nullptr) throw LongTermLoanException(LongTermLoanException::exceptionAccount);
    double balance = 0;
    double percentage = 0;
    pt::ptime deadline = pt::not_a_date_time;
    if(longTermType == SHORT)
    {
        percentage = 0.07;
        balance = 100000 + 100000*0.07;
        deadline = beginTime + gr::years(10);
    }
    else if(longTermType == MEDIUM_SHORT)
    {
        percentage = 0.055;
        balance = 200000 + 200000*0.055;
        deadline = beginTime + gr::years(15);
    }
    else if(longTermType == MEDIUM)
    {
        percentage = 0.042;
        balance = 350000 + 350000 * 0.042;
        deadline = beginTime + gr::years(20);
    }
    else if(longTermType == LONG)
    {
        percentage = 0.037;
        balance = 600000 + 600000 * 0.037;
        deadline = beginTime + gr::years(25);
    }
    else if(longTermType == VERY_LONG)
    {
        percentage = 0.03;
        balance = 900000 + 900000 * 0.03;
        deadline = beginTime + gr::years(30);
    }
    this->setBalance(balance);
    this->setPercentage(percentage);
    this->setDeadline(deadline);
}

void LongTermLoan::endService(const pt::ptime &endTime)
{
    if(this->getDeadline() >= endTime)
    {
        this->setEndTime(endTime);

    }
    else
    {
        long days;
        pt::time_period period(getDeadline(), endTime);
        long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();
        days=(int)(secs/86400);
        if(longTermType == SHORT)
        {
            this->setBalance(days*12);
        }
        else if(longTermType == MEDIUM_SHORT)
        {
            this->setBalance(days*15);
        }
        else if(longTermType == MEDIUM)
        {
            this->setBalance(days*20);
        }
        else if(longTermType == LONG)
        {
            this->setBalance(days*50);
        }
        else if(longTermType == VERY_LONG)
        {
            this->setBalance(days*100);
        }
        this->setDeadline(endTime + boost::posix_time::hours(8640));
    }
}