//
// Created by student on 18.05.2021.
//

#include "model/Gold.h"

double Gold::getMaxLoan() {
    return 1000000;
}

int Gold::getMaxDeposits() {
    return 5;
}

double Gold::getLoanBonus() {
    return 0.3;
}

double Gold::getDepositBonus() {
    return 0.15;
}

std::string Gold::getType() {
    return "Gold";
}
