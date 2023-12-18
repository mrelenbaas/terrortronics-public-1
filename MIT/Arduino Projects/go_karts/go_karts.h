////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file go_karts.h

   @mainpage go_karts

   @section author Attribution
   - Title: GoKarts file.
   - Author: Bradley Elenbaas (mr.elenbaas@gmail.com)
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
   - Empty.

   @section notes Notes
   - Empty.

   @section warnings WARNINGS
   - Empty.

   @section libraries Libraries
   - Serial

   @section circuit Circuit
   - Empty.

   @section pins Pins
   - Empty.

   @section resources Resources
   - Empty.

   @section ut Unit Tests
   - Empty.
*/

// 2nd-party libraries.
#include "common.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void proximityButtonFunctionPress();
void proximityButtonFunctionRelease();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The board's pins. Named with the [pin + type + name] convention,
   while other enums are named with the [type + name] convention.
*/
enum pinEnum {
  // A4. Avoid - I2C.
  // A5. Avoid - I2C.
  // 2. Avoid - I2C.
  // 3. Avoid - I2C.
  pinButtonStart = 4,
  pinButtonReset = 5,
  pinSensorProximity = 6,               ///< Pin 4. Tracking sensor.
  pinLightDebug = 13
  // 20. Avoid - I2C.
  // 21. Avoid - I2C.
};

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The incoming message.
*/
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
logging = Logging(false, true);

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) at the start of the previous loop.
*/
unsigned long timePrevious;
/**
   Time (in milliseconds) at the start of the current loop.
*/
unsigned long timeCurrent;
/**
   The difference between the current and previous loops.
*/
unsigned long timeDelta;
/**
   The accumulated time this second.
*/
unsigned long timeAccumulated;

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The current number of frames counted this second.
*/
unsigned long fpsCurrent;
/**
   The number of frames counted over the course of the previous second.
*/
unsigned long fpsPrevious;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The debounce period before a Press is considered valid.
*/
unsigned long DEBOUNCE_PERIOD_START = 10L;
/**
   The debounce period before a Release is considered valid.
*/
unsigned long DEBOUNCE_PERIOD_STOP = 5L;
/**
   An enum paired with the buttons.
*/
enum buttonEnum {
  buttonStart,   ///< The Start button index.
  buttonReset    ///< The Reset button index.
};
/**
   An array of Button elements. Handles the buttons hot state,
   debouncing, and callbacks.
*/
ButtonAVR buttons[] = {
  ButtonAVR(
    pinButtonStart,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    startButtonFunctionPress,
    startButtonFunctionRelease),
  ButtonAVR(
    pinButtonReset,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    resetButtonFunctionPress,
    resetButtonFunctionRelease),
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum lightEnum {
  lightDebug
};

Light lights[] = {
  Light(pinLightDebug)
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Proximity ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A proximity sensor.
*/
Proximity proximity = Proximity(
  pinSensorProximity,
  Timer(),
  DEBOUNCE_PERIOD_START,
  DEBOUNCE_PERIOD_STOP,
  proximityButtonFunctionPress,
  proximityButtonFunctionRelease);

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*
  const int PINS_SIZE = 4;
  const int ORANGE = 2;
  const int GREEN = 3;
  const int PURPLE = 4;
  const int WHITE = 5;
  int PINS[] = {
  ORANGE,
  GREEN,
  PURPLE,
  WHITE
  };
*/

const long DELAY_BETWEEN_KEY_PRESS = 10;

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool isBlocked;
char WORD_ADMIN[] = {
  'a',
  'd',
  'm',
  'i',
  'n'
};
char WORD_PASSWORD[] = {
  'p',
  'a',
  's',
  's',
  'w',
  'o',
  'r',
  'd',
};
char WORD_SERVER[] = {
  '.',
  '/',
  'i',
  'o',
  't',
  'i',
  'v',
  'i',
  't',
  'y',
  '-',
  'l',
  'i',
  't',
  'e',
  '/',
  'p',
  'o',
  'r',
  't',
  '/',
  'l',
  'i',
  'n',
  'u',
  'x',
  '/',
  's',
  'i',
  'm',
  'p',
  'l',
  'e',
  's',
  'e',
  'r',
  'v',
  'e',
  'r'
};
