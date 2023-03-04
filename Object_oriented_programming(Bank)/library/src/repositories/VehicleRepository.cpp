//
// Created by student on 14.04.2021.
//

#include "repositories/VehicleRepository.h"
#include <algorithm>
#include "model/typedefs.h"

using namespace  std;

VehicleRepository::VehicleRepository(){  //konstruktor repozytorium z pustym wektorem
}

VehicleRepository::~VehicleRepository(){ //destruktor zwalniający wskaźniki
    for(unsigned int i=0; i<RepositorySize(); i++)
    {
        objects.erase(objects.begin() + i);
    }
}

//void VehicleRepository::add(VehiclePtr  vehicle)
//{
//    if(vehicle!=nullptr)
//        vehicleRepository.push_back(vehicle);
//}
//
//void VehicleRepository::remove(VehiclePtr  vehicle)
//{
//    if(vehicle!=nullptr)
//        vehicleRepository.erase(std::remove(vehicleRepository.begin(), vehicleRepository.end(), vehicle), vehicleRepository.end());
//}
//
//VehiclePtr VehicleRepository::get(unsigned int index)
//{
//    if(index>((unsigned int)(this->RepositorySize()-1)))
//        return nullptr;
//    else
//        return vehicleRepository.at(index);
//
//}
//
//std::string VehicleRepository::Raport() const {
//    std::string string;
//    for(unsigned int i=0; i<vehicleRepository.size(); i++)
//    {
//        string += vehicleRepository.at(i)->getVehicleInfo() + "    ";
//    }
//    return string;
//}
//
//int VehicleRepository::RepositorySize() const {
//    return vehicleRepository.size();
//}

bool VehicleRepository::testVehiclePrise10OrHigher(VehiclePtr ptr) { //przykładowy predykat
    return ptr->BasePrice()>=10;
}

vector<VehiclePtr> VehicleRepository::findAll(VehiclePredicate predicate) { //metoda zwraca wektor obiektów spełniających podany w parametrze predykat
    vector<VehiclePtr> found;
    for (unsigned int i = 0; i < (unsigned int)this->RepositorySize(); i++) {
        VehiclePtr vehicle = this->get(i);
        if (vehicle != nullptr && predicate(vehicle)) {
            found.push_back(vehicle);
        }
    }
    return found;
}

VehiclePtr VehicleRepository::findByPlateNumber(std::string plateNumber) { //metoda pozwalająca znaleźć w repozytorium obiekt o podanym plateNumber i zwrócić wskaźnik na niego
    for(unsigned int i=0; i<this->RepositorySize(); i++)
    {
        if(this->get(i)->getPlateNumber()==plateNumber)
            return this->get(i);
    }
    return nullptr;
}




