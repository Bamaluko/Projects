import csv
import math

class flowers:
    def __init__(self, sepal_length, sepal_width, petal_length, petal_width, species):
        self.sepal_length = sepal_length
        self.sepal_width = sepal_width
        self.petal_length = petal_length
        self.petal_width = petal_width
        self.species = species

def minimum(list2):
    minimum = list2[0]
    for value in list2:
        if minimum > value:
            minimum = value
    return minimum

def maksimum(list2):
    maksimum = list2[0]
    for value in list2:
        if maksimum < value:
            maksimum = value
    return maksimum

def srednia(list2, d):
    suma = 0
    for value in list2:
        suma += float(value)
    suma = suma/d
    return suma
    
def odchylenie(X, list2, d):
    suma = 0
    for value in list2:
        suma += (float(value) - X)*(float(value) - X)
    suma = suma/(d-1)
    suma = math.sqrt(suma)
    return suma

def mediana(list,d):
    list.sort()
    if d%2==0:
        x=int(d/2)
        return (float(list[x])+float(list[x-1]))/2
    else:
        x=int(d/2 + 0.5)
        return float(list[x])


list1 = []

with open('data.csv') as csvfile:
    csvReader = csv.reader(csvfile, delimiter=',')
    for row in csvReader:
        list1.append(flowers(row[0], row[1], row[2], row[3], row[4]))

print("------------------------------------------------------------------------------")
print("Rozpoczynam obliczenia")
print("------------------------------------------------------------------------------")
a = 0
b = 0
c = 0
for object in list1:
    if object.species == '0':
        a += 1
    elif object.species == '1':
        b += 1
    elif object.species == '2':
        c += 1
d=a+b+c
print("Wystepowanie gatunku setosa: " + str(a) + "        Procentowo: " + str("%.2f" % (a / d * 100)))
print("Wystepowanie gatunku versicolor: " + str(b) + "    Procentowo: " + str("%.2f" % (b / d * 100)))
print("Wystepowanie gatunku virginica: " + str(c) + "     Procentowo: " + str("%.2f" % (c / d * 100)))
print("Wszystkich : " + str(d) + "                       Procentowo: 100.00")
print("------------------------------------------------------------------------------")
print("Obliczenia dla długości działki kielicha: ")
list2 = []
for object in list1:
    list2.append(object.sepal_length)

list2.sort()

print("Najmniejsza wartość: " + str(minimum(list2)))
print("Średnia  arytmetyczna i odchylenie standardowe: " + str("%.2f" % srednia(list2, d)) + "(" + str("%.2f" % odchylenie(srednia(list2, d), list2,d)) + ")")
list3 = []
i=0
while i<d/2:
    list3.append(list2[i])
    i += 1
list4 = []
i=0
while i<d/2:
    list4.append(list2[d-i-1])
    i+=1
print("Mediana Q2(Q1-Q3): " + str(mediana(list2, d)) + "(" + str(mediana(list3, 75)) + " - " + str(mediana(list4, 75)) + ")")
print("Najwieksza wartość: " + str(maksimum(list2)))
print("------------------------------------------------------------------------------")
print("Obliczenia dla szerokości działki kielicha: ")
list2 = []
for object in list1:
    list2.append(object.sepal_width)

list2.sort()

print("Najmniejsza wartość: " + str(minimum(list2)))
print("Średnia  arytmetyczna i odchylenie standardowe: " + str("%.2f" % srednia(list2, d)) + "(" + str("%.2f" % odchylenie(srednia(list2, d), list2,d)) + ")")
list3 = []
i=0
while i<d/2 + 1:
    list3.append(list2[i])
    i += 1
list4 = []
i=0
while i<d/2 + 1:
    list4.append(list2[d-i-1])
    i+=1
print("Mediana Q2(Q1-Q3): " + str(mediana(list2, d)) + "(" + str("%.2f" % mediana(list3, len(list3))) + " - " + str("%.2f" % mediana(list4, len(list4))) + ")")
print("Najwieksza wartość: " + str(maksimum(list2)))
print("------------------------------------------------------------------------------")
print("Obliczenia dla długości platka: ")
list2 = []
for object in list1:
    list2.append(object.petal_length)

list2.sort()

print("Najmniejsza wartość: " + str(minimum(list2)))
print("Średnia  arytmetyczna i odchylenie standardowe: " + str("%.2f" % srednia(list2, d)) + "(" + str("%.2f" % odchylenie(srednia(list2, d), list2,d)) + ")")
list3 = []
i=0
while i<d/2 + 1:
    list3.append(list2[i])
    i += 1
list4 = []
i=0
while i<d/2 + 1:
    list4.append(list2[d-i-1])
    i+=1
print("Mediana Q2(Q1-Q3): " + str(mediana(list2, d)) + "(" + str("%.2f" % mediana(list3, 75)) + " - " + str("%.2f" % mediana(list4, 75)) + ")")
print("Najwieksza wartość: " + str(maksimum(list2)))
print("------------------------------------------------------------------------------")
print("Obliczenia dla szerokosci płatka: ")
list2 = []
for object in list1:
    list2.append(object.petal_width)

list2.sort()

print("Najmniejsza wartość: " + str(minimum(list2)))
print("Średnia  arytmetyczna i odchylenie standardowe: " + str("%.2f" % srednia(list2, d)) + "(" + str("%.2f" % odchylenie(srednia(list2, d), list2,d)) + ")")
list3 = []
i=0
while i<d/2 + 1:
    list3.append(list2[i])
    i += 1
list4 = []
i=0
while i<d/2 + 1:
    list4.append(list2[d-i-1])
    i+=1
print("Mediana Q2(Q1-Q3): " + str(mediana(list2, d)) + "(" + str(mediana(list3, 75)) + " - " + str(mediana(list4, 75)) + ")")
print("Najwieksza wartość: " + str(maksimum(list2)))


