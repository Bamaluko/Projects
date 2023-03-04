//
// Created by student on 21.05.2021.
//

#include "Payment.h"

Payment::Payment(int id, double money, const pt::ptime &time) : id(id), money(money), time(time) {}

double Payment::getMoney() const {
    return money;
}

const pt::ptime &Payment::getTime() const {
    return time;
}

int Payment::getId() const {
    return id;
}
