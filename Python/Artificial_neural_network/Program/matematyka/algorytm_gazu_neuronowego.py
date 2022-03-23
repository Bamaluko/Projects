import operator
from random import uniform, shuffle
from typing import List
from cmath import e
from os import makedirs
from wykresy.wykresy import mapa_gaz_neuronowy, wykres_bledow_gaz_neuronowy, gaz_neuronowy_foldery, utworz_gif
from matematyka.obliczenia import srednia_arytmetyczna, odchylenie_standardowe, minimum
from matematyka.losowanie_neuronow import losowanie_neuronow_1_okrag, losowanie_neuronow_2_okregi
from obiekty.Centroida import Centroida
from obiekty.Punkt import Punkt

# Zmienne potrzebne przy obliczeniach
epsilon = 10 ** (-10)
lambda1 = 1.5


# Utworzenie wymaganej ilosci centroid
def utworz_centroidy(ilosc: int) -> List[Centroida]:
    centroidy = []
    for indeks in range(ilosc):
        centroidy.append(Centroida(int(uniform(-10, 10)), int(uniform(-10, 10))))
    return centroidy


# Nadanie indeksow stworzonym centroidom
def indexy_dla_centroid(punkt: Punkt, centroidy: List[Centroida]) -> None:
    # Dla podanego punktu obliczamy odleglosc od kazdej centroidy
    for centroida in centroidy:
        centroida.oblicz_odleglosc(punkt)

    # Posortowanie centroid wedlugo odleglosci od badanego punktu
    centroidy.sort(key=operator.attrgetter("odleglosc"))

    # Przypisywanie indeksów według kolejności z posortowanej listy
    i: int = 1
    for centroida in centroidy:
        centroida.nadaj_indeks(i)
        i += 1


# Znajdowanie najbliższej centroidy dla podanego punktu
def najblizsza_centroida(punkt: Punkt, centroidy: List[Centroida]) -> Centroida:
    for centroida in centroidy:
        centroida.oblicz_odleglosc(punkt)
    return min(centroidy, key=operator.attrgetter("odleglosc"))


# Przesuwanie centroidy w stronę podanego punktu o obliczoną odległość
def przemieszczenie_centroidy(centroida: Centroida, punkt: Punkt) -> None:
    centroida.przesun(punkt.x, punkt.y, alfa * (e ** (-centroida.indeks / (2 * lambda1))))


# Obliczanie błędu kwantyzacji na podstawie listy punktów i listy centroid
def blad_kwantyzacji(punkty_list: List[Punkt], centroidy_list: List[Centroida]) -> float:
    suma = 0
    for punkt in punkty_list:
        punkt.dobierz_centroide(najblizsza_centroida(punkt, centroidy_list))
        suma += punkt.odleglosc

    return suma / len(punkty_list)





