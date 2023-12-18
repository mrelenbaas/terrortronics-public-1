////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file arcade_controller.cpp

   @mainpage Arcade Controller Project

   @section author Author
   - Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 29, 2023

   @section ip Intellectual Property
   Copyright (c) 2023 Bradley Elenbaas. All rights
   reserved.

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
#include "arcade_controller.h"
// 3rd-party libraries.
#include <MemoryFree.h>

/**
   Pseudo-constructor that sets up the application.

   RUSCAL
   - serial.Begin (BAUD_RATE)
   - buttons[buttonStart].StartTargeting ()
   - state.StartWaiting ()

   @startuml
   skinparam shadowing  true
   (*) -r-> "Begin serial"
   -r-> "Start targeting start button"
   -r-> "Start waiting state"
   -r-> (*)
   @enduml
*/
void setup() {
  Serial.begin(BAUD_RATE);
}

/**
   The main function.

   RUSCAL:
   - if NOT (timer)
    + returnsa NIL
   - endif
   - i isoftype Num
   - loop
    + exitif (i >= (Sizeof (buttons) / Sizeof (Button)))
    + i <- i + 1
    + if (buttons[i].UpdateHotState () = 1)
     - if (buttons[i].DebounceByTimePress () = 1)
      + if (buttons[i].DebounceByPositionPress () = 1)
       - if (buttons[i].DebounceByBlockPress () = 1)
        + if (buttons[i].DebounceByTargetPress () = 1)
         - if (state.IsRunning () = 1)
         - elseif (state.IsWaiting () = 1)
         - endif
        + endif
       - endif
      + endif
     - endif
    + endif
    + else
     - if (buttons[i].UpdateHotState () = 1)
      + if (buttons[i].DebounceByTimeRelease () = 1)
       - if (buttons[i].DebounceByPositionRelease () = 1)
        + if (buttons[i].DebounceByBlockRelease () = 1)
         - if (buttons[i].DebounceByTargetRelease () = 1)
          + if (state.IsRunning () = 1)
           - buttons[i].StopTargeting ()
           - buttons[i].DelegateFunction ()
          + elseif (state.IsWaiting () = 1)
           -
          + endif
         - endif
        + endif
       - endif
      + endif
      + buttons[i].Reset ()
     - endif
    + endif
   - if (serial.Available > 0)
    + incomingMessage = serial.Read ()
    + if (incomingMessage = messageStart)
    + elseif (incomingMessage = messageReset)
     - ResetFunction ()
    + else
    + endif
   - endif

   UML 2.0 - Sequence Diagram
   @startuml
   skinparam shadowing  true
   participant "loop" as L
   participant "timer" as T
   participant "update hot state" as D1
   participant "debounce by time" as D2
   participant "debounce by position" as D3
   participant "debounce by block" as D4
   participant "debounce by target" as D5
   activate T
   activate L
   L -> T: << update the main timer >>
   T -> L: << return FALSE if error occurs >>
   deactivate T
   activate D1
   L -> D1: << update hot state >>
   D1 -> L: << return 1 if pressed >>
   deactivate D1
   activate D2
   L -> D2: << debounce by time >>
   D2 -> L: << return 1 if time exceeds period >>
   deactivate D2
   activate D3
   L -> D3: << debounce by position >>
   D3 -> L: << return 1 if position has changed >>
   deactivate D3
   activate D4
   L -> D4: << debounce by block >>
   D4 -> L: << return 1 if not-blocked >>
   deactivate D4
   activate D5
   L -> D5: << debounce by target >>
   D5 -> L: << return 1 if targeted >>
   deactivate D5
   L -> L: << route button press>>
   activate D1
   L -> D1: << update hot state >>
   D1 -> L: << return 1 if not-pressed >>
   deactivate D1
   activate D2
   L -> D2: << debounce by time >>
   D2 -> L: << return 1 if time exceeds period >>
   deactivate D2
   activate D3
   L -> D3: << debounce by position >>
   D3 -> L: << return 1 if position has changed >>
   deactivate D3
   activate D4
   L -> D4: << debounce by block >>
   D4 -> L: << return 1 if blocked >>
   deactivate D4
   activate D5
   L -> D5: << debounce by target >>
   D5 -> L: << return 1 if targeted >>
   deactivate D5
   L -> L: << route button release >>
   L -> L: << restart loop >>
   deactivate L
   @enduml
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
                buttons[i].delegateFunctionRelease();
              } else if (state.isWaiting() == 1) {
                buttons[i].stopTargeting();
                buttons[buttonRedTop].startTargeting();
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
   The function to call when the Reset button is pressed.
*/
void resetButtonFunctionPress() {
}

void resetButtonFunctionRelease() {
}

/**
   The function to call when the top-red button is pressed.
*/
void redTopButtonFunctionPress() {
}

void redTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-red button is pressed.
*/
void redBottomButtonFunctionPress() {
}

void redBottomButtonFunctionRelease() {
}

/**
   The function to call when the top-green button is pressed.
*/
void greenTopButtonFunctionPress() {
}

void greenTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-green button is pressed.
*/
void greenBottomButtonFunctionPress() {
}

void greenBottomButtonFunctionRelease() {
}

/**
   The function to call when the blue-top button is pressed.
*/
void blueTopButtonFunctionPress() {
}

void blueTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-blue button is pressed.
*/
void blueBottomButtonFunctionPress() {
}
void blueBottomButtonFunctionRelease() {
}

/**
   The function to call when the yellow-top button is pressed.
*/
void yellowTopButtonFunctionPress() {
}

void yellowTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-yellow button is pressed.
*/
void yellowBottomButtonFunctionPress() {
}

void yellowBottomButtonFunctionRelease() {
}

/**
   The function to call when the black-top button is pressed.
*/
void blackTopButtonFunctionPress() {
}

void blackTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-black button is pressed.
*/
void blackBottomButtonFunctionPress() {
}

void blackBottomButtonFunctionRelease() {
}

/**
   The function to call when the top-white button is pressed.
*/
void whiteTopButtonFunctionPress() {
}

void whiteTopButtonFunctionRelease() {
}

/**
   The function to call when the bottom-white button is pressed.
*/
void whiteBottomButtonFunctionPress() {
}

void whiteBottomButtonFunctionRelease() {
}

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
