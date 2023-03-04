//
// Created by student on 27.05.2021.
//

#include "AddressException.h"

AddressException::AddressException(const string& arg) : logic_error(arg)  //Zbiór wyjątków informujących o błędnie podanym parametrze dla metod klasy Address
{}

const string AddressException::exceptionStreet = "INVALID STREET NAME";
const string AddressException::exceptionNumber = "INVALID HOUSE NUMBER";
const string AddressException::exceptionCity = "INVALID CITY NAME";