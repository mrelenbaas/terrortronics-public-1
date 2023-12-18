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
*/

// 2nd-party libraries.
#include "game_pad_controller.h"
// 3rd-party libraries.
#include <MemoryFree.h>

/**
   Pseudo-constructor.
*/
void setup() {
  Serial.begin(BAUD_RATE);
  buttons[buttonStart].startTargeting();
  state.startWaiting();
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
  for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
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
  if (proximity.updateHotState() == 1) {
    if (proximity.debounceByTimePress() == 1) {
      if (proximity.debounceByPositionPress() == 1) {
        if (proximity.debounceByBlockPress() == 1) {
          if (proximity.debounceByTargetPress() == 1) {
            if (state.isRunning() == 1) {
            } else if (state.isWaiting() == 1) {
            }
          }
          proximity.delegateFunctionPress();
        }
      }
    }
  } else {
    if (proximity.debounceByTimeRelease() == 1) {
      if (proximity.debounceByPositionRelease() == 1) {
        if (proximity.debounceByBlockRelease() == 1) {
          if (proximity.debounceByTargetRelease() == 1) {
            if (state.isRunning() == 1) {
              proximity.stopTargeting();
              proximity.delegateFunctionPress();
              // Do something else.
            } else if (state.isWaiting() == 1) {
              proximity.stopTargeting();
            }
          }
          proximity.delegateFunctionRelease();
        }
      }
      proximity.reset();
    }
  }
  for (int i = 0; i < (sizeof(thumbSticks) / sizeof(ThumbStick)); ++i) {
    thumbSticks[i].updateHotState();
  }
  if (Serial.available() > 0 && !state.isRunning()) {
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case messageStart:
        startFunction();
        break;
      case messageReset:
        //resetFunction();
        break;
      default:
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Reset the application.

   RUSCAL:

   @startuml
   skinparam shadowing  true
   (*) -right-> "Stop logging"
   -r-> (*)
   @enduml
*/
void resetFunction() {
}

/**
   Start the application.

   RUSCAL:

   @startuml
   skinparam shadowing  true
   (*) -right-> "Start logging"
   -r-> (*)
   @enduml
*/
void startFunction() {
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The function to call when the Start button is pressed.

   RUSCAL
   - start.StartRunning ()

   @startuml
   skinparam shadowing  true
   (*) -right-> "Start running"
   -r-> (*)
   @enduml
*/
void startButtonFunctionPress() {
  lights[lightDebug].turnOn();
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
  state.startRunning();
}

/**
   Empty. The function to call then the Reset button is pressed.
*/
void resetButtonFunctionPress() {
}

void resetButtonFunctionRelease() {
}

void proximityButtonFunctionPress() {
  startButtonFunctionPress();
  pinMode(pinButtonStart, OUTPUT);
  digitalWrite(pinButtonStart, LOW);
}

void proximityButtonFunctionRelease() {
  startButtonFunctionRelease();
  pinMode(pinButtonStart, INPUT_PULLUP);
}

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
