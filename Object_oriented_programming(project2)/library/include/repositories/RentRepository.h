//
// Created by student on 14.04.2021.
//

#ifndef WARSZTATY1_RENTREPOSITORY_H
#define WARSZTATY1_RENTREPOSITORY_H
#include <model/typedefs.h>
#include <iostream>
#include <vector>
#include "repositories/Repository.h"

class RentRepository : public Repository<Rent>{
private:
    //std::vector<RentPtr> rentRepository{};
public:
    RentRepository();
    ~RentRepository();
    //void add(RentPtr);
    //void remove(RentPtr);
    //RentPtr get(unsigned int index);
    //std::string Raport() const;
    //int RepositorySize() const;
    static bool testRentIndex12OrHigher(RentPtr ptr);
    std::vector<RentPtr> findAll(RentPredicate predicate);
};


#endif //WARSZTATY1_RENTREPOSITORY_H
