//
// Created by student on 21.05.2021.
//

#ifndef BANK_LOAN_H
#define BANK_LOAN_H

#include "Service.h"
#include <vector>

class Loan : public Service
{
private:
    double finalBalance;
    pt::ptime deadline;
    std::vector<PaymentPtr> payments;
    void endService(const pt::ptime &endTime) override=0;

protected:
    void setDeadline(const pt::ptime &deadline);

public:
    Loan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double balance, const AccountPtr &account, double percentage);

    ~Loan() override = default;
    void payMoney(double moneyPaid, const pt::ptime &time);
    PaymentPtr getPayment(unsigned long id) const;
    std::string getInfo() const override;
    const pt::ptime &getDeadline() const;

    double getFinalBalance() const override;

    std::string getServiceType() override;

};

#endif //BANK_LOAN_H
