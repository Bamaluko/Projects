//
// Created by student on 04.06.2021.
//

#ifndef BANK_ACCOUNTMANAGER_H
#define BANK_ACCOUNTMANAGER_H
#include "model/typedefs.h"
#include "repositories/AccountRepository.h"
#include <vector>
#include <iostream>
#include "AccountRepository.h"

class AccountManager {
private:
    AccountRepoPtr currentAccounts = std::make_shared<AccountRepository>();
public:
    AccountManager();
    virtual ~AccountManager();
    AccountPtr getAccount(const std::string& id);
    void registerAccount(const std::string &firstName, const std::string &lastName, const std::string &id, const AddressPtr &address);
    void unregisterAccount(const std::string& id);
    std::vector<AccountPtr> findAccounts(AccountPredicate);
    static bool findAll(const AccountPtr&);
};


#endif //BANK_ACCOUNTMANAGER_H
