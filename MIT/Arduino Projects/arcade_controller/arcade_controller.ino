/**
   @file arcade_controller.cpp

   @mainpage Arcade Controller Project

   @section description Description
   The Arcade Controller.

   @section notes Notes
   - The Overview section of the Doxygen docs does not include print
   statements. The inline comments are the same as the Overview
   section, but they do include print statements.

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

// Include 2nd-party libraries.
#include "arcade_controller.h"
// Include 3rd-party libraries.
#include <MemoryFree.h>;

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
  if (isLogging) {
    for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
      Serial.print(millis());
      Serial.print(": buttons[");
      Serial.print(i);
      Serial.print("], ");
      buttons[i].printDefinitions();
      Serial.println("");
    }
  }
  buttons[buttonStart].startTargeting();
  state.startWaiting();
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
  if (isLogging) {
    Serial.print(millis());
    Serial.println(": ----------");
  }
  if (!timer()) {
    return;
  }
  for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
    if (buttons[i].updateHotState() == 1) {
      //Serial.println("PRESSED 0");
      if (buttons[i].debounceByTimePress() == 1) {
        //Serial.println("PRESSED 1");
        if (buttons[i].debounceByPositionPress() == 1) {
          Serial.println("PRESSED 2");
          if (buttons[i].debounceByBlockPress() == 1) {
            Serial.println("PRESSED 3");
            if (buttons[i].debounceByTargetPress() == 1) {
              if (state.isRunning() == 1) {
                Serial.println("PRESSED 4 (Running)");
              } else if (state.isWaiting() == 1) {
                Serial.println("PRESSED 4 (Waiting)");
              }
              //Serial.println("PRESSED 4");
              //state.startRunning();
            }
          }
        }
      }
      //buttons[i].debounceByPosition();
    } else {
      //Serial.println("PRESSED 0");
      if (buttons[i].debounceByTimeRelease() == 1) {
        //Serial.println("RELEASED 1");
        if (buttons[i].debounceByPositionRelease() == 1) {
          Serial.println("RELEASED 2");
          if (buttons[i].debounceByBlockRelease() == 1) {
            Serial.println("RELEASED 3");
            if (buttons[i].debounceByTargetRelease() == 1) {
              if (state.isRunning() == 1) {
                Serial.println("RELEASED 4 (Running)");
                buttons[i].stopTargeting();
                buttons[i].delegateFunction();
                // Do something else.
              } else if (state.isWaiting() == 1) {
                Serial.println("RELEASED 4 (Waiting)");
                buttons[i].stopTargeting();
                buttons[i].delegateFunction();
                buttons[buttonOther].startTargeting();
              }
            }
          }
        }
        buttons[i].reset();
      }
    }
  }
  if (isLogging) {
    for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
      Serial.print(millis());
      Serial.print(": digitalRead(, ");
      Serial.print(i);
      Serial.print("), ");
      buttons[i].printDefinitions();
      Serial.println("");
    }
  }
}

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Reset the application.

   RUSCAL:
   - isLogging <- FALSE

   @startuml
   skinparam shadowing  true
   (*) -right-> "Stop logging"
   -r-> (*)
   @enduml
*/
void resetFunction() {
  if (isLogging) {
    Serial.print(millis());
    Serial.print(": ");
    Serial.println("resetFunction()");
  }
  isLogging = false;
}

/**
   Start the application.

   RUSCAL:
   - isLogging <- TRUE

   @startuml
   skinparam shadowing  true
   (*) -right-> "Start logging"
   -r-> (*)
   @enduml
*/
void startFunction() {
  if (isLogging) {
    Serial.print(millis());
    Serial.print(": startFunction(), ");
    Serial.println(OUTGOING_START);
  }
  isLogging = true;
}

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The application's primary timer.

   @returns FALSE if delta is less than zero. Otherwise, TRUE.

   RUSCAL:
   - result isoftype Bool
   - result <- TRUE
   - timePrevious <- timeCurrent
   - timeCurrent <- Millis ()
   - timeDelta <- timeCurrent - timePrevious
   - if (timeDelta < 0)
    + result <- FALSE
   - elseif
   - timeThisSecond <- timeThisSecond + timeDelta
   - if (timeThisSecond >= TIME_ONE_SECOND)
    + fpsPrevious <- fpsCurrent
    + fpsCurrent <- 0
    + timeThisSecond <- timeThisSecond - TIME_ONE_SECOND
   - fpsCurrent <- fpsCurrent + 1
   - returns result

   @startuml
   skinparam shadowing  true
   (*) -r-> "Instantiate result"
   -r-> "Set previous time to current time"
   -r-> "Set current time to polled value"
   -r-> "Calculate delta"
   -r-> "time delta less than 0"
   -d-> "Set result to FALSE"
   -u-> "time delta less than 0"
   -r-> "Add time delta to time this second"
   -r-> "Time this second is greater than time period"
   -d-> "Set the previous FPS to FPS current"
   -d-> "Set the current FPS to zero"
   -d-> "Minus 1 second from time this second"
   -u-> "Time this second is greater than time period"
   -r-> "Add 1 to the current FPS"
   -r-> (*)
   @enduml
*/
bool timer() {
  bool result = true;
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  if (timeDelta < 0) {
    if (isLogging) {
      Serial.print(millis());
      Serial.print(": ERROR, timeDelta < 0");
    }
    result = false;
  }
  timeThisSecond += timeDelta;
  if (timeThisSecond >= TIME_ONE_SECOND) {
    fpsPrevious = fpsCurrent;
    fpsCurrent = 0;
    timeThisSecond -= TIME_ONE_SECOND;
  } //else {
    //++fpsCurrent;
  //}
  ++fpsCurrent;
  if (isLogging) {
    Serial.print(millis());
    Serial.print(": freeMemory, ");
    Serial.println(freeMemory());
  }
  return result;
}

////////////////////////////////////////////////////////////////////////
// Delegates ///////////////////////////////////////////////////////////
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
void startButtonFunction() {
  state.startRunning();
  Serial.println("START RUNNING");
}

/**
   Empty. The function to call then the Other button is pressed.
*/
void otherButtonFunction() {
  Serial.println("otherButtonFunction...");
}
