/**
 * @file game_pad_controller.ino
 * 
 * @mainpage game_pad_controller
 * 
 * @section author Attribution
 * - Title: Gamepad Controller file.
 * - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * - Version: 2
 * - Date: November 6, 2023.
 * 
 * @section ip Intellectual Property
 * - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 * 
 * @section license License
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section description Description
 * Empty.
 * 
 * @section pins Pins
 * - empty
 * 
 * @section resources Resources
 * - Timer
 *  + http://popdevelop.com/2010/04/mastering-timer-interrupts-on-the-arduino/
 *  + http://www.desert-home.com/p/super-thermostat.html
 * 
 * @section warnings WARNINGS
 * - empty
 * 
 * @section ut Unit Tests
 * - empty
 */

// Include 1st-party libraries.
#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
// Include 2nd-party libraries.
#include "common.h"

////////////////////////////////////////////////////////////////////////
// Profiler Library ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Turn profiling on and off.
 */
#define PROFILING 1
/**
 * this needs to be true in at least one file.
 */
#define PROFILING_MAIN 1
/**
 * Override the number of bins.
 */
#define MAXPROF 8
#include "profiler.h"
/**
 * Counter for ISR time.
 */
volatile unsigned int int_counter;
/**
 * ISR time (seconds).
 */
volatile unsigned char seconds;
/**
 * ISR timer (minutes).
 */
volatile unsigned char minutes;
/**
 * Used to store timer value.
 */
unsigned int tcnt2;

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction();
void startFunction();
void startButtonFunction();
void resetButtonFunction();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The board's pins. Named with the [pin + type + name] convention, 
 * while other enums are named with the [type + name] convention.
 */
enum pinEnum {
  pinStickHorizontal = (int)A0,     ///< Pin A0. Stick (horizontal).
  pinStickVertical = (int)A1,       ///< Pin A1. Stick (vertical).
  pinSensorWater = (int)A2,         ///< Pin A2. Water sensor.
  pinSensorSoundAnalog = (int)A3,   ///< Pin A3. Analog sound sensor.
  pinButtonStart = 2,               ///< Pin 2. Start button.
  pinButtonReset = 3,               ///< Pin 3. Reset button.
  pinSensorTracking = 4,            ///< Pin 4. Tracking sensor.
  pinSensorSoundDigital = 5         ///< Pin 5. Digital sound sensor.
};

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The serial baud rate.
 */
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * An enum of possible message codes.
 */
enum messages {
  startMessage = 48,
  resetMessage = 49
};
/**
 * The default outgoing message.
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
 * The incoming message.
 */
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * If TRUE, then print logging tracers.
 */
bool IS_LOGGING = false;
/**
 * If TRUE, then print debug tracers.
 */
bool IS_DEBUGGING = true;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Time (in milliseconds) of a single second.
 */
unsigned long TIME_ONE_SECOND = 1000L;
/**
 * Time (in milliseconds) at the start of the previous loop.
 */
unsigned long timePrevious;
/**
 * Time (in milliseconds) at the start of the current loop.
 */
unsigned long timeCurrent;
/**
 * The difference between the current and previous loops.
 */
unsigned long timeDelta;
/**
 * The accumulated time this second.
 */
unsigned long timeAccumulated;

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The current number of frames counted this second.
 */
unsigned long fpsCurrent;
/**
 * The number of frames counted over the course of the previous second.
 */
unsigned long fpsPrevious;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The debounce period before a Press is considered valid.
 */
unsigned long DEBOUNCE_PERIOD_START = 10L;
/**
 * The debounce period before a Release is considered valid.
 */
unsigned long DEBOUNCE_PERIOD_STOP = 5L;
/**
 * An enum paired with the buttons and hotButtons.
 */
enum buttonEnum {
  buttonStart,   ///< The Start button index.
  buttonRedTop   ///< The Other button index.
};
/**
 * An array of Button elements. Handles the buttons hot state, 
 * debouncing, and callbacks.
 */
ButtonAVR buttons[] = {
  ButtonAVR(pinButtonStart,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            startButtonFunction),
  ButtonAVR(pinButtonReset,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            resetButtonFunction),
};

// Hot keyboard.
int horizontal;
int vertical;
int water;
int soundAnalog;
int tracking;
int soundDigital;

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The state of the game.
 */
State state = State();

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int counter;
