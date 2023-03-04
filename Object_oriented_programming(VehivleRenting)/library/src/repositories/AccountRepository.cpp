//
// Created by student on 01.06.2021.
//

#include "repositories/AccountRepository.h"

std::vector<AccountPtr> AccountRepository::findBy(const AccountPredicate& predicate) {
    std::vector<AccountPtr> found;
    for(unsigned int i = 0; i<objects.size(); i++)
    {
        AccountPtr account = objects[i];
        if(account != nullptr && predicate(account))
        {
            found.push_back(account);
        }
    }
    return found;
}

bool AccountRepository::findAll(AccountPtr) {
    return true;
}


