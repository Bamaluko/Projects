import os
import glob
from PIL import Image
from matplotlib import pyplot, figure
from typing import List
from obiekty.Punkt import Punkt
from obiekty.Centroida import Centroida

def mapa_gaz_neuronowy(lista_centroid: List[Centroida], lista_punktow: List[Punkt], nazwa_pliku: str) -> None:
    figura = figure.Figure()
    wykres = figura.subplots(1)
    wykres.set_aspect('equal')
    wykres.set_xlim(-10, 10)
    wykres.set_ylim(-10, 10)

    for punkt in lista_punktow:
        wykres.plot(punkt.x, punkt.y, color=punkt.kolor, marker='.', markersize=3, alpha=0.7)

    for centroida in lista_centroid:
        wykres.plot(centroida.x, centroida.y, color=centroida.kolor, marker='o', markersize=6, markeredgecolor="black",
                    alpha=0.7)

    figura.savefig(f"{nazwa_pliku}")

def mapa_k_srednich(lista_centroid: List[Centroida], lista_punktow: List[Punkt], nazwa_pliku: str) -> None:
    figura = figure.Figure()
    wykres = figura.subplots(1)
    wykres.set_aspect('equal')

    for punkt in lista_punktow:
        wykres.plot(punkt.x, punkt.y, color=punkt.kolor, marker='.', markersize=4, alpha=0.7)

    for centroida in lista_centroid:
        wykres.plot(centroida.x, centroida.y, color=centroida.kolor, marker='o', markersize=4, markeredgecolor="black")

    figura.savefig(f"{nazwa_pliku}")





def wykres_bledow_gaz_neuronowy(lista: List[float], plik: str, podpisz_os_x: bool = True) -> None:
    if podpisz_os_x:
        pyplot.plot([2, 4, 6, 8, 10, 12, 14, 16, 18, 20], lista, color='yellow', marker='o')
    else:
        pyplot.plot(lista, color='yellow', marker='o')

    pyplot.xlabel("Liczba centroid")
    pyplot.ylabel("Błąd kwantyzacji dla liczby centroid")
    pyplot.savefig(f"{plik}")
    pyplot.clf()

def wykres_bledow_k_srednich(lista: List[float], plik: str, podpisz_os_x: bool = True) -> None:
    if podpisz_os_x:
        pyplot.plot([2, 4, 6, 8, 10, 12, 14, 16, 18, 20], lista, color='yellow', marker='o')
    else:
        pyplot.plot(lista, color='yellow', marker='o')

    pyplot.xlabel("Liczba centroid")
    pyplot.ylabel("Błąd kwantyzacji dla liczby centroid")
    pyplot.savefig(f"{plik}")
    pyplot.clf()





def gaz_neuronowy_foldery(nazwa: str) -> str:
    baza = "wygenerowane_wykresy_i_gify"
    baza_gaz_neuronowy = "wygenerowane_wykresy_i_gify/algorytm_gazu_neuronowego"
    baza_gaz_neuronowy_nazwa = f"wygenerowane_wykresy_i_gify/algorytm_gazu_neuronowego/{nazwa}"

    if os.path.isdir(baza):
        if not os.path.isdir(baza_gaz_neuronowy):
            os.makedirs(baza_gaz_neuronowy)
    else:
        os.makedirs(baza_gaz_neuronowy)

    return baza_gaz_neuronowy_nazwa

def k_srednich_foldery(nazwa: str) -> str:
    baza = "wygenerowane_wykresy_i_gify"
    baza_k_srednich = "wygenerowane_wykresy_i_gify/algorytm_k_srednich"
    baza_k_srednich_nazwa = f"wygenerowane_wykresy_i_gify/algorytm_k_srednich/{nazwa}"

    if os.path.isdir(baza):
        if not os.path.isdir(baza_k_srednich):
            os.makedirs(baza_k_srednich)
    else:
        os.makedirs(baza_k_srednich)

    return baza_k_srednich_nazwa




# Tworzenie gifów ze zdjęć w podanym folderze
def utworz_gif(sciezka_do_folderu: str, nazwa_pliku: str, czas_trwania: int = 300) -> None:
    fp_in = f"{sciezka_do_folderu}/*.png"
    fp_out = f"{sciezka_do_folderu}/../{nazwa_pliku}.gif"
    img, *imgs = [Image.open(f) for f in sorted(glob.glob(fp_in))]
    img.save(fp=fp_out, format='GIF', append_images=imgs, save_all=True, duration=czas_trwania, loop=0)