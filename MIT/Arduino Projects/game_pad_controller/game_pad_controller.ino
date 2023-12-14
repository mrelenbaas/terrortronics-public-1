/**
   @file game_pad_controller.ino

   @mainpage game_pad_controller

   @section author Attribution
   - Title: Gamepad Controller file.
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
#include "game_pad_controller.h"
// Include 3rd-party libraries.
#include <MemoryFree.h>;

/**
   Arduino runs at 16 Mhz, so we have 1000 overflows per second...
   This ISR will get hit once a millisecond.
*/
ISR(TIMER2_OVF_vect) {
  int_counter++;
  if (int_counter == 1000) {
    seconds++;
    int_counter = 0;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
    }
  }
#if PROFILING
  prof_array[prof_line]++;
#endif
  TCNT2 = tcnt2;
}

/**
   Setup the ISR timer.
*/
void setupTimer(void) {
  // First disable the timer overflow interrupt while we're configuring
  TIMSK2 &= ~(1 << TOIE2);
  // Configure timer2 in normal mode (pure counting, no PWM etc.)
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  // Select clock source: internal I/O clock
  ASSR &= ~(1 << AS2);
  // Disable Compare Match A interrupt enable (only want overflow)
  TIMSK2 &= ~(1 << OCIE2A);
  // Now configure the prescaler to CPU clock divided by 128
  TCCR2B |= (1 << CS22) | (1 << CS20);  // Set bits
  TCCR2B &= ~(1 << CS21);               // Clear bit
  /* We need to calculate a proper value to load the timer counter.
     The following loads the value 131 into the Timer 2 counter register
     The math behind this is:
     (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
     (desired period) / 8us = 125.
     MAX(uint8) - 125 = 131;
  */
  // Save value globally for later reload in ISR
  tcnt2 = 131;
  // Finally load end enable the timer
  TCNT2 = tcnt2;
  TIMSK2 |= (1 << TOIE2);
  sei();
}

