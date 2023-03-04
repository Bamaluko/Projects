//
// Created by student on 29.04.2021.
//

#ifndef WARSZTATY1_CLIENTMANAGER_H
#define WARSZTATY1_CLIENTMANAGER_H

#include "model/typedefs.h"
#include "repositories/ClientRepository.h"
#include <vector>
#include <iostream>

class ClientManager{
    ClientRepoPtr currentClients;
public:
    ClientManager(const ClientRepoPtr &currentClients);
    ~ClientManager();
    ClientPtr getClient(std::string);
    ClientPtr registerClient(const std::string &, const std::string &, const std::string &, AddressPtr, ClientTypePtr);
    void unregisterClient(std::string);
    std::vector<ClientPtr> findClients(ClientPredicate) const;
    static bool findAll(ClientPtr client);
    static bool testClientMaxRentsIsOne(ClientPtr);
};


#endif //WARSZTATY1_CLIENTMANAGER_H
