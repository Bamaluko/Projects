import operator
from typing import List
from os import makedirs
from random import  choice

from matematyka.obliczenia import srednia_arytmetyczna, odchylenie_standardowe, minimum
from obiekty.Centroida import Centroida
from obiekty.Punkt import Punkt
from wykresy.wykresy import mapa_k_srednich, wykres_bledow_k_srednich, k_srednich_foldery, utworz_gif
from matematyka.losowanie_neuronow import losowanie_neuronow_1_okrag, losowanie_neuronow_2_okregi

# Wartość epsilon używana w obliczeniach
epsilon = 10 ** (-5)


# Wybieramy losowy punkt i przyjmujemy go jako centroidę
def utworz_centroidy(liczba_centroid: int, punkty: List[Punkt]) -> List[Centroida]:
    centroidy = []
    for i in range(liczba_centroid):
        punkt = choice(punkty)
        centroidy.append(Centroida(punkt.x, punkt.y))
    return centroidy


# Szukamy najbliższej centroidy dla podanego punktu
def najblizsza_centroida(punkt: Punkt, centroidy: List[Centroida]) -> Centroida:
    for centroida in centroidy:
        centroida.oblicz_odleglosc(punkt)
    return min(centroidy, key=operator.attrgetter("odleglosc"))


# Znajdujemy srodek ciezkosci
def srodek_ciezkosci(centroida: Centroida, punkty: List[Punkt]):
    iterator = 0
    x_razem = 0
    y_razem = 0
    for punkt in punkty:
        if punkt.centroida == centroida:
            x_razem += punkt.x
            y_razem += punkt.y
            iterator += 1

    if iterator != 0:
        return x_razem / iterator, y_razem / iterator
    else:
        centroida.wylacz()
        return 2, 2


# Wyznaczamy błąd kwantyzacji
def blad_kwantyzacji(punkty: List[Punkt]) -> float:
    odleglosci = 0
    for punkt in punkty:
        odleglosci += punkt.odleglosc

    return odleglosci / len(punkty)





