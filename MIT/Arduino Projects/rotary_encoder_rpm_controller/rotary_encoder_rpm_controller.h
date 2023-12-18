/**
   @file rotary_encoder_rpm_controller.h

   @mainpage rotary_encoder_rpm_controller

   @section author Attribution
   - Title: Rotary Encoder RPM Controller file.
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
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF d  paOR IN
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
   - https://www.adafruit.com/product/3405
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
   - https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview
   - https://github.com/espressif/arduino-esp32
   - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
   - https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
   - https://docs.arduino.cc/built-in-examples/digital/toneMelody

   @section ut Unit Tests
   - Empty.
*/

// 1st-party libraries.
#include "WiFi.h"
#include "AsyncUDP.h"
// 2nd-party libraries.
#include "common.h"
// 3rd-party libraries.
#include "pitches.h"

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
  pinButtonGreen = 5,
  pinButtonRed = 13,
  pinBuzzer = 14,
  pinLightBlue = 15,
  pinButtonBlue = 18,
  pinButtonYellow = 19,
  pinButtonReset = 20,
  pinButtonStart = 21,
  pinLightRed = 23,
  pinLightYellow = 32,
  pinLightGreen = 33
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
  lightRed,
  lightGreen,
  lightBlue,
  lightYellow
};

Light lights[] = {
  Light(pinLightRed),
  Light(pinLightGreen),
  Light(pinLightBlue),
  Light(pinLightYellow)
};

////////////////////////////////////////////////////////////////////////
// Sound ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
bool isBlinkOn;

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const char * ssid = "NETGEAR08";
const char * password = "largeskates190";
AsyncUDP udp;
bool isWifiConnected;
char udpBuffer[40];

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
