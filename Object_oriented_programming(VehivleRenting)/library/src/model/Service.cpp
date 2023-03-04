//
// Created by student on 21.05.2021.
//

#include "Service.h"

Service::Service(const std::string &id, pt::ptime beginTime, double balance, const AccountPtr &account, double percentage) :
id(id), beginTime(beginTime), balance(balance), account(account), percentage(percentage)
{
}

double Service::getBalance() const {
    return balance;
}

double Service::getPercentage() const {
    return percentage;
}

void Service::setEndTime(const pt::ptime &endTime1) {
    Service::endTime = endTime1;
}

void Service::setBalance(double balance1) {
    Service::balance = balance1;
}

AccountPtr Service::getAccount(){
    return account;
}

const pt::ptime &Service::getEndTime() const {
    return endTime;
}

const pt::ptime &Service::getBeginTime() const {
    return beginTime;
}

const std::string &Service::getId() const {
    return id;
}

void Service::setBeginTime(const pt::ptime &beginTime1) {
    Service::beginTime = beginTime1;
}

void Service::setPercentage(double newPercentage) {
    Service::percentage = newPercentage;
}


