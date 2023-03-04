//
// Created by student on 21.05.2021.
//

#ifndef BANK_PAYMENT_H
#define BANK_PAYMENT_H

#include <boost/date_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Payment
{
private:
    int id;
    double money;
    pt::ptime time;
public:
    Payment(int id, double money, const pt::ptime &time);
    ~Payment() = default;

    double getMoney() const;
    const pt::ptime &getTime() const;
    int getId() const;
};

#endif //BANK_PAYMENT_H
