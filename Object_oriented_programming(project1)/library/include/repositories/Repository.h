//
// Created by student on 01.06.2021.
//

#ifndef BANK_REPOSITORY_H
#define BANK_REPOSITORY_H
#include <memory>
#include <string>
#include <vector>

template<class T> class Repository
{
protected:
    std::vector<std::shared_ptr<T>> objects;
public:
    std::shared_ptr<T> get(unsigned int index)  //getter pozwalający uzyskać obiekt z repozytorium (obiekt na indeksie 0 uzyskujemy podając cyfrę 1, pierwszy obiekt)
    {
        if( this->size()<=index)
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
        for(unsigned int i = 0; i<this->size(); i++)
        {
            if(objects.at(i)==temp)
                objects.erase(objects.begin() + i);
        }
    }

    unsigned int size () const  //metoda zwraca liczbę obiektów w repozytorium
    {
        return objects.size();
    }

    std::string report() const  //metoda wykorzystuje metody get by zwrócić napis zawierający informacje o wszystkich obiektach repozytorium
    {
        std::string rep;
        for(unsigned int i=0; i<objects.size();i++)
            rep += objects.at(i)->getInfo() + "\n";

        return rep ;
    }




};
#endif //BANK_REPOSITORY_H
