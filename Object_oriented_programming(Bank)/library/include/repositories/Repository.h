//
// Created by student on 05.05.2021.
//

#ifndef WARSZTATY1_REPOSITORY_H
#define WARSZTATY1_REPOSITORY_H
#include <memory>
#include <string>
#include <vector>

template<class T> class Repository
{
protected:
    std::vector<std::shared_ptr<T>> objects;
public:
    std::shared_ptr<T> get(unsigned int index)  //getter pozwalający uzyskać obiekt z repozytorium znajdujący się na podanym indeksie wektora
    {
        if( this->RepositorySize()-1<index)
            return nullptr;
        else
            return objects[index];
    }
    void add(std::shared_ptr<T> temp)  //metoda dodająca podany obiekt do repozytorium, jeśli nie jest to pusty wskaźnik
    {
        if(temp != nullptr)
            objects.push_back(temp);
    }
    void remove(std::shared_ptr<T> temp)  //metoda usuwająca podany objekt z repozytorium
    {
       // if(temp != nullptr)
       //     objects.erase(std::remove(objects.begin(), objects.end(), temp), objects.end());
        for(unsigned int i = 0; i<this->RepositorySize(); i++)
        {
            if(objects.at(i)==temp)
                objects.erase(objects.begin() + i);
        }
    }
    unsigned int RepositorySize () const  //metoda zwraca liczbę obiektów w repozytorium
    {
        return objects.size();
    }
    std::string Raport() const  //metoda wykorzystuje metody get by zwrócić napis zawierający informacje o wszystkich obiektach repozytorium
    {
        std::string rep;
        int u=objects.size();
        for(int i=0; i<u;i++)
            rep += objects.at(i)->getInfo() + " ";

        return rep ;
    }


};


#endif //WARSZTATY1_REPOSITORY_H
