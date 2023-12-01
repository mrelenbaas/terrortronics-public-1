# Title: coap_client file.
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
CoAP Client

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

import asyncio
import aiocoap


async def main():
    context = await aiocoap.Context.create_client_context()
    await asyncio.sleep(2)
    payload = b"0"
    filename = os.path.expanduser('~/Desktop')
    filename = os.path.join(filename, 'hosts.txt')
    with open(filename, 'r') as file:
        while line := file.readline():
            print("line: " + line)
            request = aiocoap.Message(
                code=aiocoap.PUT,
                payload=payload,
                uri="coap://" + line + "/resource/update")
            response = await context.request(request).response
            print('Result: %s\n%r' % (response.code, response.payload))

if __name__ == "__main__":
    asyncio.run(main())
