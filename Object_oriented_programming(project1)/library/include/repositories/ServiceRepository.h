//
// Created by student on 02.06.2021.
//

#ifndef BANK_SERVICEREPOSITORY_H
#define BANK_SERVICEREPOSITORY_H
#include "Service.h"
#include "Repository.h"

class ServiceRepository : public Repository<Service>{
public:
    ServiceRepository() = default;
    virtual ~ServiceRepository() = default;
    std::vector<ServicePtr> findBy(const ServicePredicate& predicate);
    const std::vector<ServicePtr> &findAll();
};


#endif //BANK_SERVICEREPOSITOSRY_H
