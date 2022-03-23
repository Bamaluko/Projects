//
// Created by student on 18.05.2021.
//

#include "model/Bronze.h"


double Bronze::getMaxLoan() {
    return 100000;
}

int Bronze::getMaxDeposits() {
    return 1;
}

double Bronze::getLoanBonus() {
    return 0.1;
}

double Bronze::getDepositBonus() {
    return 0.05;
}

std::string Bronze::getType() {
    return "Bronze";
}
