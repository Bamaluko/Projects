from random import randint
from scipy.spatial import distance


class Centroida:
    def __init__(self, x: int, y: int):
        self.indeks = -1
        self.x = x
        self.y = y
        self.kolor = self.generuj_kolor()
        self.odleglosc = 0
        self.aktywna = True

    # Generujemy losowy kolor dla centroidy
    @staticmethod
    def generuj_kolor() -> str:
        rand = lambda: randint(0, 255)
        return '#%02X%02X%02X' % (rand(), rand(), rand())

    # Podmieniamy współrzędne
    def zmien_polozenie(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    # Odległość euklidesowa między tym punktem a innym obliczona za pomocą funkcji distance.euclidean
    def oblicz_odleglosc(self, punkt) -> None:
        self.odleglosc = distance.euclidean((self.x, self.y), (punkt.x, punkt.y))

    # Deaktywacja centroidy
    def wylacz(self) -> None:
        self.aktywna = False

    # Aktywacja centroidy
    def wlacz(self) -> None:
        self.aktywna = True

    # Nadanie indeksu dla centroidy
    def nadaj_indeks(self, indeks: int) -> None:
        self.indeks = indeks

    # Przesuwanie na kazdej osi o odleglosc miedzy wspolrzednymi punktow pomnozona przez wspolczynnik przesuniecia
    def przesun(self, x: int, y: int, wspolczynnik_przesuniecia: float) -> None:
        self.x += (x - self.x) * wspolczynnik_przesuniecia
        self.y += (y - self.y) * wspolczynnik_przesuniecia

