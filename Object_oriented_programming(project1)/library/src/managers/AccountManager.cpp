//
// Created by student on 04.06.2021.
//

#include "managers/AccountManager.h"

AccountManager::AccountManager()
{

}

AccountManager::~AccountManager() {

}

AccountPtr AccountManager::getAccount(const std::string& id) {
    for(unsigned int i=0; i<currentAccounts->size(); i++)
    {
        if(currentAccounts->get(i)->getId()==id)
            return currentAccounts->get(i);
    }
    return nullptr;
}

void AccountManager::registerAccount(const std::string &firstName, const std::string &lastName, const std::string &id,
                          const AddressPtr &address) {
    if(this->getAccount(id) == nullptr)
    {
        AccountPtr account = std::make_shared<Account>(firstName, lastName, id, address);
        currentAccounts->add(account);
    }
}

void AccountManager::unregisterAccount(const std::string &id) {
    if(this->getAccount(id)!= nullptr)
        this->getAccount(id)->setIsArchive(true);

}

std::vector<AccountPtr> AccountManager::findAccounts(AccountPredicate predicate) {
    return currentAccounts->findBy(predicate);
}

bool AccountManager::findAll(const AccountPtr& ptr) {//predykat do znajdywania wszystkich niezarchiwizowanych klientow
    return (!ptr->isArchive());
}
