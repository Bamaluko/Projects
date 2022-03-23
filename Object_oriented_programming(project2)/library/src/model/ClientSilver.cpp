//
// Created by student on 26.04.2021.
//

#include "model/ClientSilver.h"

double ClientSilver::applyDiscount(double price)//podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    price=6;
    return price;
}

int ClientSilver::getMaxVehicles()//zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 3;
}

std::string ClientSilver::getTypeInfo()//metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "Silver";
}