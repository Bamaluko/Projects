//
// Created by student on 18.05.2021.
//

#include "model/Account.h"
#include "model/Bronze.h"
#include <utility>
#include <AccountException.h>
#include <iostream>

Account::Account(const std::string &firstName, const std::string &lastName, const std::string &id,
                 const AddressPtr &address) : firstName(firstName), lastName(lastName), id(id), address(address) {
    if (firstName.empty()) throw AccountException(AccountException::exceptionFirstName);
    if (lastName.empty()) throw AccountException(AccountException::exceptionLastName);
    if (id.empty()) throw AccountException(AccountException::exceptionPersonalID);                     //konstruktor dla obiektu klasy Client. Sprawdza jednocześnie, czy
    if (address == nullptr) throw AccountException(AccountException::exceptionAddress);                         //poadne dane są poprawne, jeśli nie, to wyrzuca wyjątek. Parametry to
    archive = false;
    balance = 0;
    AccountTypePtr bronze = std::shared_ptr<AccountType>(new Bronze);
    accountType = bronze;
}

const std::string &Account::getFirstName() const {
    return firstName;
}

const std::string &Account::getLastName() const {
    return lastName;
}

const std::string &Account::getId() const {
    return id;
}

double Account::getBalance() const {
    return balance;
}

bool Account::isArchive() const {
    return archive;
}

void Account::setFirstName(const std::string &firstName1) {
    if (firstName1.empty()) throw AccountException(AccountException::exceptionFirstName);
    Account::firstName = firstName1;
}

void Account::setLastName(const std::string &lastName1) {
    if (lastName1.empty()) throw AccountException(AccountException::exceptionLastName);
    Account::lastName = lastName1;
}

void Account::setBalance(double balance1) {
    Account::balance = balance1;
}

void Account::setIsArchive(bool isArchive) {
    Account::archive = isArchive;
}

const AccountTypePtr Account::getAccountType() const {
    return accountType;
}

const AddressPtr &Account::getAddress() const {
    return address;
}

void Account::setAccountType(AccountTypePtr type) {
    Account::accountType = std::move(type);
}

void Account::putMoneyIn(double money) {
    setBalance(getBalance()+money);
}

double Account::takeMoneyOut(double money) {
    if(money<=this->getBalance())
        setBalance(getBalance()-money);
    else
        throw AccountException(AccountException::exceptionSetBalance);
    return money;
}

std::string Account::getAccountInfo() {
    return getFirstName() + " " + getLastName() + " Id:" + getId() + " Balance:" + std::to_string(getBalance()) + " Account Type: " + getAccountType()->getType();
}

double Account::getMaxLoan() {
    return getAccountType()->getMaxLoan();
}

int Account::getMaxDeposits() {
    return getAccountType()->getMaxDeposits();
}

void Account::setAddress(const AddressPtr &address1) {
    if (address1 == nullptr) throw AccountException(AccountException::exceptionAddress);
    Account::address = address1;
}

std::string Account::getInfo() {
    return this->getAccountInfo();
}




