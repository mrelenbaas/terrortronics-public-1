////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file joystick_manager.ino

   @mainpage joystick_manager

   @section author Attribution
   - Title: Joystick Manager file.
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

   @section circuit Circuit
   - Board
    + Arduino Uno
   - Buttons

   @section libraries Libraries
   - Serial

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - empty

   @section warnings WARNINGS
   - empty
*/

// 2nd-party libraries.
#include "game_pad_manager.h"

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.flush();
  for (int i = 0; i < PINS_SIZE; i++) {
    pinMode(PINS[i], OUTPUT);
  }
  //pinMode(pinButtonStart, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(13, HIGH);
}

/**
   The main function.
*/
void loop() {
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

  //delay(SERIAL_DELAY);
  Serial.println(millis());
  previousTime = currentTime;
  currentTime = millis();
  deltaTime = currentTime - previousTime;
  delayTime += deltaTime;
  if ((isTurningJoysticksOn && delayTime >= DELAY_BETWEEN_JOYSTICKS)
      || (isTurningJoysticksOn && pinIndex == 0)) {
    digitalWrite(PINS[pinIndex], HIGH);
    delayTime = 0;
    pinIndex++;
    if (pinIndex >= PINS_SIZE) {
      isTurningJoysticksOn = false;
    }
  } else if (isTurningJoysticksOff) {
    //digitalWrite(PINS[pinIndex], LOW);
    delayTime = 0;
    //pinIndex++;
    //if (pinIndex >= PINS_SIZE) {
    //  isTurningJoysticksOff = false;
    //}
    for (int i = 0; i < PINS_SIZE; i++) {
      digitalWrite(PINS[i], LOW);
    }
    isTurningJoysticksOff = false;
  }
  if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame
    // application.
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


void resetFunction() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
  isTurningJoysticksOn = false;
  isTurningJoysticksOff = true;
  delayTime = 0;
  pinIndex = 0;
}

void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  isTurningJoysticksOff = false;
  isTurningJoysticksOn = true;
  delayTime = 0;
  pinIndex = 0;
}

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
