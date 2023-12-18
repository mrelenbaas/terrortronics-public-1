////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file ultrasonic_sensors.ino

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
*/

// 2nd-party libraries.
#include "ultrasonic_sensor.h"
// 3rd-party libraries.
#include <MemoryFree.h>

void setup() {
  Serial.begin(BAUD_RATE);
}

/**
   The main function.
*/
void loop() {
  result = sentinelTimer.updateGuard();
  if (result == 0) {
    return;
  } else if (result == 1) {
    fps.increment();
  } else if (result == 2) {
    Serial.print(millis());
    Serial.print(", FPS: ");
    Serial.print(fps.getFPS());
    Serial.print(", freeMemory: ");
    Serial.print(freeMemory());
    Serial.println();
    fps.reset();
  }
  for (unsigned int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) { // TODO: Use unsigned int for other for loops.
    if (buttons[i].updateHotState() == 1) {
      if (buttons[i].debounceByTimePress() == 1) {
        if (buttons[i].debounceByPositionPress() == 1) {
          if (buttons[i].debounceByBlockPress() == 1) {
            if (buttons[i].debounceByTargetPress() == 1) {
              if (state.isRunning() == 1) {
              } else if (state.isWaiting() == 1) {
              }
            }
            buttons[i].delegateFunctionPress();
          }
        }
      }
    } else {
      if (buttons[i].debounceByTimeRelease() == 1) {
        if (buttons[i].debounceByPositionRelease() == 1) {
          if (buttons[i].debounceByBlockRelease() == 1) {
            if (buttons[i].debounceByTargetRelease() == 1) {
              if (state.isRunning() == 1) {
                buttons[i].stopTargeting();
                buttons[i].delegateFunctionPress();
              } else if (state.isWaiting() == 1) {
                buttons[i].stopTargeting();
                state.startRunning();
                buttons[buttonReset].startTargeting();
              }
            }
            buttons[i].delegateFunctionRelease();
          }
        }
        buttons[i].reset();
      }
    }
  }
  if (Serial.available() > 0) {
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case messageStart:
        startFunction();
        break;
      case messageReset:
        resetFunction();
        break;
      default:
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction() {
}

void startFunction() {
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startButtonFunctionPress() {
  lights[lightDebug].turnOn();
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
}

/**
   Empty. The function to call then the Reset button is pressed.
*/
void resetButtonFunctionPress() {
}

void resetButtonFunctionRelease() {
}

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////s
