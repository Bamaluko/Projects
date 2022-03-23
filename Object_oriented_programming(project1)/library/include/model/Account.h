//
// Created by student on 18.05.2021.
//

#ifndef WARSZTATY1_ACCOUNT_H
#define WARSZTATY1_ACCOUNT_H
#include <string>
#include "typedefs.h"


class Account {
private:
    std::string firstName;
    std::string lastName;
    std::string id;
    double balance;
    bool archive;
    AccountTypePtr accountType;
    AddressPtr address;
    void setBalance(double balance);

public:
    Account(const std::string &firstName, const std::string &lastName, const std::string &id, const AddressPtr &address);
    virtual ~Account() = default;

    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getId() const;
    double getBalance() const;
    bool isArchive() const;
    const AccountTypePtr getAccountType() const;
    const AddressPtr &getAddress() const;

    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setIsArchive(bool isArchive);

    void setAddress(const AddressPtr &address);

    void setAccountType(AccountTypePtr account);
    void putMoneyIn(double money);
    double takeMoneyOut(double money);
    std::string getAccountInfo();
    double getMaxLoan();
    int getMaxDeposits();

    std::string getInfo();

    


};


#endif //WARSZTATY1_ACCOUNT_H
