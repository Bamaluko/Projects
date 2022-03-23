import numpy
from cmath import pi, sqrt, cos, sin
from random import random
from typing import List
from obiekty.Punkt import Punkt


# Losowanie neuronów dla pojedynczego okręgu, 200 punktów na okrąg
def losowanie_neuronow_1_okrag() -> List[Punkt]:
    punkty = []

    for i in range(200):
        radian = 1 * sqrt(random())
        value = random() * 2 * pi

        x = numpy.real([0 + radian * cos(value)])
        y = numpy.real([0 + radian * sin(value)])

        punkty.append(Punkt(x, y))

    return punkty


# Losowanie neuronów dla dwóch okręgów, 100 punktów na okrąg
def losowanie_neuronow_2_okregi() -> List[Punkt]:
    punkty = []

    for i in range(100):
        radian = 0.5 * sqrt(random())
        value = random() * 2 * pi

        x = numpy.real([-3 + radian * cos(value)])
        y = numpy.real([0 + radian * sin(value)])

        punkty.append(Punkt(x, y))

    for i in range(100):
        radian = 0.5 * sqrt(random())
        value = random() * 2 * pi

        x = numpy.real([3 + radian * cos(value)])
        y = numpy.real([0 + radian * sin(value)])

        punkty.append(Punkt(x, y))

    return punkty
