# Title: game file.
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


# 1st-party libraries.
import sys
# 2nd-party libraries.
import inputer
import outputer
# 3rd-party libraries.
import pygame


"""Game manager.

Description
-----------
Game manager.

Author(s)
---------
- Created by Bradley Elenbaas on 12/30/2020.
- Modified by Bradley Elenbaas on 12/31/2020.

Copyright (c) 2020 Bradley Elenbaas.  All rights reserved.

Members
-------
"""


def teardown():
    """Quit everything."""
    pygame.quit()
    sys.exit()


class Game:
    """
    Game manager.

    Attributes
    ----------
    __inputer : Inputer
        Input manager.
    __outputer : Outputer
        Output manager.
    """

    def __init__(self):
        """Pseudo-constructor."""
        pygame.init()
        # Class variables.
        self.__inputer = inputer.Inputer()
        self.__outputer = outputer.Outputer()

    def updater(self):
        """Update input and output."""
        pressed, count = self.__inputer.updater()
        self.__outputer.updater(pressed, count)
