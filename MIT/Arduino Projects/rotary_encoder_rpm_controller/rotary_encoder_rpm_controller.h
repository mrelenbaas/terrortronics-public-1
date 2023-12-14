/**
   @file rotary_encoder_rpm_controller.h

   @mainpage rotary_encoder_rpm_controller

   @section author Attribution
   - Title: Rotary Encoder RPM Controller file.
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
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF d  paOR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - https://www.adafruit.com/product/3405
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
   - https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview
   - https://github.com/espressif/arduino-esp32
   - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
   - https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
   - https://docs.arduino.cc/built-in-examples/digital/toneMelody

   @section warnings WARNINGS
   - empty
*/

// Include 1st-party libraries.
#include "WiFi.h"
#include "AsyncUDP.h"
// Include 2nd-party libraries.
#include "common.h"
// Include 3rd-party libraries.
#include "pitches.h"

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
  pinButtonStart = 21,
  pinButtonReset = 20
  // 20. Avoid - I2C.
  // 21. Avoid - I2C.
};

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

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
    startButtonFunctionRelease)/*,
  ButtonAVR(
    pinButtonReset,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    resetButtonFunctionPress,
    resetButtonFunctionRelease),*/
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   An enum of possible message codes.
*/
enum messages {
  startMessage = 48, ///< Start message.
  resetMessage = 49  ///< Reset message.
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
   If TRUE, then print tracer statements.
*/
bool isLogging;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// TODO: Remember that this is the only .ino file that uses the #define convention. Other .ino files use const ints.
// Rotary Encoder Inputs
#define CLK 22
#define DT 12
// TODO: Preserve this button setup in another prohject, but migrate this project to use interrupt pins.
#define RED_BUTTON 13
#define YELLOW_BUTTON 19
#define BLUE_BUTTON 18
#define GREEN_BUTTON 5
#define RED_LED 23
#define YELLOW_LED 32
#define BLUE_LED 15
#define GREEN_LED 33
#define BUZZER 14

int counter2 = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
bool currentStateCLK3Flag;

int counter3 = 0;
int lastStateCLK3;
String currentDir3 = "-";

// Serial.
const int SERIAL_DELAY = 10;

int INDEX_MAX = 9;
int counter = 0;

const float STEPS = 600.0f;
const float STEP = 0.6f; // 360 diveded by 600
float angle;

const long TIME_PERIOD = 1000;
long timeAtStart;
long timeSinceStart;
float timePercentage;
bool isRecording;
bool isRecordingFlag;

int specialCounter;
float totalSteps;

bool clkSet[1000];
bool dwSet[1000];

int fps;
int btnState;
int btnState0;
int btnState1;
int btnState2;
int btnState3;

float rps;
char angleBuffer[6];
char rpsBuffer[6];
char totalStepsBuffer[6];
//char stepsBuffer[6];

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
bool isBlinkOn;

const char * ssid = "NETGEAR08";
const char * password = "largeskates190";
AsyncUDP udp;
bool isWifiConnected;
char udpBuffer[40];

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
