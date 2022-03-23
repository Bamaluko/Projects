//
// Created by student on 26.04.2021.
//

#include "model/ClientGold.h"

double ClientGold::applyDiscount(double price)//podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    return price*0.05;
}

int ClientGold::getMaxVehicles()//zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 4;
}

std::string ClientGold::getTypeInfo()//metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "GOLD";
}