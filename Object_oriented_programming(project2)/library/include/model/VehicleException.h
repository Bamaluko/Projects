//
// Created by student on 04.05.2021.
//

#ifndef WARSZTATY1_VEHICLEEXCEPTION_H
#define WARSZTATY1_VEHICLEEXCEPTION_H
#include <stdexcept>


class VehicleException : public std::logic_error
{
public:
    explicit VehicleException(const std::string&);
    static const std::string exceptionPrice;
    static const std::string exceptionPlateNumber;
};


#endif //WARSZTATY1_VEHICLEEXCEPTION_H