# GLOWNA FUNKCJA ALGORYTMU
def k_srednich_main(dwa_okregi: bool, folder: str) -> None:
    # Tworzymy folder, w którym będą zapisywane wszystkie wykresy
    sciezka_folderu = k_srednich_foldery(folder)

    # Lista bledow na koniec dzialania algorytmu
    bledy_finalne = []

    # WYKRES
    # Ustalamy ilość kregów dla algorytmu (wariant z jednym lub dwoma)
    if dwa_okregi:
        punkty = losowanie_neuronow_2_okregi()
    else:
        punkty = losowanie_neuronow_1_okrag()

    # Zmieniamy co 2 ilosc centroid w przedziale <2, 20>
    for ilosc_centroid in range(2, 22, 2):
        # Kontynuacja tworzenia struktury katalogu
        folder_liczba_centroid = f"centroidy_{ilosc_centroid}"
        sciezka_dla_centroid = f"{sciezka_folderu}/{folder_liczba_centroid}"
        makedirs(f"{sciezka_folderu}/{folder_liczba_centroid}")

        # # Wypelniamy liste centroid
        centroidy = utworz_centroidy(ilosc_centroid, punkty)

        # Iterator sprawdzajacy ile testow udalo sie juz przeprowadzic
        iterator = 1
        # Pierwsze dwa elementy potrzebne dla spelnienia warunku (w koncowym rozrachunku sa nieistotne)
        bledy = [100, 50]

        # Otwieramy pętle.Warunek zakończenia: wartość będzie mniejsza od epsilonu bądź iterator większy lub równy 50
        while (bledy[-2] - bledy[-1]) / bledy[-1] >= epsilon and iterator < 50:
            # Przypisanie każdemu punktowi odpowiedniej centroidy
            for punkt in punkty:
                punkt.dobierz_centroide(najblizsza_centroida(punkt, centroidy))

            # Ścieżka do wykresu
            if iterator < 9:
                numer_wykresu = f"0{iterator + 1}"
            else:
                numer_wykresu = f"{iterator + 1}"
            sciezka_wykres = f"{sciezka_dla_centroid}/wykres_{numer_wykresu}"

            # Tworzymy mapę punktów
            mapa_k_srednich(centroidy, punkty, sciezka_wykres)

            # Dodajemy aktualny błąd do listy wszystkich błędów
            bledy.append(blad_kwantyzacji(punkty))

            # Zależnie od środka ciężkości położenie każdej centroidy jest zmieniane
            for centroida in centroidy:
                if centroida.aktywna:
                    x, y = srodek_ciezkosci(centroida, punkty)
                    centroida.zmien_polozenie(x, y)

            iterator += 1

        # Gdy jeden z warunków jest niespełniony, rysujemy finałowy wykres
        mapa_k_srednich(centroidy, punkty, f"{sciezka_dla_centroid}/wykres_{iterator + 1}")

        # Ostatni błąd na liście błędów jest dodawanych do listy błędów finalnych
        bledy_finalne.append(bledy[-1])

        # GIF
        utworz_gif(sciezka_dla_centroid, folder_liczba_centroid)

    # Wykres błędów finalnych
    wykres_bledow_k_srednich(bledy_finalne, f"{sciezka_folderu}/koncowe_bledy_WYKRESY")

    # Podsumowanie
    print("+++ Dane_do_wykresów +++")
    print("Błędy finalne zależnie od liczby centrów:")
    print(bledy_finalne)

    print("\n\n")

    # TABELE
    # Lista na błędy_finalne i ilość nieaktywnych punktów
    bledy_finalne = []
    nieaktywnych_centroid = []

    # 100 prób nauki
    for i in range(100):
        # Ustalamy ilosc okregow
        if dwa_okregi:
            punkty = losowanie_neuronow_2_okregi()
        else:
            punkty = losowanie_neuronow_1_okrag()

        # Tworzymy centroidy
        centroidy = utworz_centroidy(20, punkty)

        # Iterator sprawdzajacy ile testow udalo sie juz przeprowadzic
        iterator = 0
        # Pierwsze dwa elementy potrzebne dla spelnienia warunku (w koncowym rozrachunku sa nieistotne)
        bledy = [100, 50]

        # Otwieramy pętle.Warunek zakończenia: wartość będzie mniejsza od epsilonu bądź iterator większy lub równy 50
        while ((bledy[-2] - bledy[-1]) / bledy[-1] >= epsilon and iterator < 50):
            # Przypisanie każdemu punktowi odpowiedniej centroidy
            for punkt in punkty:
                punkt.dobierz_centroide(najblizsza_centroida(punkt, centroidy))

            # Dopisujemy aktualny błąd do listy błędów
            bledy.append(blad_kwantyzacji(punkty))

            # Zależnie od środka ciężkości położenie każdej centroidy jest zmieniane
            for centroida in centroidy:
                if centroida.aktywna:
                    x, y = srodek_ciezkosci(centroida, punkty)
                    centroida.zmien_polozenie(x, y)

            iterator += 1

        # Przyjmujemy, że mam 0 nieaktywnych centroid (początkowo)
        ilosc_nieaktywnych = 0

        # Jeżeli jakieś centroidy są nieaktywne to dodajemy
        for centroida in centroidy:
            if not centroida.aktywna:
                ilosc_nieaktywnych += 1

        # Dopisujemy aktualną ilość nieaktywnych centroid
        nieaktywnych_centroid.append(ilosc_nieaktywnych)

        # Błąd finalny zostaje dopisany do odpowiedniej listy
        bledy_finalne.append(bledy[-1])

        # Pasek postepu
        if i % 10 == 0:
            z: int = 0
            napis: str = "|"
            while z < 10:
                if i >= 10*z:
                    napis += "#"
                else:
                    napis += " "
                z += 1
            napis += "|"
            print(napis)

    # Wykres finalnych błędów
    wykres_bledow_k_srednich(bledy_finalne, f"{sciezka_folderu}/koncowe_bledy_TABELE", False)

    # Podsumowanie
    srednia_bledy = srednia_arytmetyczna(bledy_finalne)
    odchylenie_bledy = odchylenie_standardowe(bledy_finalne, srednia_bledy)
    wartosc_minimalna_bledy = minimum(bledy_finalne)

    srednia_neurony = srednia_arytmetyczna(nieaktywnych_centroid)
    odchylenie_neurony = odchylenie_standardowe(nieaktywnych_centroid, srednia_neurony)

    print("\n\n")
    print("+++ Dane_do_tabeli +++")
    print("Końcowe błędy:")
    print(bledy_finalne)
    print(f"Ilości nieaktywnych neuronów:")
    print(nieaktywnych_centroid)
    print(f"Średni błąd kwantyzacji: {srednia_bledy}")
    print(f"Minimalny błąd kwantyzacji: {wartosc_minimalna_bledy}")
    print(f"Odchylenie standardowe dla błędów kwantyzacji: {odchylenie_bledy}")
    print(f"Średnia ilość nieaktywnych neuronów: {srednia_neurony}")
    print(f"Odchylenie standardowe dla nieaktywnych neuronów: {odchylenie_neurony}")

    print("\n\n")


# Główna funkcja do użycia w main.py
def k_srednich():
    k_srednich_main(False, "jeden_okrag")
    k_srednich_main(True, "dwa_okregi")
