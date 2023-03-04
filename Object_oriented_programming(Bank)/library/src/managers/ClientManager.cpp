//
// Created by student on 29.04.2021.
//

#include "managers/ClientManager.h"
#include <iostream>
#include <vector>

ClientManager::ClientManager(const ClientRepoPtr &currentClients) : currentClients(currentClients) {  //konstruktor przyjmuje wektor zawierający obiekty klasy Client

}

ClientManager::~ClientManager() {  //destruktor repozytorium

}

ClientPtr ClientManager::getClient(std::string id) {  //metoda przyjmuje napis i szuka klienta, który ma atrybut id ospowiadający napisowi. Zwrócony zostanie wskaźnik na taki obiekt
    return this->currentClients->findByPersonalId(id);// a gdy go nie ma, to pusty wskaźnik.
}

ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID, AddressPtr address, ClientTypePtr clientType) {
    if(this->currentClients->findByPersonalId(personalID) != nullptr) //metoda przyjmuje dane dla konstruktora klasy Client. Jeśli taki klient istnieje w repozytorium, to zwrócony
        return this->currentClients->findByPersonalId(personalID);  //zostanie wskaźnik na tego klienta. Jeśli nie, to zostanie utworzony nowy obiekt w repozytorium i zwrocony zostanie
    else                                                           //wskaźnik na niego
    {
        ClientPtr client = std::make_shared<Client>(firstName, lastName, personalID, address, clientType);
        currentClients->add(client);
        return client;
    }

}

void ClientManager::unregisterClient(std::string id) {  //metoda ustawia klienta jako archiwalnego
    if(this->getClient(id) != nullptr)
    {
        this->getClient(id)->setArchive(true);
    }

}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate predicate) const {  //metoda find clients wykorzystuje metodę findAll i predykat by według niego zwrócić wektor objektów
    return this->currentClients->findAll(predicate);   //klasy Client spełniających warunki
}

bool ClientManager::findAll(ClientPtr ptr)   //predykat zwracający prawdę, gdy klient jest poza archiwum
{
    return (!ptr->isInArchive());
}

bool ClientManager::testClientMaxRentsIsOne(ClientPtr ptr) {  //przykładowy predykat
    if(!ptr->isInArchive())
        return ptr->getMaxVehicles()==1;
    else
        return false;
}





