import math
from typing import List


# Po prostu średnia z listy floatów
def srednia_arytmetyczna(liczby: List[float]) -> float:
    suma = 0
    dlugosc = len(liczby)

    for liczba in liczby:
        suma += float(liczba)
    return suma / dlugosc

# Odchylenie standardowe (suma kwadratow odchylen od sredniej dzielona przez ilosc wynikow i spierwiastkowana)
def odchylenie_standardowe(liczby: List[float], srednia: float) -> float:
    suma = 0
    dlugosc = len(liczby)

    for liczba in liczby:
        suma += float(liczba - srednia) ** 2
    return math.sqrt(suma / dlugosc)


# Szukanie minimum
def minimum(liczby: List[float]) -> float:
    min = liczby[0]

    for liczba in liczby:
        if min > liczba:
            min = liczba
    return min
