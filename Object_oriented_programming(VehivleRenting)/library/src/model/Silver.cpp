//
// Created by student on 18.05.2021.
//

#include "model/Silver.h"

double Silver::getMaxLoan() {
    return 500000;
}

int Silver::getMaxDeposits() {
    return 3;
}

double Silver::getLoanBonus() {
    return 0.2;
}

double Silver::getDepositBonus() {
    return 0.1;
}

std::string Silver::getType() {
    return "Silver";
}
