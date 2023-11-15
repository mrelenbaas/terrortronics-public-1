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
# This file observes the GPL3 License.

"""
Go Karts

Description
-----------
Empty.

Circuit
-------
- Empty.

Libraries
---------
- Empty.

Notes
-----
- Empty.

TODO
----
- Empty.

Author(s)
---------
- Bradley Elenbaas (mr.elenbaas@gmail.com)
- Version 2
- Date: September 15, 2023

Intellectual Property
---------------------
Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

License
-------
Copyright 2023 Bradley Elenbaas

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Pins
----
- Empty.

Resources
---------
- Empty.

WARNINGS
--------
- Empty.
"""

import pathlib

import pygame
from pygame.locals import *
import random
import os
import sys

FILENAME = './points.txt'
imageIndex = 0
imageMax = 8
desktop = os.path.normpath(os.path.expanduser('./'))


def def_close_window():
    "Close the window with [x] button or ESC"
    loop = 1
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            loop = 0
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                loop = 0
    return loop


pygame.init()
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
# screen = pygame.display.set_mode((100, 100))
clock = pygame.time.Clock()


def start():
    loop = 1
    while loop:
        loop = def_close_window()
        screen.fill((0, 0, 0))
        filename = FILENAME
        randomImage = None
        with open(filename, 'r+') as f:
            data = f.read()
            data = data.replace('\n', '')
            data = data.replace('\r', '')
            print('DATA: ' + repr(data))
            if data == '0':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '000.png'))
            elif data == '1':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '001.png'))
            elif data == '2':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '002.png'))
            elif data == '3':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '003.png'))
            elif data == '4':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '004.png'))
            elif data == '5':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '005.png'))
            elif data == '6':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '006.png'))
            elif data == '7':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '007.png'))
            elif data == '8':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '008.png'))
            elif data == '9':
                randomImage = pygame.image.load(os.path.join(pathlib.Path().resolve(), '009.png'))
        randomImage = pygame.transform.scale(randomImage, (952, 743))
        screen.blit(randomImage, (0, 0))
        pygame.display.update()
        clock.tick(60)
    pygame.quit()


start()
