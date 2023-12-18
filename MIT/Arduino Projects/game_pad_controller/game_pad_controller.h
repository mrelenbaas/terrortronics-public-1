////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file game_pad_controller.ino

   @mainpage game_pad_controller

   @section author Attribution
   - Title: Gamepad Controller file.
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
   - Board
    + Arduino Uno R3
   - Buttons

   @section pins Pins
   - Empty.

   @section resources Resources
   - Timer
    + http://popdevelop.com/2010/04/mastering-timer-interrupts-on-the-arduino/
    + http://www.desert-home.com/p/super-thermostat.html

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
  pinStickLeftHorizontal = (int)A0,    ///< Pin A0. L-Stick horizontal.
  pinStickLeftVertical = (int)A1,      ///< Pin A1. L-Stick vertical.
  pinStickRightHorizontal = (int)A2,   ///< Pin A2. R-Stick horizontal.
  pinStickRightVertical = (int)A3,     ///< Pin A3. R-Stick vertical.
  //pinSensorWater = (int)A4,            ///< Pin A2. Water sensor.
  //pinSensorSoundAnalog = (int)A5,      ///< Pin A3. Analog sound sensor.
  pinButtonStart = 4,                  ///< Pin 2. Start button.
  pinButtonReset = 5,                  ///< Pin 3. Reset button.
  pinSensorProximity = 6,               ///< Pin 4. Tracking sensor.
  //pinSensorSoundDigital = 5            ///< Pin 5. Digital sound sensor.
  pinLightDebug = 13
  // 20. Avoid - I2C.
  // 21. Avoid - I2C.
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Logging logging = Logging();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The incoming message.
*/
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
SentinelTimer sentinelTimer = SentinelTimer();

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
FPS fps = FPS();

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
    resetButtonFunctionRelease)
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
// Thumb Sticks ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*
   An enum paired with the thumbSticks.
*/
enum thumbStickEnum {
  thumbStickLeft,   ///< the left thumb stick.
  thumbStickRight   ///< The right thumb stick.
};

/**
   An array of ThumbStick elements. Handles the thumb sticks hot state.
*/
ThumbStick thumbSticks[] = {
  ThumbStick(pinStickLeftHorizontal, pinStickLeftVertical),
  ThumbStick(pinStickRightHorizontal, pinStickRightVertical)
};

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int result;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
