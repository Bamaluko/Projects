from scipy.spatial import distance


class Punkt:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
        self.kolor = 'black'
        # Centroida przypisana do danego punktu:
        self.centroida = None
        self.odleglosc = 0

    # Przypisywanie koloru
    def przypisz_kolor(self, kolor: str) -> None:
        self.kolor = kolor

    # Gdy znajdziemy najblizsza centroide, przypisujemy ja do punktu, obliczamy jej odleglosc od punktu, a takze nadajemy punktowi kolor odpowiadajacy centroidzie
    def dobierz_centroide(self, centroida) -> None:
        self.centroida = centroida
        self.odleglosc_punt_centroida(centroida.x, centroida.y)
        self.przypisz_kolor(centroida.kolor)

    # Obliczamy odleglosc euklidesowa miedzy punktem, a centrodia za pomoca funkcji distance.euclidean
    def odleglosc_punt_centroida(self, x: int, y: int) -> None:
        self.odleglosc = distance.euclidean((self.x, self.y), (x, y))

