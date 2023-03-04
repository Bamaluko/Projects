//
// Created by student on 04.05.2021.
//

#include "model/VehicleException.h"
using namespace  std;

VehicleException::VehicleException(const string& arg) : logic_error(arg){ //zbiór wyjątków logicznych dla klasy vehicle. Informuje o podaniu błędnego parametru
}

const string VehicleException::exceptionPrice = "INVALID PRICE";
const string VehicleException::exceptionPlateNumber = "INVALID PLATE NUMBER";