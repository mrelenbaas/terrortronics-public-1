# Title: timer file.
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

import time


PERIOD = 1.0
"""int: 1 second."""
PRINT = 'FPS: '
"""string: Prefix to print before FPS."""


class Timer:
    """Counts FPS."""

    def __init__(self, debug=False):
        self.__count = 0
        """int: Frames counted during current second."""
        self.__current = 0
        """int: Time (milliseconds) since start of second."""
        self.__debug = debug
        """boolean: Toggle debug calls on/off."""
        self.__fps = 0
        """int: Frames counted during previous second."""
        self.__function = self.printer
        """list: Function to be called once per period."""
        self.__now = 0
        """int: Time (milliseconds) since start of pygame."""
        self.__previous = 0
        """int: Time (milliseconds) at previous update."""

    def set_callback(self, function):
        """Set callback function to be called once per period. Function must have foo(string) definition."""
        self.__function = function

    def printer(self, text):
        """Print FPS to console."""
        if self.__debug:
            print('{}{}'.format(PRINT, text))

    def updater(self):
        """Counts frames for 1 second, then resets."""
        self.__now = time.time()
        self.__current += self.__now - self.__previous
        self.__previous = self.__now
        self.__count += 1
        if self.__current > PERIOD:
            self.__fps = self.__count
            self.__count = 0
            self.__current = 0
            self.__callback()

    def __callback(self):
        """Call functions."""
        self.__function(str(self.__fps))


if __name__ == '__main__':
    timer = Timer(debug=True)
    timer.set_callback(timer.printer)
    while True:
        timer.updater()
