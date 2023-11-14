/*
 * Title: usb file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the MIT License.
 */

 /**
   @file usb.h

   @mainpage usb

   @section author Attribution
   - Title: FPS file.
   - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 6, 2023.

   @section ip Intellectual Property
   - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   @section license License
   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation files
   (the “Software”), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - https://www.cs.cmu.edu/~410/doc/doxygen.html

   @section warnings WARNINGS
   - empty
*/

#ifdef _WIN32
  #include <stdio.h>
  #include <stdint.h>
  #include <stdlib.h>
  #include <sys/time.h>
  #include <time.h>
  #include <windows.h>
#else
  #include <stdbool.h>
  #include <fcntl.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdint.h>
  #include <termios.h>
#endif

struct timespec start, end;

struct timespec timeAtStart;
uint64_t timeSinceStart;
uint64_t TIME_MAX = 1000000;
struct timespec timeNow;
int fpsPrevious;
int fpsCurrent;
uint64_t delta_us;
uint64_t timeDelta;

const int A_LOWER = 'a';

// Serial variables.
const uint32_t SERIAL_BAUD_RATE = 9600;
const int DEVICE_MIN = 0;
const int DEVICE_MAX = 255;
#ifdef _WIN32
  const DWORD TIMEOUT = 2000;
  HANDLE port;
  char device[] = {'\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0'};
#else
  // TODO: Remember that the Arduino Uno R3 board uses ttyACM*.
  // TODO: Remember that the Adafruit Feather ESP32 board uses ttyUSB*.
  // TODO: Remember that the Arduino Micro is a wildcard that shares a traditional USB connection and a generic gamepad connection over the same line, and that this really messes up Windows.
  // TODO: Build a discovery component that is similar the one built out in Python.
  // TODO: Remember that I build the discovery component in C#, not Python.
  const int TIMEOUT = 2000;
  int port;
  char device[] = {'/', 'd', 'e', 'v', '/', 't', 't', 'y', 'A', 'C', 'M', '\0', '\0', '\0', '\0'};
#endif

// Incoming data.
#ifdef _WIN32
  const uint8_t INCOMING_BUFFER = '<';
  DWORD received;
#else
  const int INCOMING_BUFFER = '<';
  size_t received;
  bool success;
#endif
uint8_t incomingBuffer[] = { INCOMING_BUFFER };

// Outgoing data.
#ifdef _WIN32
  const uint8_t OUTGOING_BUFFER = '>';
  DWORD written;
#else
  const int OUTGOING_BUFFER = '>';
#endif
uint8_t outgoingBuffer[] = { OUTGOING_BUFFER };

// Time.
#ifdef _WIN32
  SYSTEMTIME currentTime;
#else
#endif

// Error.
#ifdef _WIN32
  BOOL success;
#else
  ssize_t r;
  ssize_t result;
#endif

// Main loop.
#ifdef _WIN32
  BOOL isRunning = TRUE;
#else
#endif

char hourTime[3];
char minuteTime[3];
char secondTime[3];
char millisecondsTime[4];

char incomingChar[2];

// TODO: Remember that you cannot use index as a variable name.
int charIndex = 0;
const int INDEX_MAX = 72;
char incomingChars[73];
