import math
import numpy
from csv import reader
from matplotlib import pyplot as plt


class DaneZPojedynczymX(object):
    def __init__(self):
        self.nazwa = "nazwa"
        self.X1 = []
        self.Y = []
        self.roznice_w_modelu_1 = []
        self.roznice_w_modelu_2 = []
        self.roznice_w_modelu_3 = []
        self.wartosci_w_modelu_1 = []
        self.wartosci_w_modelu_2 = []
        self.wartosci_w_modelu_3 = []

class DaneZDwomaX(object):
    def __init__(self):
        self.nazwa = "nazwa"
        self.X1 = []
        self.Y = []
        self.roznice_w_modelu_1 = []
        self.roznice_w_modelu_2 = []
        self.wartosci_w_modelu_1 = []
        self.wartosci_w_modelu_2 = []
        self.X2 = []

def wyznaczRoznice(dane):
    dane.roznice_w_modelu_1 = roznica(dane.wartosci_w_modelu_1, dane.Y)
    dane.roznice_w_modelu_2 = roznica(dane.wartosci_w_modelu_2, dane.Y)
    dane.roznice_w_modelu_3 = roznica(dane.wartosci_w_modelu_3, dane.Y)

def wyznaczFunkcje(dane):
    dane.wartosci_w_modelu_1 = utworzFunkcje(macierz_x_model1(dane), regresja(macierz_x_model1(dane), dane.Y))
    dane.wartosci_w_modelu_2 = utworzFunkcje(macierz_x_model2(dane), regresja(macierz_x_model2(dane), dane.Y))
    dane.wartosci_w_modelu_3 = utworzFunkcje(macierz_x_model3(dane), regresja(macierz_x_model3(dane), dane.Y))

def macierz_x_model1(dane):
    return numpy.array([dane.X1]).transpose()

def macierz_x_model2(dane):
    return numpy.array([dane.X1, wyrazWolny(dane.X1)]).transpose()

def macierz_x_model3(dane):
    return numpy.array([potega2(dane.X1), sinus(dane.X1), wyrazWolny(dane.X1)]).transpose()

def wyznaczRoznice_2X(dane):
    dane.roznice_w_modelu_1 = roznica(dane.wartosci_w_modelu_1, dane.Y)
    dane.roznice_w_modelu_2 = roznica(dane.wartosci_w_modelu_2, dane.Y)

def wyznaczFunkcje_2X(dane):
    dane.wartosci_w_modelu_1 = utworzFunkcje(macierz_x_model1_2X(dane), regresja(macierz_x_model1_2X(dane), dane.Y))
    dane.wartosci_w_modelu_2 = utworzFunkcje(macierz_x_model2_2X(dane), regresja(macierz_x_model2_2X(dane), dane.Y))

def macierz_x_model1_2X(dane):
        return numpy.array([dane.X1, dane.X2, wyrazWolny(dane.X1)]).transpose()

def macierz_x_model2_2X(dane):
        return numpy.array([potega2(dane.X1), mnozenie(dane.X1, dane.X2), potega2(dane.X2), dane.X1, dane.X2, wyrazWolny(dane.X1)]).transpose()

#A = (XT X)−1XT Y
def regresja(X, Y):
    return numpy.linalg.inv(X.transpose().dot(X)).dot(X.transpose()).dot(Y)

def roznica(dane1, dane2):
    return list(map(lambda x, y: x - y, dane1, dane2))

def wyrazWolny(lista):
    return list(map(lambda x: 1, lista))

def sinus(lista):
    return list(map(lambda x: math.sin(x), lista))

def potega2(lista):
    return list(map(lambda x: x * x, lista))

def mnozenie(lista1, lista2):
    return list(map(lambda X1, X2: X1 * X2, lista1, lista2))

def utworzFunkcje(X, parametry):
    wartosci = []
    for rzad in X:
        y = 0
        for X, parametr in zip(rzad, parametry):
            y += X * parametr
        wartosci.append(y)
    return wartosci

