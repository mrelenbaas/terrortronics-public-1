# Title: usb file.
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

import sys
import time

import serial

# Serial.
SERIAL_BAUD_RATE = 9600
DEVICE_MIN = 0
DEVICE_MAX = 255
# TODO: Add discovery.
DEVICE_PREFIX = ''
device = ''
if sys.platform == 'win32':
    DEVICE_PREFIX = 'COM'
elif sys.platform == 'linux':
    DEVICE_PREFIX = '/dev/ttyACM'
TIMEOUT = 2000
port = None

# Incoming data.
INCOMING_BUFFER = b'<'
incoming_buffer = INCOMING_BUFFER

# Outgoing data.
OUTGOING_BUFFER = b'>'
outgoing_buffer = OUTGOING_BUFFER

# Main loop.
is_running = True


# Iterate through ports, and stop after the first success.
def connect_serial_port():
    # Declarations.
    global device
    global port
    # Definitions.
    result = -1
    # Loop through ports.
    for i in range(DEVICE_MAX):
        try:
            # Define device.
            device = '{}{}'.format(DEVICE_PREFIX, i)
            # Open port.
            port = serial.Serial(device)
            result = 0
            break
        except serial.SerialException as e:
            print('ERROR: Invalid handle value.')
            continue
    return result


# Main function.
if __name__ == '__main__':
    # Open port.
    if connect_serial_port() is -1:
        exit(-1)

    # Flush port.
    port.flush()

    # Set timeout.
    port.timeout = TIMEOUT

    # Set state.
    port.baudrate = SERIAL_BAUD_RATE

    # Main loop.
    while is_running:
        # Update incoming data.
        print('{}: {}'.format(
            time.strftime("%H %M %S", time.gmtime()),
            port.read(len(INCOMING_BUFFER)).decode("utf-8")))

        # Update outgoing data.
        # WARNING: pySerial.write() will have an error if it isn't
        # handled in a thread seperate from PyGame.
        port.write(outgoing_buffer)

    # Close port.
    port.close()
