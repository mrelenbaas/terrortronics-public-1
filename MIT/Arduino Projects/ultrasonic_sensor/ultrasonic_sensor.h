////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file ultrasonic_sensors.h

   @mainpage ultrasonic_sensors

   @section author Attribution
   - Title: Ultrasonic Sensors file.
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
   - https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
   - https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all
   - https://stackoverflow.com/questions/1637332/static-const-vs-define

   @section ut Unit Tests
   - Empty.
*/

// 2nd-party libraries.
#include "common.h"
// 3rd-party libraries.
#include <NewPing.h>

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//#define TRIGGER_PIN 11
//#define ECHO_PIN 13
//#define TRIGGER_PIN_1 9
//#define ECHO_PIN_1 10
//#define TRIGGER_PIN_2 7
//#define ECHO_PIN_2 8
//#define TRIGGER_PIN_3 5
//#define ECHO_PIN_3 6
//#define TRIGGER_PIN_4 3
//#define ECHO_PIN_4 4
//#define MAX_DISTANCE 200
//#define AVOID_PIN 13
//#define METAL_PIN 14
//#define LED 15
//#define SOUND_ANALOG 16
//#define SOUND_DIGITAL 17
//#define PAPER 18

// NewPing setup of pins and maximum distance
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
//NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
//NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
//NewPing sonar4(TRIGGER_PIN_4, ECHO_PIN_4, MAX_DISTANCE);
//bool avoid;
//int metal;
//bool led;
//int soundAnalog;
//bool soundDigital;
//bool paper;

//int sonarIndex = 0;
//const int SONAR_MAX = 5;

//const long PERIOD = 1000;
//long timePrevious;
//long timeCurrent;
//long timeDelta;
//long timeThisSecond;
//unsigned long fpsPrevious;
//unsigned long fpsCurrent;

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
