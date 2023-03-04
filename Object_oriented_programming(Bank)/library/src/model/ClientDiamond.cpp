//
// Created by student on 26.04.2021.
//

#include "model/ClientDiamond.h"

double ClientDiamond::applyDiscount(double price)//podliczenie i zwrócenie zniżki dla typu klient, przyjmowana jako parametr jest końcowa cena uzyskana po zakończeniu danego wypożyczenia
{
    if(price>0 && price<=125)
        price=price*0.1;
    else if(price>125 && price<=250)
        price=price*0.2;
    else if(price>250 && price<=500)
        price=price*0.3;
    else
        price=price*0.4;

    return price;
}

int ClientDiamond::getMaxVehicles()//zwrócenie maksymalnej liczby pojazdów dla danego typu klienta
{
    return 10;
}

std::string ClientDiamond::getTypeInfo()//metoda wykorzystywana jako element dla metody klasy Client getClientInfo, zwraca napis informujący o typie klienta
{
    return "DIAMOND";
}