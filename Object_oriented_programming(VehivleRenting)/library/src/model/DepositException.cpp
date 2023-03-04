//
// Created by student on 28.05.2021.
//

#include "DepositException.h"

DepositException::DepositException(const string& arg) : logic_error(arg)  //Zbiór wyjątków informujących o błędnie podanym parametrze dla metod klasy Address
{}

const string DepositException::exceptionId = "INVALID ID";
const string DepositException::exceptionNotADateTime = "YOU NEED TO INSERT PROPER DATE";
const string DepositException::exceptionBalance = "BALANCE CANNOT BE BELOW 0";
const string DepositException::exceptionAccount = "NOT PROVIDED WITH PROPER ACCOUNT";
const string DepositException::exceptionPercentage = "PERCENTAGE CANNOT BE BELOW 0 AND ABOVE 1 (0.05 = 5%)";

