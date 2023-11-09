# Title: tcp_client file.
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

DELAY = 1
MAC_EXTENSION = '.png'
MAC_FILENAME = 'hosts.txt'
MAC_KEYWORD = 'image_to_process_'
WINDOWS_FILENAME_CLEAN = 'clean_pingtest.txt'
WINDOWS_FILENAME_RAW = 'previous_pingtest.txt'
PACKET_SIZE = 1024
PORT = 5005


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


class Mac:

    def __init__(self):
        self.__current_filename = ''
        self.__hosts = []

    def main(self):
        desktop = os.path.expanduser("~/Desktop")
        while True:
            is_top = True
            for root, directory, filenames in os.walk(desktop):
                if is_top is False:
                    continue
                is_top = False
                for filename in filenames:
                    if MAC_KEYWORD in filename:
                        self.__current_filename = filename.encode('ascii')
                        host_filename = os.path.join(desktop, MAC_FILENAME)
                        with open(host_filename) as file:
                            while line := file.readline():
                                self.__hosts.append(line.rstrip())
                        for host in self.__hosts:
                            image = os.path.join(desktop, filename)
                            if os.path.exists(image):
                                file = open(image, 'rb')
                                bytes_to_send = file.read()
                                size = len(bytes_to_send)
                                max_size = PACKET_SIZE
                                packet_count = int(size / max_size) + 1
                                for i in range(packet_count):
                                    start = i * max_size
                                    end = (i + 1) * max_size
                                    if i < packet_count - 1:
                                        with socket.socket(
                                                socket.AF_INET,
                                                socket.SOCK_STREAM) as sock:
                                            sock.connect((host, PORT))
                                            sock.sendall(
                                                bytes_to_send[start:end])
                                            sock.close()
                                    else:
                                        with socket.socket(
                                                socket.AF_INET,
                                                socket.SOCK_STREAM) as sock:
                                            sock.connect((host, PORT))
                                            sock.sendall(
                                                bytes_to_send[start:])
                                            sock.close()
                                with socket.socket(
                                        socket.AF_INET,
                                        socket.SOCK_STREAM) as sock:
                                    sock.connect((host, PORT))
                                    sock.sendall(self.__current_filename)
                                    sock.close()
                                os.remove(os.path.join(desktop, filename))
                            else:
                                time.sleep(DELAY)


class Windows:

    def __init__(self):
        self.__hosts = []

    def main(self):
        print('main start')
        raw_filename = ''
        clean_filename = ''
        if socket.gethostname() == 'DESKTOP-CR5GQ2G':
            raw_filename += os.path.join(
                'C:',
                os.sep,
                'Users',
                os.getlogin(),
                'OneDrive',
                'Desktop',
                WINDOWS_FILENAME_RAW)
            clean_filename += os.path.join(
                'C:',
                os.sep,
                'Users',
                os.getlogin(),
                'OneDrive',
                'Desktop',
                WINDOWS_FILENAME_CLEAN)
        else:
            raw_filename += os.path.join(
                'C:',
                os.sep,
                'Users',
                os.getlogin(),
                'Desktop',
                WINDOWS_FILENAME_RAW)
            clean_filename += os.path.join(
                'C:',
                os.sep,
                'Users',
                os.getlogin(),
                'Desktop',
                WINDOWS_FILENAME_CLEAN)
        print('raw_filename: ' + raw_filename)
        print('clean_filename: ' + clean_filename)
        with open(raw_filename) as file:
            while line := file.readline():
                clean_line = line.rstrip()
                clean_line = clean_line.split('Reply from ')[-1]
                clean_line = clean_line.split(':')[0]
                self.__hosts.append(clean_line)
        with open(clean_filename, 'w') as file:
            file.write('')
        with open(clean_filename, 'a') as file:
            for host in self.__hosts:
                file.write(host)
        for host in self.__hosts:
            file = open(clean_filename, 'rb')
            package = file.read()
            print('host: ' + host)
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                sock.connect((host, PORT))
                sock.send(package)
                sock.close()
        os.remove(raw_filename)
        os.remove(clean_filename)


class Main:

    def __init__(self):
        if is_windows():
            windows = Windows()
            windows.main()
        if is_mac():
            mac = Mac()
            mac.main()


if __name__ == '__main__':
    Main()
