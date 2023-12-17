/**
   @file joystick_manager.h

   @mainpage joystick_manager

   @section author Attribution
   - Title: Joystick Manager file.
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

// Include 2nd-party libraries.
#include "common.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction();
void startFunction();

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
  pinButtonReset = 5
  // 20. Avoid - I2C.
  // 21. Avoid - I2C.
};

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   An enum of possible message codes.
*/
enum messageEnum {
  messageStart = 48, ///< Start message.
  messageReset = 49  ///< Reset message.
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
  'f',
  'p',
  's',
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
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   If TRUE, then print logging tracers.
*/
bool IS_LOGGING = false;
/**
   If TRUE, then print debug tracers.
*/
bool IS_DEBUGGING = true;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) of a single second.
*/
unsigned long TIME_ONE_SECOND = 1000L;
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
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// Pins.
const int PIN_ONE = 5;
const int PIN_TWO = 6;
const int PIN_THREE = 7;
const int PIN_FOUR = 8;
const int PINS_SIZE = 4;
const int PINS[] = {
  PIN_ONE,
  PIN_TWO,
  PIN_THREE,
  PIN_FOUR
};
int pinIndex;

// Joysticks.
const long DELAY_BETWEEN_JOYSTICKS = 10000;
bool isTurningJoysticksOn;
bool isTurningJoysticksOff;

// Timer.
unsigned long previousTime;
unsigned long currentTime;
unsigned long deltaTime;
unsigned long delayTime;

// Serial.
const int SERIAL_DELAY = 200;

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
