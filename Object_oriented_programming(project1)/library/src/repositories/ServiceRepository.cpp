//
// Created by student on 02.06.2021.
//

#include "repositories/ServiceRepository.h"


std::vector<ServicePtr> ServiceRepository::findBy(const ServicePredicate &predicate) {
    std::vector<ServicePtr> found;
    for(unsigned int i = 0; i<objects.size(); i++)
    {
        ServicePtr service = objects[i];
        if((service != nullptr) && predicate(service))
        {
            found.push_back(service);
        }
    }
    return found;
}

const std::vector<ServicePtr> &ServiceRepository::findAll() {
    return objects;
}
