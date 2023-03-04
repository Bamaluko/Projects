//
// Created by student on 21.05.2021.
//

#include "Loan.h"
#include "Payment.h"
#include "Account.h"


Loan::Loan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance, const AccountPtr &account, double percentage) :
Service(id, beginTime, balance, account, percentage),  finalBalance(balance), deadline(deadline)
{

}

void Loan::payMoney(double moneyPaid, const pt::ptime &time) {
    if(this->getBalance()<=moneyPaid)//Na wypadek, gdy przeplacimy
    {
        PaymentPtr newPayment = std::make_shared<Payment>(payments.size(), this->getBalance(), time); //Ustawiamy wartosc paymentu na tyle, ile jeszcze zostalo do splacenia
        payments.push_back(newPayment);
        this->setBalance(this->getBalance()-moneyPaid);
        this->getAccount()->putMoneyIn(-this->getBalance()); //Wowczas zwracamy niepotrzebna czesc wplaty na konto (jesli balans pozyczki to np. -23$, to wplacimy na konto 23$)
        this->setBalance(0);//Pozyzcka zostala splacona, a kwota naddatkowa zostala zwrocona (balance=0)
        this->endService(time);//Wywolujemy metode konczaca dany service, sprawdzimy tam, czy pozyczka zostala splacona w teminie
    }
    else//jesli pozyczka pozostaje niesplacona, to po prostu dokonujemy wplaty
    {
        PaymentPtr newPayment = std::make_shared<Payment>(payments.size(), moneyPaid, time);
        payments.push_back(newPayment);
        this->setBalance(this->getBalance()-moneyPaid);
    }
}

PaymentPtr Loan::getPayment(unsigned long id) const {
    if(payments.size() <= id)
    {
        return nullptr;
    }
    return payments[id];
}

const pt::ptime &Loan::getDeadline() const {
    return deadline;
}

void Loan::setDeadline(const pt::ptime &deadline1) {
    Loan::deadline = deadline1;
}

std::string Loan::getInfo() const {
    return "POZYCZKA: " + this->getId() + " O BALANSIE: " + std::to_string(this->getBalance()) + " I OPROCENTOWANIU : " + std::to_string(this->getPercentage());
}

double Loan::getFinalBalance() const {
    return finalBalance;
}

std::string Loan::getServiceType() {
    return "Loan";
}
