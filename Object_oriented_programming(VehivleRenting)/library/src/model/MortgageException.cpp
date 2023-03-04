//
// Created by student on 28.05.2021.
//

#include "MortgageException.h"

MortgageException::MortgageException(const std::string &message) : logic_error(message)
{
}

const std::string MortgageException::exceptionId = "Invalid Id";
const std::string MortgageException::exceptionBeginTime = "Begin time is not a date time";
const std::string MortgageException::exceptionDeadline = "Deadline smaller than beginTime or not a date time";
const std::string MortgageException::exceptionBalance = "Balance smaller or equals 0";
const std::string MortgageException::exceptionPercentage = "Percentage should be beetwen 0 and 1";
const std::string MortgageException::exceptionAddress = "Address nullptr";
const std::string MortgageException::exceptionAccount = "Account nullptr";
