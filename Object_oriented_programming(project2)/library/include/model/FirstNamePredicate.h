//
// Created by student on 06.05.2021.
//

#ifndef WARSZTATY1_FIRSTNAMEPREDICATE_H
#define WARSZTATY1_FIRSTNAMEPREDICATE_H

#include <regex>
#include "typedefs.h"
#include "model/Client.h"

class FirstNamePredicate {
private:
    std::string name;
public:
    FirstNamePredicate(std::string ini_name) : name(ini_name){}

    bool operator()(const ClientPtr &ptr) const
    {
        std::regex temp ( "(.*)" + name + "(.*)" );

        return std::regex_match(ptr->getFirstName(),temp);
    }

};

#endif //WARSZTATY1_FIRSTNAMEPREDICATE_H
