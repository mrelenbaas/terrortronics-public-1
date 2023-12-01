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

"""
Village House

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
Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files
(the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

import os
import pathlib
import sys
import time

if sys.platform == 'linux':
    import gpiozero
import pygame
from screeninfo import get_monitors

if sys.platform == 'linux':
    BUTTON_000 = 23
    BUTTON_001 = 6
    BUTTON_002 = 17
    BUTTON_003 = 26
    BUTTON_004 = 24
    BUTTON_005 = 5
    # BUTTON_000 = 22
else:
    BUTTON_000 = '1'
    BUTTON_001 = '2'
    BUTTON_002 = '3'
    BUTTON_003 = '4'
    BUTTON_004 = '5'
    BUTTON_005 = '6'
BUTTON_QUIT = 'q'


class Main:

    def __init__(self):
        width, height = self.__get_screen_dimensions()
        pygame.init()
        if width == 1024 and height == 600:
            self.__window = pygame.display.set_mode((0, 0),
                                                    pygame.FULLSCREEN)
        else:
            self.__window = pygame.display.set_mode((1024, 600))
        self.__background_color = pygame.Color('#000000')
        self.__other_color = pygame.Color('#FFFFFF')
        self.__color_on = pygame.Color('#FFFFFF')
        self.__color_off = pygame.Color('#000000')
        self.__color_000 = pygame.Color('#FFFFFF')
        self.__color_001 = pygame.Color('#FFFFFF')
        self.__color_002 = pygame.Color('#FFFFFF')
        self.__color_003 = pygame.Color('#FFFFFF')
        self.__color_004 = pygame.Color('#FFFFFF')
        self.__color_005 = pygame.Color('#FFFFFF')
        self.__block_destroy = False
        self.__x_000 = 0
        self.__y_000 = 20
        self.__x_001 = 360
        self.__y_001 = -30
        self.__x_002 = 0
        self.__y_002 = 460
        self.__x_003 = 270
        self.__y_003 = 440
        self.__x_004 = 480
        self.__y_004 = 440
        self.__x_005 = 650
        self.__y_005 = 440
        self.__rectangle_000 = pygame.Rect(self.__x_000,
                                           self.__y_000,
                                           340,
                                           300)
        self.__rectangle_001 = pygame.Rect(self.__x_001,
                                           self.__y_001,
                                           660,
                                           320)
        self.__rectangle_002 = pygame.Rect(self.__x_002,
                                           self.__y_002,
                                           210,
                                           130)
        self.__rectangle_003 = pygame.Rect(self.__x_003,
                                           self.__y_003,
                                           160,
                                           140)
        self.__rectangle_004 = pygame.Rect(self.__x_004,
                                           self.__y_004,
                                           160,
                                           140)
        self.__rectangle_005 = pygame.Rect(self.__x_005,
                                           self.__y_005,
                                           360,
                                           140)
        self.__image_000 = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_000.png'))
        self.__image_001_on = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_001_on.png'))
        self.__image_001_off = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_001_off.png'))
        self.__image_002 = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_002.png'))
        self.__image_003_on = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_003_on.png'))
        self.__image_003_off = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_003_off.png'))
        self.__image_004_on = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_004_on.png'))
        self.__image_004_off = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_004_off.png'))
        self.__image_005 = pygame.image.load(os.path.join(pathlib.Path().resolve(), 'temp_005.png'))
        self.__block_000 = False
        self.__block_001 = False
        self.__block_002 = False
        self.__block_003 = False
        self.__block_004 = False
        self.__block_005 = False
        if sys.platform == 'linux':
            self.__button_000 = gpiozero.Button(BUTTON_000)
            self.__button_001 = gpiozero.Button(BUTTON_001)
            self.__button_002 = gpiozero.Button(BUTTON_002)
            self.__button_003 = gpiozero.Button(BUTTON_003)
            self.__button_004 = gpiozero.Button(BUTTON_004)
            self.__button_005 = gpiozero.Button(BUTTON_005)
            self.__button_000.when_pressed = self.__function_000
            self.__button_001.when_pressed = self.__function_001
            self.__button_002.when_pressed = self.__function_002
            self.__button_003.when_pressed = self.__function_003
            self.__button_004.when_pressed = self.__function_004
            self.__button_005.when_pressed = self.__function_005
            self.__button_000.when_released = self.__release
            self.__button_001.when_released = self.__release
            self.__button_002.when_released = self.__release
            self.__button_003.when_released = self.__release
            self.__button_004.when_released = self.__release
            self.__button_005.when_released = self.__release
        # self.__image = pygame.transform.scale(self.__image, (1024, 600))
        self.__time_debounce = 0.01

    def loop(self):
        """The main function."""
        while True:
            if self.__block_destroy:
                break
            main.update()

    def update(self):
        self.__input()
        self.__output()

    def __function_000(self):
        if self.__block_000:
            self.__block_000 = False
        else:
            self.__block_000 = True
        time.sleep(self.__time_debounce)

    def __function_001(self):
        if self.__block_001:
            self.__block_001 = False
        else:
            self.__block_001 = True
        time.sleep(self.__time_debounce)

    def __function_002(self):
        if self.__block_002:
            self.__block_002 = False
        else:
            self.__block_002 = True
        time.sleep(self.__time_debounce)

    def __function_003(self):
        if self.__block_003:
            self.__block_003 = False
        else:
            self.__block_003 = True
        time.sleep(self.__time_debounce)

    def __function_004(self):
        if self.__block_004:
            self.__block_004 = False
        else:
            self.__block_004 = True
        time.sleep(self.__time_debounce)

    def __function_005(self):
        if self.__block_005:
            self.__block_005 = False
        else:
            self.__block_005 = True
        time.sleep(self.__time_debounce)

    def __get_screen_dimensions(self):
        for m in get_monitors():
            print(str(m))
        screen_info = str(get_monitors()[0])
        screen_info = screen_info.split('(')[1]
        screen_info = screen_info.split(')')[0]
        screen_info = screen_info.split(', ')
        width = screen_info[2]
        width = width.split('=')[1]
        width = int(width)
        height = screen_info[3]
        height = height.split('=')[1]
        height = int(height)
        print('{}, {}'.format(width, height))
        return width, height

    def __input(self):
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                self.__quit()
            if event.type == pygame.KEYDOWN:
                print(event.unicode)
                if event.unicode == BUTTON_QUIT:
                    self.__quit()
                elif event.unicode == BUTTON_000:
                    self.__function_000()
                elif event.unicode == BUTTON_001:
                    self.__function_001()
                elif event.unicode == BUTTON_002:
                    self.__function_002()
                elif event.unicode == BUTTON_003:
                    self.__function_003()
                elif event.unicode == BUTTON_004:
                    self.__function_004()
                elif event.unicode == BUTTON_005:
                    self.__function_005()
            if event.type == pygame.KEYUP:
                pass

    def __output(self):
        self.__window.fill(self.__background_color)
        if not self.__block_000:
            self.__window.blit(self.__image_000,
                               (self.__x_000, self.__y_000))
        if self.__block_001:
            self.__window.blit(self.__image_001_off,
                               (self.__x_001, self.__y_001))
        else:
            self.__window.blit(self.__image_001_on,
                               (self.__x_001, self.__y_001))
        if not self.__block_002:
            self.__window.blit(self.__image_002,
                               (self.__x_002, self.__y_002))
        if self.__block_003:
            self.__window.blit(self.__image_003_off,
                               (self.__x_003, self.__y_003))
        else:
            self.__window.blit(self.__image_003_on,
                               (self.__x_003, self.__y_003))
        if self.__block_004:
            self.__window.blit(self.__image_004_off,
                               (self.__x_004, self.__y_004))
        else:
            self.__window.blit(self.__image_004_on,
                               (self.__x_004, self.__y_004))
        if not self.__block_005:
            self.__window.blit(self.__image_005,
                               (self.__x_005, self.__y_005))
        pygame.display.update()

    def __release(self):
        self.__block = False

    def __quit(self):
        self.__block_destroy = True
        pygame.quit()
        sys.exit()


if __name__ == '__main__':
    main = Main()
    main.loop()
    print('complete')