#fuv = Var(Err)/Var(Y)
def R2(dane1, dane2):
    fuv = wariancja(roznica(dane1, dane2)) / wariancja(dane2)
    return 1 - fuv

def kowariancja(X, Y):
    razem = 0
    for i in range(len(X)):
        razem += (X[i] - numpy.mean(X)) * (Y[i] - numpy.mean(Y))
    return razem/len(X)

def wariancja(dane):
    return kowariancja(dane, dane)

def kwadrat_sredniej_roznicy(roznice):
    return sum(value*value for value in roznice) / len(roznice)

def max_roznica(roznice):
    roznice.sort()
    if(roznice[0]*roznice[0] > roznice[-1]*roznice[-1]):
        return roznice[0]
    else:
        return roznice[-1]

def rozwiazanie1(dane):
    print("----------------------------------------------------------------------------------")
    print("model 1: aX")
    print("Parametry funkcji: ", regresja(macierz_x_model1(dane), dane.Y))
    print("Wartosc R2: ", R2(dane.wartosci_w_modelu_1, dane.Y))
    print("Srednia roznica^2: ",kwadrat_sredniej_roznicy(dane.roznice_w_modelu_1))
    print("Najwieksza roznica: ", max_roznica(dane.roznice_w_modelu_1))


def rozwiazanie2(dane):
    print("----------------------------------------------------------------------------------")
    print("model 2: aX + b")
    print("Parametry funkcji: ", regresja(macierz_x_model2(dane), dane.Y))
    print("Wartosc R2: ", R2(dane.wartosci_w_modelu_2, dane.Y))
    print("Srednia roznica^2: ", kwadrat_sredniej_roznicy(dane.roznice_w_modelu_2))
    print("Najwieksza roznica: ", max_roznica(dane.roznice_w_modelu_2))


def rozwiazanie3(dane):
    print("----------------------------------------------------------------------------------")
    print("model 3: aX^2 + bsin(X) + C")
    print("Parametry funkcji: ", regresja(macierz_x_model3(dane), dane.Y))
    print("Wartosc R2: ", R2(dane.wartosci_w_modelu_3, dane.Y))
    print("Srednia roznica^2: ",kwadrat_sredniej_roznicy(dane.roznice_w_modelu_3))
    print("Najwieksza roznica: ", max_roznica(dane.roznice_w_modelu_3))

def Wykres2D(dane, wartosci, roznice, nazwa):
    fig = plt.figure(nazwa)
    plot1 = plt.subplot(1, 2, 1)
    plot2 = plt.subplot(1, 2, 2)
    plot1.plot(dane.X1, dane.Y, '.b')
    plot1.plot(dane.X1, wartosci, 'red')
    plot2.hist(roznice)
    plt.show()

def wykres3D(dane, wartosci, nazwa):
    fig = plt.figure(nazwa)
    X1 = numpy.array(dane.X1)
    X2 = numpy.array(dane.X2)
    Y = numpy.array(wartosci)

    plot1 = fig.add_subplot(2, 2, 1, projection='3d')
    plot2 = fig.add_subplot(2, 2, 2, projection='3d')
    plot3 = fig.add_subplot(2, 2, 3)

    plot1.scatter(X1, X2, dane.Y, cmap='Blues')
    plot1.scatter(X1, X2, Y, cmap='Reds')
    plot2.plot_trisurf(X1, X2, dane.Y, cmap='Blues')
    plot2.plot_trisurf(X1, X2, Y, cmap='Reds')
    plot3.hist(roznica(Y, dane.Y))
    plt.show()

def rozwiazanie4(dane):
    print("----------------------------------------------------------------------------------")
    print("model 1: aX1 + bX2 + c")
    print("Parametry funkcji: ", regresja(macierz_x_model1_2X(dane), dane.Y))
    print("Wartosc R2: ", R2(dane.wartosci_w_modelu_1, dane.Y))
    print("Srednia roznica^2: ",kwadrat_sredniej_roznicy(dane.roznice_w_modelu_1))
    print("Najwieksza roznica: ", max_roznica(dane.roznice_w_modelu_1))

