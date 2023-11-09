# Title: inputer file.
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
Copyright 2023 Bradley Elenbaas

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
"""


# 2nd-party libraries.
import game
from timer import Timer
# 3rd-party libraries.
import pygame


"""Input manager.

Description
-----------
Input Manager.

Notes
-----
 - Cannot be named Input.

Author(s)
---------
- Created by Bradley Elenbaas on 12/30/2020.
- Modified by Bradley Elenbaas on 12/31/2020.

Copyright (c) 2020 Bradley Elenbaas.  All rights reserved.

Members
-------
"""


# Global Constants.
PRINT = 'Click: '
"""Print before click count."""


class Inputer:
    """Input manager.

    Attributes
    ----------
    __block : bool
        Blocks button input from press to release.
    __count : int
        Button press count.
    """

    def __init__(self):
        """Pseudo-constructor."""
        self.__timer = Timer()
        self.__timer.set_callback(self.decrement)
        self.__block = False
        self.__count = 0
        self.__pressed_blocked = False
        self.__pressed_count = 0

    def decrement(self, blank=None):
        if self.__count <= 0:
            return
        self.__count -= 1

    def increment(self):
        """Increment count."""
        self.__count += 1

    def is_pressed(self, pressed):
        """Filters raw input.

        :param pressed: Raw input.
        :type pressed: bool
        :return: Filtered input.
        :rtype: bool
        """
        result = False
        if (not self.__block) and pressed:
            result = True
            self.__block = True
        elif self.__block and (not pressed):
            self.__block = False
        return result

    def output(self):
        """Print click count."""
        print('{}{}'.format(PRINT, self.__count))

    def updater(self):
        """Increment count if button is pressed."""
        self.__timer.updater()
        pressed = False
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                game.Game.quit()
            if event.type == pygame.KEYDOWN:
                print(event.unicode)
                pressed = True
                self.__pressed_count += 1
                if not self.__pressed_blocked:
                    self.__pressed_blocked = True
            if event.type == pygame.KEYUP:
                self.__pressed_count -= 1
                if self.__pressed_blocked:
                    if self.__pressed_count <= 0:
                        self.__pressed_blocked = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if 0 < event.button <= 3:
                    print(repr(event.button))
                    self.__pressed_count += 1
                    pressed = True
                    if not self.__pressed_blocked:
                        self.__pressed_blocked = True
            if event.type == pygame.MOUSEBUTTONUP:
                self.__pressed_count -= 1
                if self.__pressed_blocked:
                    if self.__pressed_count <= 0:
                        self.__pressed_blocked = False
        if self.is_pressed(pressed):
            self.increment()
            self.output()
        return self.__pressed_blocked, self.__count
