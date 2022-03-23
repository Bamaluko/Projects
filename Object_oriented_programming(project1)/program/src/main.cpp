#include <iostream>
#include "ServicesManager.h"
#include "ServiceRepository.h"

int main()
{
    ServicesManager sm;

    std::cout << "START" << std::endl;
    sm.createLongTermLoan("1", pt::not_a_date_time, nullptr, LONG);
    std::cout << "STOP" << std::endl;

    return 0;
}
