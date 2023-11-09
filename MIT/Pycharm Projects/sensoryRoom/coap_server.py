# Title: coap_server file.
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

__version__ = '0.1'
__author__ = 'Bradley Elenbaas'


import os
import socket
import subprocess
import sys

import asyncio
import aiocoap.resource as resource
import aiocoap


PACKET_SIZE = 1024
PORT = 5683


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


class Resource(resource.Resource):

    def __init__(self):
        super().__init__()
        self.__content = b"default"
        self.set_content(self.__content)

    def set_content(self, content):
        self.__content = content
        while len(self.__content) <= PACKET_SIZE:
            self.__content = self.__content + b"0123456789\n"

    async def render_get(self, request):
        return aiocoap.Message(payload=self.__content)

    async def render_put(self, request):
        print('PUT payload: %s' % request.payload)
        self.set_content(request.payload)
        print('shutdown')
        if is_windows():
            pass
            subprocess.run([os.path.join(get_path(), 'SHUTDOWN.BAT')])
        else:
            print('mac detected')
        return aiocoap.Message(code=None, payload=self.__content)


class Main:

    def __init__(self):
        self.__root = resource.Site()
        self.__root.add_resource(['resource', 'update'], Resource())
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.connect(("8.8.8.8", 80))
        self.__my_ip_address = sock.getsockname()[0]
        print(self.__my_ip_address)
        asyncio.run(self.__main())

    async def __main(self):
        await aiocoap.Context.create_server_context(
            bind=(self.__my_ip_address, PORT),
            site=self.__root)
        await asyncio.get_running_loop().create_future()


if __name__ == "__main__":
    Main()
