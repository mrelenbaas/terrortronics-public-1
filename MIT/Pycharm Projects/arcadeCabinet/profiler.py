# Title: profiler file.
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

import cProfile
import io
import pstats
from pstats import SortKey


"""Profiler file.

Description
-----------
Runs the built-in Python profiler.

Author(s)
---------
- Created by Bradley Elenbaas on 12/30/2020.
- Modified by Bradley Elenbaas on 12/31/2020.

Copyright (c) 2020 Bradley Elenbaas.  All rights reserved.

Members
-------
"""


def parse(filename, s):
    for i in range(len(s)):
        if i < 5:
            continue
        if i > len(s) - 3:
            continue
        if not '{}.py'.format(filename) in s[i]:
            continue
        if '(updater)' in s[i]:
            pass
        else:
            continue
        d = []
        for c in s[i].split(' '):
            if c == '':
                continue
            else:
                d.append(c)
        print('[{}] {}'.format(filename, d[3]))


class Profiler:
    """Profiler manager."""

    def __init__(self):
        """Pseudo-constructor."""
        self.__profiler = None
        self.__start()

        self.__count = 0
        self.__column_counter = 0

    def dump(self):
        """Print and clear profile."""
        self.stop()
        self.__start()

    def output(self):
        """Print profile."""
        s = io.StringIO()
        sortby = SortKey.CUMULATIVE
        ps = pstats.Stats(self.__profiler, stream=s).sort_stats(sortby)
        ps.print_stats()
        s = s.getvalue().splitlines()
        # Note: this is working, though is shows that the Python version
        # spends its time performing output, and the Ardino verion spends
        # its time performing input.
        parse('inputer', s)
        parse('outputer', s)

    def stop(self):
        """Stop profiler."""
        self.__profiler.disable()
        self.output()

    def __start(self):
        """Start profiler."""
        self.__profiler = cProfile.Profile()
        self.__profiler.enable()
