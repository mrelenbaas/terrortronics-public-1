# Title: main file.
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version: 2
# Date: September 15, 2023
#
# Intellectual Property:
# Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
#
# License:
# This file is owned by Terrortronics / Bradley Elenbaas.
# This file observes the MIT License.

# https://www.geeksforgeeks.org/graph-plotting-in-python-set-1/

import matplotlib.pyplot as plt

is_omen_included = False
is_kiosk_included = False

x5 = [0, 1]
y5 = [15287507, 15287507]
plt.plot(x5, y5, label="C++")

x6 = [0, 1]
y6 = [0, 0]
plt.plot(x6, y6, label="-")

x7 = [0, 1]
y7 = [0, 0]
plt.plot(x7, y7, label="-")

x8 = [0, 1]
y8 = [0, 0]
plt.plot(x8, y8, label="-")

x9 = [0, 1]
y9 = [0, 0]
plt.plot(x9, y9, label="-")

if is_kiosk_included:
    x3 = [0, 1, 2, 3]
    y3 = [415000, 415000, 236161, 236161]
    plt.plot(x3, y3, label="Unity Kiosk (Thread)")
    x4 = [0, 1, 2, 3]
    y4 = [59, 59, 59, 59]
    plt.plot(x4, y4, label="Unity Kiosk (Update)")

if is_omen_included:
    x1 = [0, 1, 2, 3]
    y1 = [1167000, 1167000, 1178000, 1178000]
    plt.plot(x1, y1, label="Unity Omen (Thread)")
    x2 = [0, 1, 2, 3]
    y2 = [59, 59, 59, 59]
    plt.plot(x2, y2, label="Unity Omen (Update)")

# naming the x axis
plt.xlabel('x - axis: Day #')
# naming the y axis
plt.ylabel('y - axis: FPS')
# giving a title to my graph
plt.title('FPS Graph')

# show a legend on the plot
plt.legend()

# function to show the plot
plt.show()


def main():
    """The main function."""
    pass
