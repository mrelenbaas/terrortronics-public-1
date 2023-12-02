/*
   Title: game_pad_controller file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the MIT License.
*/

/**
  @file game_pad_controller.ino

  @mainpage game_pad_controller

  @section author Attribution
  - Title: Gamepad Controller file.
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
  - empty

  @section warnings WARNINGS
  - empty
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <HardwareSerial.h>

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   An enum of possible message codes.
*/
enum messages {
  startMessage = 48,
  resetMessage = 49
};
/**
   The default outgoing message.
*/
const char OUTGOING_START[] = {
  't',
  'y',
  'p',
  'e',
  ':',
  'c',
  'o',
  'n',
  'f',
  'i',
  'g',
  ',',
  'f',
  'i',
  'l',
  'e',
  'n',
  'a',
  'm',
  'e',
  ':',
  'g',
  'a',
  'm',
  'e',
  '_',
  'p',
  'a',
  'd',
  '_',
  'c',
  'o',
  'n',
  't',
  'r',
  'o',
  'l',
  'l',
  'e',
  'r',
  ',',
  'f',
  'u',
  'n',
  'c',
  't',
  'i',
  'o',
  'n',
  ':',
  'r',
  'e',
  's',
  'e',
  't',
  ',',
  'd',
  'e',
  'l',
  'i',
  'm',
  'i',
  't',
  'e',
  'r',
  's',
  ':',
  ' ',
  'c',
  'm',
  '0',
  ';',
  ' ',
  'c',
  'm',
  '1',
  ';',
  ' ',
  'c',
  'm',
  '2',
  ';',
  ' ',
  'c',
  'm',
  '3',
  ';',
  ' ',
  'c',
  'm',
  '4',
  ';',
  '\\',
  'n',
  '\0'
};
/**
   The incoming message.
*/
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

const int SERIAL_DELAY = 10;

// Pin constants.
const int HORIZONTAL = A0;
const int VERTICAL = A1;
const int WATER = A2;
const int SOUND_ANALOG = A3;
const int BUTTON = 2;
const int SILICONE_BUTTON = 3;
const int TRACKING = 4;
const int SOUND_DIGITAL = 5;

// Hot keyboard.
int horizontal;
int vertical;
int water;
int soundAnalog;
int button;
int siliconeButton;
int tracking;
int soundDigital;

const long PERIOD = 1000;
long timePrevious;
long timeCurrent;
long timeDelta;
long timeThisSecond;
unsigned long fpsPrevious;
unsigned long fpsCurrent;

// this can be used to turn profiling on and off
#define PROFILING 1
// this needs to be true in at least ONE .c, .cpp, or .ino file in your sketch
#define PROFILING_MAIN 1
// override the number of bins
#define MAXPROF 8
#include "profiler.h"

// some handy macros for printing debugging values
//#define DL(x) Serial.print(x)
//#define DLn(x) Serial.println(x)
//#define DV(m, v) do{Serial.print(m);Serial.print(v);Serial.print(" ");}while(0)
//#define DVn(m, v) do{Serial.print(m);Serial.println(v);}while(0)

// more handy macros but unused in this example
#define InterruptOff  do{TIMSK2 &= ~(1<<TOIE2)}while(0)
#define InterruptOn  do{TIMSK2 |= (1<<TOIE2)}while(0)

// stuff used for time keeping in our ISR
volatile unsigned int int_counter;
volatile unsigned char seconds, minutes;
unsigned int tcnt2; // used to store timer value

bool isStarted;

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
