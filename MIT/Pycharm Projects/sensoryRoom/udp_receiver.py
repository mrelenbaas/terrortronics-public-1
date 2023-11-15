# Title: udp_receiver file.
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
UDP Receiver

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
import socket
import sys


FILENAME = 'udp_received.txt'
PACKET_SIZE = 1024
PORT = 9875


def get_path():
    path = ''
    if socket.gethostname() == 'DESKTOP-CR5GQ2G':
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'OneDrive',
            'Desktop')
    else:
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'Desktop')
    return path


def is_windows():
    result = False
    if os.name == 'nt' and sys.platform == 'win32':
        result = True
    return result


class UDP:

    def __init__(self):
        self.red = 0
        self.green = 0
        self.blue = 0
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.bind(("0.0.0.0", PORT))
        while True:
            connection, address = sock.recvfrom(PACKET_SIZE)
            connection = connection.decode('ascii')
            print(connection)
            with open(os.path.join(
                    os.path.expanduser('~/Desktop'), FILENAME), 'w+') as file:
                messages = connection.split(',')
                print(messages)
                for message in messages:
                    print(message)
                try:
                    file.write('{},{},{}'.format(
                        messages[0],
                        messages[1],
                        messages[2]))
                except OSError:
                    pass


class Main:

    def __init__(self):
        UDP()


if __name__ == '__main__':
    Main()