/**
   Pseudo-constructor.
*/
void setup() {
  Serial.begin(BAUD_RATE);
  if (IS_DEBUGGING) {
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
  //pinMode(pinButtonStart, INPUT_PULLUP);
  pinMode(13, OUTPUT);
#if PROFILING
  PF(0);
  prof_has_dumped = 0;
  clear_profiling_data();
#endif
  int_counter = 0;
  seconds = 0;
  minutes = 0;
  setupTimer();
}

/**
   The main function.
*/
void loop() {
  unsigned char op;
  if (IS_LOGGING) {
    //Serial.print(millis());
    //Serial.println(": ----------");
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
          //Serial.println("PRESSED 2");
          if (buttons[i].debounceByBlockPress() == 1) {
            //Serial.println("PRESSED 3");
            if (buttons[i].debounceByTargetPress() == 1) {
              if (state.isRunning() == 1) {
                //Serial.println("PRESSED 4 (Running)");
              } else if (state.isWaiting() == 1) {
                //Serial.println("PRESSED 4 (Waiting)");
              }
            }
            buttons[i].delegateFunctionPress();
          }
        }
      }
      //buttons[i].debounceByPosition();
    } else {
      //Serial.println("PRESSED 0");
      if (buttons[i].debounceByTimeRelease() == 1) {
        //Serial.println("RELEASED 1");
        if (buttons[i].debounceByPositionRelease() == 1) {
          //Serial.println("RELEASED 2");
          if (buttons[i].debounceByBlockRelease() == 1) {
            //Serial.println("RELEASED 3");
            if (buttons[i].debounceByTargetRelease() == 1) {
              if (state.isRunning() == 1) {
                //Serial.println("RELEASED 4 (Running)");
                buttons[i].stopTargeting();
                buttons[i].delegateFunctionPress();
                // Do something else.
              } else if (state.isWaiting() == 1) {
                //Serial.println("RELEASED 4 (Waiting)");
                buttons[i].stopTargeting();
                //buttons[i].delegateFunctionRelease();
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
  for (int i = 0; i < (sizeof(thumbSticks) / sizeof(ThumbStick)); ++i) {
    thumbSticks[i].updateHotState();
  }
  //water.updateHotState();
  //proximity.updateHotState();
  //soundDigital.updateHotState();
  //soundAnalog.updateHotState();
  if (IS_DEBUGGING) {
    counter = 0;
    for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
      if (buttons[i].printDefinitions() == 1) {
        ++counter;
      }
    }
    if (counter > 0) {
      Serial.println("");
    }
  }
  for (int i = 0; i < (sizeof(thumbSticks) / sizeof(ThumbStick)); ++i) {
    Serial.print("(");
    thumbSticks[i].printDefinitions();
    Serial.print("), ");
  }
  //water.printDefinitions();
  //Serial.print(", ");
  //proximity.printDefinitions();
  //Serial.print(", ");
  //soundDigital.printDefinitions();
  //Serial.print(", ");
  //soundAnalog.printDefinitions();
  Serial.println();

  if (Serial.available() > 0 && !state.isRunning()) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame
    // application.
    incomingMessage = Serial.read();
    //Serial.println(incomingMessage);
    switch (incomingMessage) {
      case startMessage:
        startFunction();
        break;
      case resetMessage:
        //resetFunction();
        break;
      default:
        break;
    }
  }
  PF(1);
  op ^= 1;
#if PROFILING
  if (seconds % 60 == 3 && !prof_has_dumped) {
    dump_profiling_data();
  }
  if (seconds % 60 == 4 && prof_has_dumped) {
    prof_has_dumped = 0;
  }
#endif
}

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Reset the application.

   RUSCAL:
   - IS_LOGGING <- FALSE

   @startuml
   skinparam shadowing  true
   (*) -right-> "Stop logging"
   -r-> (*)
   @enduml
*/
void resetFunction() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
  IS_LOGGING = false;
}

/**
   Start the application.

   RUSCAL:
   - IS_LOGGING <- TRUE

   @startuml
   skinparam shadowing  true
   (*) -right-> "Start logging"
   -r-> (*)
   @enduml
*/
void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  IS_LOGGING = true;
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
   - timeAccumulated <- timeAccumulated + timeDelta
   - if (timeAccumulated >= TIME_ONE_SECOND)
    + fpsPrevious <- fpsCurrent
    + fpsCurrent <- 0
    + timeAccumulated <- timeAccumulated - TIME_ONE_SECOND
   - else
    + fpsCurrent <- fpsCurrent + 1
   - endif
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
   -r-> "Else add 1 to the current FPS"
   -r-> (*)
   @enduml
*/
bool timer() {
  bool result = true;
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  if (timeDelta < 0) {
    if (IS_LOGGING) {
      Serial.print(millis());
      Serial.print(": ERROR, timeDelta < 0");
    }
    result = false;
  }
  timeAccumulated += timeDelta;
  if (timeAccumulated >= TIME_ONE_SECOND) {
    if (IS_LOGGING || IS_DEBUGGING) {
      Serial.print(millis());
      Serial.print(": FPS, ");
      Serial.println(fpsCurrent);
      Serial.print(millis());
      Serial.print(": freeMemory, ");
      Serial.println(freeMemory());
    }
    fpsPrevious = fpsCurrent;
    fpsCurrent = 0;
    timeAccumulated -= TIME_ONE_SECOND;
  } else {
    ++fpsCurrent;
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
void startButtonFunctionPress() {
  digitalWrite(13, HIGH);
  Serial.println("startButtonFunction()");
}

void startButtonFunctionRelease() {
  digitalWrite(13, LOW);
}

/**
   Empty. The function to call then the Reset button is pressed.
*/
void resetButtonFunctionPress() {
  Serial.println("reset()");
}

void resetButtonFunctionRelease() {

}

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
