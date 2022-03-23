//
// Created by student on 14.04.2021.
//

#include "repositories/ClientRepository.h"
#include <algorithm>
#include <vector>
#include "model/typedefs.h"



ClientRepository::ClientRepository(){  //konstruktor repozytorium z pustym wektorem
}

ClientRepository::~ClientRepository(){  //destruktor zwalniający wskaźniki
    for(unsigned int i=0; i<RepositorySize(); i++)
    {
       objects.erase(objects.begin() + i);
    }

}
//
//void ClientRepository::add(ClientPtr client)
//{
//    if(client!=nullptr)
//        clientRepository.push_back(client);
//}
//
//void ClientRepository::remove(ClientPtr client)
//{
//    if(client!=nullptr)
//    clientRepository.erase(std::remove(clientRepository.begin(), clientRepository.end(), client), clientRepository.end());
//}
//
//ClientPtr ClientRepository::get(unsigned int index) const {
//    if(index>((unsigned int)(this->RepositorySize()-1)))
//        return nullptr;
//    else
//        return clientRepository.at(index);
//
//}
//
//std::string ClientRepository::Raport() const {
//    std::string string;
//    for(unsigned int i=0; i<clientRepository.size(); i++)
//    {
//        string += clientRepository.at(i)->getClientinfo() + "    ";
//    }
//    return string;
//}
//
//int ClientRepository::RepositorySize() const {
//    return clientRepository.size();
//}

//std::vector<ClientPtr> ClientRepository::findAll(ClientPredicate predicate) {
//    std::vector<ClientPtr> found;
//    for (unsigned int i = 0; i < (unsigned int)(this->RepositorySize()); i++) {
//        ClientPtr client = this->get(i);
//        if (client != nullptr && predicate(client)) {
//            found.push_back(client);
//        }
//    }
//    return found;
//}

ClientPtr ClientRepository::findByPersonalId(std::string id) {  //metoda zwracajaca wskaźnik na obiekt repozytorium o podanym id
    for(unsigned int i = 0; i<this->RepositorySize(); i++)
    {
        if(this->get(i)->getPersonalID()==id)
            return this->get(i);
    }

    return nullptr;
}



//bool ClientRepository::testClientTwoRents(ClientPtr ptr) {
//    return ptr->getCurrentRents().size()==2;
//}