def rozwiazanie5(dane):
    print("----------------------------------------------------------------------------------")
    print("model 2: aX1^2 + bX1X2 + cX2^2 + dX1 + eX2 + f")
    print("Parametry funkcji: ", regresja(macierz_x_model2_2X(dane), dane.Y))
    print("Wartosc R2: ", R2(dane.wartosci_w_modelu_2, dane.Y))
    print("Srednia roznica^2: ",kwadrat_sredniej_roznicy(dane.roznice_w_modelu_2))
    print("Najwieksza roznica: ", max_roznica(dane.roznice_w_modelu_2))




print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print("***dane1***")
dane1 = DaneZPojedynczymX()
file = open('data1.csv')
dane1.nazwa = 'dane1'
for row in reader(file):
    dane1.X1.append(float(row[0]))
    dane1.Y.append(float(row[1]))
file.close()
wyznaczFunkcje(dane1)
wyznaczRoznice(dane1)
rozwiazanie1(dane1)
Wykres2D(dane1, dane1.wartosci_w_modelu_1, dane1.roznice_w_modelu_1, "DANE1 MODEL1")
rozwiazanie2(dane1)
Wykres2D(dane1, dane1.wartosci_w_modelu_2, dane1.roznice_w_modelu_2, "DANE1 MODEL2")
rozwiazanie3(dane1)
Wykres2D(dane1, dane1.wartosci_w_modelu_3, dane1.roznice_w_modelu_3, "DANE1 MODEL3")


print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print("***dane2***")
dane2 = DaneZPojedynczymX()
file = open('data2.csv')
dane1.nazwa = 'dane2'
for row in reader(file):
    dane2.X1.append(float(row[0]))
    dane2.Y.append(float(row[1]))
file.close()
wyznaczFunkcje(dane2)
wyznaczRoznice(dane2)
rozwiazanie1(dane2)
Wykres2D(dane2, dane2.wartosci_w_modelu_1, dane2.roznice_w_modelu_1, "DANE2 MODEL1")
rozwiazanie2(dane2)
Wykres2D(dane2, dane2.wartosci_w_modelu_2, dane2.roznice_w_modelu_2, "DANE2 MODEL2")
rozwiazanie3(dane2)
Wykres2D(dane2, dane2.wartosci_w_modelu_3, dane2.roznice_w_modelu_3, "DANE2 MODEL3")

print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print("***dane3***")
file = open("data3.csv")
dane3 = DaneZDwomaX()
dane3.name = "dane3"
for row in reader(file):
    dane3.X1.append(float(row[0]))
    dane3.X2.append(float(row[1]))
    dane3.Y.append(float(row[2]))
file.close()
wyznaczFunkcje_2X(dane3)
wyznaczRoznice_2X(dane3)
rozwiazanie4(dane3)
wykres3D(dane3, dane3.wartosci_w_modelu_1, "DANE3 MODEL1")
rozwiazanie5(dane3)
wykres3D(dane3, dane3.wartosci_w_modelu_2, "DANE3 MODEL2")

print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print("***dane4***")
file = open("data4.csv")
dane4 = DaneZDwomaX()
dane4.name = "dane4"
for row in reader(file):
    dane4.X1.append(float(row[0]))
    dane4.X2.append(float(row[1]))
    dane4.Y.append(float(row[2]))
file.close()
wyznaczFunkcje_2X(dane4)
wyznaczRoznice_2X(dane4)
rozwiazanie4(dane4)
wykres3D(dane4, dane4.wartosci_w_modelu_1, "DANE4 MODEL1")
rozwiazanie5(dane4)
wykres3D(dane4, dane4.wartosci_w_modelu_2, "DANE4 MODEL2")
