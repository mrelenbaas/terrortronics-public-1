# Title: gui file.
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
import tkinter
import tkinter.messagebox
# 2nd-party libraries.
import game
from timer import Timer


ABOUT_CAPTION = 'About SoftfootFalls'
ABOUT_LABEL = 'About'
ABOUT_TEXT = 'SoftfootFalls by Bradley Elenbaas (c)2020'
PRINT = 'FPS: '
QUIT_CAPTION = 'Quit'
QUIT_TEXT = 'Do you really wish to quit?'
ROOT_PROTOCOL = 'WM_DELETE_WINDOW'
STATUS_TEXT = 'FPS'
WINDOW_CAPTION = 'SoftfootFalls'


def callback_about():
    tkinter.messagebox.showinfo(ABOUT_CAPTION, ABOUT_TEXT)


class GUI:
    """
    Manages the tkinter library.

    Attributes
    ----------
    """

    def __init__(self):
        # Local variables.
        root = tkinter.Tk()
        root.protocol(ROOT_PROTOCOL, self.callback_quit)
        root.title(WINDOW_CAPTION)
        menubar = tkinter.Menu(root)
        menubar.add_command(label=ABOUT_LABEL, command=callback_about)
        root.config(menu=menubar)
        # Class variables.
        self.__main_dialog = tkinter.Frame(root)
        self.__status_line = tkinter.Label(self.__main_dialog,
                                           relief=tkinter.SUNKEN,
                                           anchor=tkinter.W)
        self.__status_line.config(text='[status line]')
        self.__timer = Timer()
        self.__timer.set_callback(self.set_status_line)
        self.__timer.set_callback(root.title)
        # Pack.
        self.__status_line.pack(side=tkinter.BOTTOM, fill=tkinter.X)
        self.__main_dialog.pack()

    def set_status_line(self, text):
        self.__status_line.config(text=text)

    def callback_quit(self):
        if tkinter.messagebox.askokcancel(QUIT_CAPTION, QUIT_TEXT):
            self.__main_dialog.destroy()
            game.Game.quit()

    def updater(self):
        self.__main_dialog.update()
        self.__timer.updater()
