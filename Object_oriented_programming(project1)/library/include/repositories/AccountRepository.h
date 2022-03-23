//
// Created by student on 01.06.2021.
//

#ifndef BANK_ACCOUNTREPOSITORY_H
#define BANK_ACCOUNTREPOSITORY_H

#include "Account.h"
#include "Repository.h"
#include "typedefs.h"

class AccountRepository : public Repository<Account>{
public:
    AccountRepository() = default;
    virtual ~AccountRepository() = default;
    std::vector<AccountPtr> findBy(const AccountPredicate& predicate);
    static bool findAll(AccountPtr);
};


#endif //BANK_ACCOUNTREPOSITORY_H
