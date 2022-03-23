//
// Created by student on 27.05.2021.
//

#include "AccountException.h"

using namespace  std;

AccountException::AccountException(const string &arg) : logic_error(arg)  //zbiór wyjątków logicznych dla klasy Client, informują o podaniu niewłaściwego parametru przez użytkownika
{}

const string AccountException::exceptionFirstName = "INVALID FIRST NAME";
const string AccountException::exceptionLastName = "INVALID LAST NAME";
const string AccountException::exceptionPersonalID = "INVALID PERSONAL ID";
const string AccountException::exceptionAddress = "INVALID ADDRESS";
const string AccountException::exceptionSetBalance = "CURRENT BALANCE DOESN'T ENABLE THIS OPERATION";
