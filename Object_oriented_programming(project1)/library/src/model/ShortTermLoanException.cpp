//
// Created by student on 28.05.2021.
//

#include "ShortTermLoanException.h"

ShortTermLoanException::ShortTermLoanException(const std::string& message) : logic_error(message)
{

}

const std::string ShortTermLoanException::exceptionId = "Invalid Id";
const std::string ShortTermLoanException::exceptionBeginTime = "Begin time is not a date time";
const std::string ShortTermLoanException::exceptionDeadline = "Deadline smaller than beginTime or not a date time";
const std::string ShortTermLoanException::exceptionBalance = "Balance smaller or equals 0";
const std::string ShortTermLoanException::exceptionPercentage = "Percentage should be beetwen 0 and 1";
const std::string ShortTermLoanException::exceptionAccount = "Account nullptr";
const std::string ShortTermLoanException::exceptionTooLongPeriod = "Max time period is 5 years";