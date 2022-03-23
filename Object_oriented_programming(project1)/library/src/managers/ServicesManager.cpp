//
// Created by student on 08.06.2021.
//

#include "ServiceRepository.h"
#include "ServicesManager.h"
//#include "LongTermLoan.h"
#include "LongTermLoanException.h"
#include "ShortTermLoan.h"
#include "ShortTermLoanException.h"
#include "Mortgage.h"
#include "MortgageException.h"
#include "Deposit.h"
#include "DepositException.h"
#include "Account.h"
#include "Bronze.h"
#include "Silver.h"
#include "Gold.h"

ServicesManager::ServicesManager()
{
}

ServicePtr ServicesManager::getService(const std::string &id) const
{
    ServicePredicate predicateID = [id](const ServicePtr &service)
    {
        if(service->getId() == id) {
            return true;
        }
        return false;
    };
    std::vector<ServicePtr> found = findServices(predicateID);
    if(found.size() == 1)
        return found[0];
    else
        return nullptr;

}

void ServicesManager::createLongTermLoan(const std::string &id, const pt::ptime &beginTime, const AccountPtr &account,
                                         LongTermLoanType type)
{
    try
    {
        LongTermLoanPtr newLongTermLoan = std::make_shared<LongTermLoan>(id, beginTime, account, type);
        serviceRepository->add(newLongTermLoan);
    }
    catch (LongTermLoanException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ServicesManager::createShortTermLoan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline,
                                          const AccountPtr &account, double moneyLoan, double percentage)
{
    try
    {
        ShortTermLoanPtr newShortTermLoan = std::make_shared<ShortTermLoan>(id, beginTime, deadline, moneyLoan, account, percentage);
        serviceRepository->add(newShortTermLoan);
    }
    catch (ShortTermLoanException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ServicesManager::createMortgage(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline,
                                     double moneyLoan,
                                     const AccountPtr &account, double percentage, const AddressPtr &houseAddress)
{
    try
    {
        MortgagePtr newMortgage = std::make_shared<Mortgage>(id, beginTime, deadline, moneyLoan, account, percentage, houseAddress);
        serviceRepository->add(newMortgage);
    }
    catch (MortgageException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ServicesManager::createDeposit(const std::string &id, const pt::ptime &beginTime, double money,
                                    const AccountPtr &account, double percentage, bool capitalization)
{
    try
    {
        DepositPtr newDeposit = std::make_shared<Deposit>(id, beginTime, money, account, percentage, capitalization);
        serviceRepository->add(newDeposit);
    }
    catch (DepositException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void ServicesManager::endDeposit(ServicePtr deposit, const pt::ptime &endTime)
{
    if(deposit->getServiceType() == "Deposit")
    {
        std::vector<ServicePtr> found = findServices([deposit](ServicePtr service) {
            if(deposit == service)
            {
                return true;
            }
            return false;
        });
        if(found[0]==deposit)
        {
            deposit->endService(endTime);
            serviceArchive->add(deposit);
            serviceRepository->remove(deposit);
            changeAccountType(deposit->getAccount());
        }
    }


}

std::vector<ServicePtr> ServicesManager::getAllAccountServices(const AccountPtr &account) const
{
    std::vector<ServicePtr> found=findServices([account](ServicePtr service) {
        if(service->getAccount() == account)
        {
            return true;
        }
        return false;
    });

    return found;
}

std::vector<ServicePtr> ServicesManager::findServices(ServicePredicate predicate) const
{
    std::vector<ServicePtr> found = serviceRepository->findBy(predicate);
    return found;
}

std::vector<ServicePtr> ServicesManager::findAll()
{
    return serviceRepository->findAll();
}

double ServicesManager::checkActivity(const AccountPtr &account) const
{
    double sum = 0.0;
    for(unsigned int i =0; i<serviceArchive->size(); i++)
    {
        if(serviceArchive->get(i)->getAccount()==account)
            sum += serviceArchive->get(i)->getFinalBalance();
    }
    return sum;
}

void ServicesManager::changeAccountType(const AccountPtr &account) const
{
    double sum = checkActivity(account);
    if(sum <= 100000)
    {
        account->setAccountType(std::make_shared<Bronze>());
    }
    else if(sum <= 500000)
    {
        account->setAccountType(std::make_shared<Silver>());
    }
    else if(sum <= 1000000)
    {
        account->setAccountType(std::make_shared<Gold>());
    }
}

void ServicesManager::payMoneyLoan(const ServicePtr &loan, double money, pt::ptime date)
{
    if(loan->getServiceType() == "Loan")
    {
        std::vector<ServicePtr> found = findServices([loan](const ServicePtr &service) {
            if(loan == service)
            {
                return true;
            }
            return false;
        });
        if(found.size() == 1) {
            LoanPtr castedPtr = std::dynamic_pointer_cast<Loan>(loan);
            castedPtr->payMoney(money, date);
            if(loan->getBalance() == 0)
            {
                serviceArchive->add(loan);
                serviceRepository->remove(loan);
                changeAccountType(loan->getAccount());
            }
        }
    }

}

ServicePtr ServicesManager::getServiceArchive(const string &id) const {
    for(unsigned int i=0; i < serviceArchive->size(); i++)
    {

        if(serviceArchive->get(i)->getId() == id )
            return serviceArchive->get(i);
    }

    return nullptr;
}


