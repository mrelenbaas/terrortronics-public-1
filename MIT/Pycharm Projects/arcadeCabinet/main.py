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
import gui
import profiler


"""The main file. Houses the main function and Main class.

Description
-----------
The main function instantiates the Main class, and nothing else.

Author(s)
---------
- Created by Bradley Elenbaas on 12/27/2020.
- Modified by Bradley Elenbaas on 12/29/2020.

Copyright (c) 2020 Bradley Elenbaas.  All rights reserved.

Members
-------
"""


class Main:
    """
    Manager of managers. Instantiates managers, and runs main game loop.

    Attributes
    ----------
    __gui : GUI
        Manages the tkinter library.

        Must be instantiated before Game class. Breaks on Mac only.

    __game : Game
        Manages the pygame library.
    """

    def __init__(self):
        """Main setup."""
        # Class variables.
        self.__gui = gui.GUI()
        self.__game = game.Game()
        self.__profiler = profiler.Profiler()
        # Calls.
        self.loop()

    def loop(self):
        """Main loop."""
        while True:
            self.__gui.updater()
            self.__game.updater()


if __name__ == '__main__':
    Main()