# GLOWNA FUNKCJA ALGORYTMU
def gaz_nuronowy_main(dwa_okregi: bool, folder: str) -> None:
    # Tworzenie struktury katalogowej
    sciezka_folderu = gaz_neuronowy_foldery(folder)

    # Lista bledow na koniec dzialania algorytmu
    bledy_finalne = []

    # WYKRES
    # Ustalamy ilość kregów dla algorytmu (wariant z jednym lub dwoma)
    if dwa_okregi:
        punkty = losowanie_neuronow_2_okregi()
    else:
        punkty = losowanie_neuronow_1_okrag()

    # Lista zawierajaca ilosci nieaktywnych centroid w danym momencie
    nieaktywnych_centroid = []

    # Zmieniamy co 2 ilosc centroid w przedziale <2, 20>
    for ilosc_centroid in range(2, 22, 2):
        # Kontynuacja tworzenia struktury katalogu
        folder_liczba_centroid = f"centroidy_{ilosc_centroid}"
        sciezka_dla_centroid = f"{sciezka_folderu}/{folder_liczba_centroid}"
        makedirs(f"{sciezka_folderu}/{folder_liczba_centroid}")

        # Wypelniamy liste centroid
        centroidy = utworz_centroidy(ilosc_centroid)

        # Kazdemu punktowi dopasowujemy centroide, ktora jest dla niego najblizsza
        for punkt in punkty:
            punkt.dobierz_centroide(najblizsza_centroida(punkt, centroidy))

        # Iterator sprawdzajacy ile testow udalo sie juz przeprowadzic
        iterator = 0
        # Pierwsze dwa elementy potrzebne dla spelnienia warunku (w koncowym rozrachunku sa nieistotne)
        bledy = [100, 50]

        # Otwieramy pętle, która będzie działała dopóki warunek nie będzie większy do epsilonu
        while True:
            # Na poczatku kolejnosc punktow musi zostac pomieszana
            shuffle(punkty)

            # Iterujemy po wszystkich punktach
            for punkt in punkty:
                # Ścieżka do wykresu
                if iterator < 9:
                    numer_wykresu = f"0{iterator + 1}"
                else:
                    numer_wykresu = f"{iterator + 1}"
                sciezka_wykres = f"{sciezka_dla_centroid}/wykres_{numer_wykresu}"

                # Warunek pozwalajacy na kontynuacje dzialania
                if (bledy[-2] - bledy[-1]) / bledy[-1] >= epsilon:
                    # Jezeli to nie koniec, to tworzymy mape przedstawiajaca polozenie punktow i centroid,
                    # robimy to co okreslona ilosc, zeby nie przegiac z iloscia map
                    if iterator % 3 == 0:
                        mapa_gaz_neuronowy(centroidy, punkty, sciezka_wykres)

                    # Wszystkie centroidy dostaja ponowny przydzial indeksow
                    indexy_dla_centroid(punkt, centroidy)

                    # Nastepuje przemieszczenie centroid w kierunku danego punktu
                    for centroida in centroidy:
                        przemieszczenie_centroidy(centroida, punkt)

                    # blad kwantyzacji zostaje dopisany do odpowiedniej listy
                    blad = blad_kwantyzacji(punkty, centroidy)
                    bledy.append(blad)

                    # Zwiekszamy iterator o 1
                    iterator += 1
                else:
                    # Jesli wartosc (lista_bledow[-2] - lista_bledow[-1]) / lista_bledow[-1] jest mniejsza niz
                    # epsilon, to pora na narysowanie ostatniej mapy i przerwanie petli
                    mapa_gaz_neuronowy(centroidy, punkty, sciezka_wykres)
                    break
            break

        # Lista bledow po zakonczeniu dzialania algorytmu zostaje poszerzona o odpowiednia wartosc
        bledy_finalne.append(bledy[-1])

        # Jeżeli ilość punktów, do których przesuwaliśmy centroidy jest mniejsza od ich łącznej ilości
        # to pozostałą ilość punktów przypisujemy do listy nieaktywnych punktów
        if iterator < len(punkty):
            nieaktywnych_centroid.append(len(punkty) - iterator)
        else:
            nieaktywnych_centroid.append(0)

        # Z powstalych obrazow generowany jest GIF
        utworz_gif(sciezka_dla_centroid, folder_liczba_centroid)

    # Z finalnych bledow powstaje wykres
    wykres_bledow_gaz_neuronowy(bledy_finalne, f"{sciezka_folderu}/koncowe_bledy_WYKRESY")

    # Podsumowanie dla wykresów
    print("+++ Dane_do_wykresów +++")
    print(f"ALFA={alfa}")
    print(f"LAMBDA={lambda1}")
    print("Lista błędow końcowych:")
    print(bledy_finalne)
    print(f"Ilość nieaktywnych neuronow:")
    print(nieaktywnych_centroid)

    print("\n\n")




    # Puste listy z błędami i ilościami nieaktywnych punktów
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
        centroidy = utworz_centroidy(20)

        # Iterator sprawdzajacy ile testow udalo sie juz przeprowadzic
        iterator = 0
        # Pierwsze dwa elementy potrzebne dla spelnienia warunku (w koncowym rozrachunku sa nieistotne)
        bledy = [100, 50]

        # Otwieramy pętle, która będzie działała dopóki warunek nie będzie większy od epsilonu
        while True:
            # Mieszamy listę z punktami
            shuffle(punkty)

            # Iterujemy po wszystkich punktach
            for punkt in punkty:
                # Sprawdzamy warunek
                if (bledy[-2] - bledy[-1]) / bledy[-1] >= epsilon:
                    # Przypisujemy indeksy wszystkim centroidom
                    indexy_dla_centroid(punkt, centroidy)

                    # Przesuwamy wszystkie centroidy do danego punktu
                    for centroida in centroidy:
                        przemieszczenie_centroidy(centroida, punkt)

                    # Obliczamy i dodajemy błąd do listy wszystkich błędów
                    blad = blad_kwantyzacji(punkty, centroidy)
                    bledy.append(blad)

                    # Inkrementujemy licznik
                    iterator += 1
                else:
                    break
            break

        # Dodajemy ostatni błąd do listy ostatnich błędów
        bledy_finalne.append(bledy[-1])

        # Jeżeli ilość punktów, do których przesuwaliśmy centroidy jest mniejsza od ich łącznej ilości
        # to pozostałą ilość punktów przypisujemy do listy nieaktywnych punktów
        if iterator < len(punkty):
            nieaktywnych_centroid.append(len(punkty) - iterator)
        else:
            nieaktywnych_centroid.append(0)

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

    # Robimy wykres błędów
    wykres_bledow_gaz_neuronowy(bledy_finalne, f"{sciezka_folderu}/koncowe_bledy_TABELE", False)

    # Podsumowanie
    srednia_bledy = srednia_arytmetyczna(bledy_finalne)
    odchylenie_bledy = odchylenie_standardowe(bledy_finalne, srednia_bledy)
    wartosc_minimalna_bledy = minimum(bledy_finalne)

    srednia_neurony = srednia_arytmetyczna(nieaktywnych_centroid)
    odchylenie_neurony = odchylenie_standardowe(nieaktywnych_centroid, srednia_neurony)

    print("\n\n")
    print("+++ Dane_do_tabeli +++")
    print(f"ALFA={alfa}")
    print(f"LAMBDA={lambda1}")
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




# FUNKCJA STERUJACA (uzywana w main)
def gaz_neuronowy():
    global alfa

    alfa = 0.05
    gaz_nuronowy_main(False, f"jeden_okrag_alfa_{round(alfa, 3)}_lamba_{lambda1}")
    gaz_nuronowy_main(True, f"dwa_okregi_alfa_{round(alfa, 3)}_lamba_{lambda1}")

    alfa = 0.1
    gaz_nuronowy_main(False, f"jeden_okrag_alfa_{round(alfa, 3)}_lamba_{lambda1}")
    gaz_nuronowy_main(True, f"dwa_okregi_alfa_{round(alfa, 3)}_lamba_{lambda1}")

    alfa = 0.3
    gaz_nuronowy_main(False, f"jeden_okrag_alfa_{round(alfa, 3)}_lamba_{lambda1}")
    gaz_nuronowy_main(True, f"dwa_okregi_alfa_{round(alfa, 3)}_lamba_{lambda1}")

    alfa = 0.6
    gaz_nuronowy_main(False, f"jeden_okrag_alfa_{round(alfa, 3)}_lamba_{lambda1}")
    gaz_nuronowy_main(True, f"dwa_okregi_alfa_{round(alfa, 3)}_lamba_{lambda1}")
