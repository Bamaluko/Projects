//
// Created by student on 22.05.2021.
//

#include "ShortTermLoan.h"
#include "ShortTermLoanException.h"

ShortTermLoan::ShortTermLoan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance,
                             const AccountPtr &account, double percentage) :
                     Loan(id, beginTime,deadline, balance, account, percentage)
 {
    if(id.empty()) throw ShortTermLoanException(ShortTermLoanException::exceptionId);
    if(beginTime == pt::not_a_date_time) throw ShortTermLoanException(ShortTermLoanException::exceptionBeginTime);
    if( (beginTime >= deadline) || (deadline == pt::not_a_date_time)) throw ShortTermLoanException(ShortTermLoanException::exceptionDeadline);
    pt::time_period period(beginTime, deadline);
    if(period.length().hours()/8760 > 5) throw ShortTermLoanException(ShortTermLoanException::exceptionTooLongPeriod);//tutaj pięć i ponad pięć
    if(balance <= 0) throw ShortTermLoanException(ShortTermLoanException::exceptionBalance);
    if( (percentage < 0) || (percentage > 1) ) throw ShortTermLoanException(ShortTermLoanException::exceptionPercentage);
    if(account == nullptr) throw ShortTermLoanException(ShortTermLoanException::exceptionAccount);
    this->setBalance(balance+balance*percentage);
 }

void ShortTermLoan::endService(const pt::ptime &endTime) {
    if(endTime<=this->getDeadline())//Jesli wyrobilismy sie ze splata, to ustawiamy czas zakonczenia pozyczki, reszta zajmie sie manager
        this->setEndTime(endTime);
    else
    {
        int days;
        pt::time_period period(getDeadline(), endTime);  //Wyliczamy opoznienie w splacie pozyczki, ne jego podstawie doliczona zostanie kara
        long long int secs = period.length().hours()*3600+period.length().minutes()*60+period.length().seconds();  //Obliczamy opoznienie najpierw sekundach
        days=(int)(secs/86400);//przeliczamy wartosc w sekundach na dni
        this->setBalance(days*10);//Za kazdy dzien opoznienia nakladamy 10$ kary. Manadzer bedzie poxniej wiedzial, czy pozyczka zostala splacona sprawdzajac, czy balance=0
        this->setDeadline(endTime + boost::posix_time::hours(8640));//Ustawiamy nowa wartosc deadline (Dla pozyczki ShortTerm jest to 360 dni)
    }

}
