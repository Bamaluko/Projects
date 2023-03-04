//
// Created by student on 26.04.2021.
//

#include "model/ClientBronze.h"

double ClientBronze::applyDiscount(double price) //podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    price=3;
    return price;
}

int ClientBronze::getMaxVehicles()   //zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 2;
}

std::string ClientBronze::getTypeInfo()  //metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "BRONZE";
}