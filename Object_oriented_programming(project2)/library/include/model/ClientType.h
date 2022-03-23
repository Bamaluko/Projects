//
// Created by student on 26.04.2021.
//

#ifndef WARSZTATY1_CLIENTTYPE_H
#define WARSZTATY1_CLIENTTYPE_H

#include <string>
#include "typedefs.h"

class ClientType
{
public:
    virtual double applyDiscount(double price)=0;
    virtual int getMaxVehicles()=0;
    virtual std::string getTypeInfo()=0;
    virtual ~ClientType()= 0;
};


#endif //WARSZTATY1_CLIENTTYPE_H
