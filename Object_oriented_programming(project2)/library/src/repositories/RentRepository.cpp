//
// Created by student on 14.04.2021.
//

#include "repositories/RentRepository.h"

#include "repositories/VehicleRepository.h"
#include <algorithm>
#include "model/typedefs.h"


using namespace  std;

RentRepository::RentRepository(){  //konstruktor repozytorium z pustym wektorem
}

RentRepository::~RentRepository(){ //destruktor zwalniający wskaźniki
    for(unsigned int i=0; i<RepositorySize(); i++)
    {
        objects.erase(objects.begin() + i);
    }

}

//void RentRepository::add(RentPtr rent)
//{
//    if(rent!=nullptr)
//        rentRepository.push_back(rent);
//}
//
//void RentRepository::remove(RentPtr rent)
//{
//    if(rent!=nullptr)
//        rentRepository.erase(std::remove(rentRepository.begin(), rentRepository.end(), rent), rentRepository.end());
//}
//
//RentPtr RentRepository::get(unsigned int index)
//{
//    if(index>((unsigned int)(this->RepositorySize()-1)))
//        return nullptr;
//    else
//        return rentRepository.at(index);
//
//}
//
//std::string RentRepository::Raport() const {
//    std::string string;
//    for(unsigned int i=0; i<rentRepository.size(); i++)
//    {
//        string += rentRepository.at(i)->getRentInfo() + "    ";
//    }
//    return string;
//}
//
//int RentRepository::RepositorySize() const {
//    return rentRepository.size();
//}

bool RentRepository::testRentIndex12OrHigher(RentPtr ptr) { //przykładowy predykar
    return ptr->getId()>=12;
}

std::vector<RentPtr> RentRepository::findAll(RentPredicate predicate) {   //metoda zwraca wektor obiektów spełniających podany w parametrze predykat
    vector<RentPtr> found;
    for (unsigned int i = 0; i < (unsigned int)(this->RepositorySize()); i++) {
        RentPtr rent = this->get(i);
        if (rent != nullptr && predicate(rent)) {
            found.push_back(rent);
        }
    }
    return found;
}
