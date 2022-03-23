//
// Created by student on 06.05.2021.
//

#ifndef WARSZTATY1_LASTNAMEPREDICATE_H
#define WARSZTATY1_LASTNAMEPREDICATE_H

class LastNamePredicate {
private:
    std::string lastname;
public:
    LastNamePredicate(std::string last_name) : lastname(last_name){}

    bool operator()(const ClientPtr &ptr) const
    {
        std::regex temp ( "(.*)" + lastname + "(.*)" );

        return std::regex_match(ptr->getLastName(),temp);
    }

};

#endif //WARSZTATY1_LASTNAMEPREDICATE_H
