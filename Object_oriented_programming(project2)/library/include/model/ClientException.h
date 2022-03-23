//
// Created by student on 04.05.2021.
//

#ifndef WARSZTATY1_CLIENTEXCEPTION_H
#define WARSZTATY1_CLIENTEXCEPTION_H
#include <stdexcept>


class ClientException : public std::logic_error
{
public:
    explicit ClientException(const std::string&);
    static const std::string exceptionFirstName;
    static const std::string exceptionLastName;
    static const std::string exceptionPersonalID;
    static const std::string exceptionAddress;
    static const std::string exceptionClientType;
};


#endif //WARSZTATY1_CLIENTEXCEPTION_H
