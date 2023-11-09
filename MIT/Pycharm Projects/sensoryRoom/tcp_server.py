# Title: tcp_server file.
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

import os
import socket
import sys
import time

DELAY = 0.1
FILENAME = 'image_to_process_'
EXTENSION = '.png'
KEYWORD = 'Cloud'
MAC_FILENAME = 'hosts.txt'
MAC_KEYWORD = 'image_to_process_'
PACKET_SIZE = 1024
PORT = 5005
TIMEOUT = 5


def get_path():
    path = os.path.normpath(os.path.expanduser('~/Desktop'))
    if socket.gethostname() == 'DESKTOP-CR5GQ2G':
        path = os.path.normpath(os.path.expanduser('~/OneDrive/Desktop'))
    if os.name == 'posix' and socket.gethostname() == 'raspberrypi':
        path = os.path.normpath(
            os.path.expanduser(
                '~/Apps/purebasic_demo/examples/3d/Data/Textures'))
    return path


def is_windows():
    result = False
    if os.name == 'nt' and sys.platform == 'win32':
        result = True
    return result


def is_mac():
    result = False
    if os.name == 'posix' and sys.platform == 'darwin':
        result = True
    return result


def is_raspberry_pi():
    result = False
    if os.name == 'posix' and socket.gethostname() == 'raspberrypi':
        result = True
    return result


class Mac:

    def __int__(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind(('', PORT))
        sock.listen(TIMEOUT)
        while True:
            connection, address = sock.accept()
            data = connection.recv(PACKET_SIZE)
            data = data.decode('utf-8')
            data = str(data)
            if 'image_to_process_' not in data:
                filename = os.path.join(
                    os.path.normpath(os.path.expanduser('~/Desktop')),
                    MAC_FILENAME)
                with open(filename, 'w') as file:
                    print('file: ' + file.name)
                    print(data)
                    file.write(data)
                    connection.close()
                time.sleep(0.1)


class Windows:

    def __int__(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind(('', PORT))
        sock.listen(TIMEOUT)
        total_data = b''
        while True:
            data, addr = sock.accept()
            binary_data = data.recv(PACKET_SIZE)
            try:
                decoded_data = binary_data.decode('ascii')
                if 'Reply from ' in decoded_data:
                    continue
                index = decoded_data
                index = index.split('.')[0]
                index = index.split('_')[-1]
                if (os.name == 'posix') and (
                        socket.gethostname() == 'raspberrypi'):
                    filename_to_write = KEYWORD + index + EXTENSION
                    path = os.path.join(get_path(), filename_to_write)
                    with open(path, 'w+b') as file:
                        file.write(total_data)
                        data.close()
                else:
                    path = os.path.join(
                        get_path(),
                        'PureBasic',
                        'Examples',
                        '3D',
                        'Data',
                        'Textures',
                        KEYWORD + str(index).zfill(3) + EXTENSION)
                    with open(path, 'w+b') as file:
                        file.write(total_data)
                        data.close()
                time.sleep(DELAY)
                total_data = b''
            except OSError:
                total_data += binary_data


class Main:

    def __init__(self):
        if is_windows():
            Windows()
        if is_mac():
            Mac()


if __name__ == '__main__':
    print('IP Address: ' + socket.gethostbyname(socket.gethostname()))
    main = Main()
