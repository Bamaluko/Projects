//
// Created by student on 26.04.2021.
//

#include "model/ClientPlatinum.h"

double ClientPlatinum::applyDiscount(double price)//podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    price=price*0.1;
    return price;
}

int ClientPlatinum::getMaxVehicles()//zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 5;
}

std::string ClientPlatinum::getTypeInfo()//metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "PLATINUM";
}