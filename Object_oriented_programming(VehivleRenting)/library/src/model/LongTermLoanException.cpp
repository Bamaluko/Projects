//
// Created by student on 28.05.2021.
//

#include "LongTermLoanException.h"

LongTermLoanException::LongTermLoanException(const std::string &arg) : logic_error(arg)
{

}

const std::string LongTermLoanException::exceptionId = "Invalid Id";;
const std::string LongTermLoanException::exceptionBeginTime = "Begin time is not a date time";;
const std::string LongTermLoanException::exceptionAccount = "Account nullptr";;