//
// Created by student on 26.04.2021.
//

#include "model/ClientDefault.h"

double ClientDefault::applyDiscount(double price) //podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    price=0;
    return price;
}

int ClientDefault::getMaxVehicles()//zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 1;
}

std::string ClientDefault::getTypeInfo()//metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "DEFAULT";
}

ClientDefault::~ClientDefault() {

}
