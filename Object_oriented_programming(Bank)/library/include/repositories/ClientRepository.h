//
// Created by student on 14.04.2021.
//

#ifndef WARSZTATY1_CLIENTREPOSITORY_H
#define WARSZTATY1_CLIENTREPOSITORY_H
#include <string>
#include <iostream>
#include <vector>
#include <model/typedefs.h>
#include <model/Client.h>
#include <model/typedefs.h>
#include "repositories/Repository.h"

class ClientRepository : public Repository<Client>{

private:
        //std::vector<ClientPtr> clientRepository{};
public:
    ClientRepository();
    ~ClientRepository();
    //void add(ClientPtr);
    //void remove(ClientPtr);
    //ClientPtr get(unsigned int index) const;
    //std::string Raport() const;
    //int RepositorySize() const;
    //std::vector<ClientPtr> findAll(ClientPredicate predicate);
    //static bool testClientTwoRents(ClientPtr ptr);
    ClientPtr findByPersonalId(std::string);

    template <class C>  std::vector<ClientPtr> findAll (const C &predicate) const  //template metody findAll pozwalającej znaleźć obiekty odpowiadające podanemu predykatowi i zwrócić zawierający je wektor
    {
        std::vector<ClientPtr> found;
        for(unsigned int i = 0; i<objects.size(); ++i)
        {
            ClientPtr c = objects[i];
            if(c != nullptr && predicate(c))
            {
                found.push_back(c);
            }
        }
        return found;
    }
};


#endif //WARSZTATY1_CLIENTREPOSITORY_H
