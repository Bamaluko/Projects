//
// Created by student on 18.05.2021.
//

#ifndef BANK_TYPEDEFS_H
#define BANK_TYPEDEFS_H

#include <vector>
#include <memory>
#include<functional>
#include "Address.h"

class AccountType;
class Account;
class Payment;
class Service;
class Loan;
class Deposit;
class AccountRepository;
class ServiceRepository;
class AccountManager;
class Mortgage;
class ShortTermLoan;
class LongTermLoan;
class ServicesManager;

typedef std::shared_ptr<Mortgage> MortgagePtr;
typedef std::shared_ptr<ShortTermLoan> ShortTermLoanPtr;
typedef std::shared_ptr<LongTermLoan> LongTermLoanPtr;
typedef std::shared_ptr<Loan> LoanPtr;
typedef std::shared_ptr<Deposit> DepositPtr;
typedef std::shared_ptr<Service> ServicePtr;
typedef std::shared_ptr<Payment> PaymentPtr;
typedef std::shared_ptr<AccountType> AccountTypePtr;
typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Account> AccountPtr;

typedef std::shared_ptr<AccountRepository> AccountRepoPtr;
typedef std::shared_ptr<ServiceRepository> ServiceRepoPtr;

typedef std::function<bool(AccountPtr)> AccountPredicate;
typedef std::function<bool(ServicePtr)> ServicePredicate;

typedef std::shared_ptr<AccountManager> AccountManagerPtr;
typedef std::shared_ptr<ServicesManager> ServicesManagerPtr;

#endif //BANK_TYPEDEFS_H
