//
// Created by student on 04.05.2021.
//

#include "model/ClientException.h"

using namespace  std;

ClientException::ClientException(const string &arg) : logic_error(arg)  //zbiór wyjątków logicznych dla klasy Client, informują o podaniu niewłaściwego parametru przez użytkownika
{}

const string ClientException::exceptionFirstName = "INVALID FIRST NAME";
const string ClientException::exceptionLastName = "INVALID LAST NAME";
const string ClientException::exceptionPersonalID = "INVALID PERSONAL ID";
const string ClientException::exceptionAddress = "INVALID ADDRESS";
const string ClientException::exceptionClientType = "INVALID CLIENT TYPE";