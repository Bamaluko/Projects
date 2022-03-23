//
// Created by student on 04.05.2021.
//

#include "model/RentException.h"
using namespace  std;

RentException::RentException(const string& arg) : logic_error(arg)  //zbiór wyjątków dla klasy Rent informujących o błędnie podanym parametrze
{}

const string RentException::exceptionClientNullPtr = "INVALID CLIENT (NULLPTR)";
const string RentException::exceptionVehicleNullPtr = "INVALID VEHICLE (NULLPTR)";
const string RentException::exceptionID ="INVALID ID";