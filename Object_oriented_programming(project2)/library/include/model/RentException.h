//
// Created by student on 04.05.2021.
//

#ifndef WARSZTATY1_RENTEXCEPTION_H
#define WARSZTATY1_RENTEXCEPTION_H
#include<stdexcept>

class RentException : public std::logic_error
{
public:
    explicit RentException(const std::string&);
    static const std::string exceptionClientNullPtr;
    static const std::string exceptionVehicleNullPtr;
    static const std::string exceptionID;
};


#endif //WARSZTATY1_RENTEXCEPTION_H
