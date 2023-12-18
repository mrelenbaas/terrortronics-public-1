/**
   @file go_karts.ino

   @mainpage go_karts

   @section author Attribution
   - Title: GoKarts file.
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

   @section circuit Circuit
   - Board
    + Arduino Micro
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

// Include 1st-part libraries.
#include "Keyboard.h"
// Include 2nd-party libraries.
#include "go_karts.h"

/*
  void openNewTerminal() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('t');
  Keyboard.releaseAll();
  delay(DELAY_AFTER_SPACE);
  }
*/

/*
  void pressKeys(String keys) {
  buttonBlock = true;
  for (int i = 0; i < keys.length(); i++) {
    Keyboard.press(keys[i]);
    delay(DELAY_BETWEEN_KEY_PRESS);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_RETURN);
  }
*/

void setup() {
  Serial.begin(BAUD_RATE);
  Keyboard.begin();

  //for (int i = 0; i < PINS_SIZE; i++) {
  //  pinMode(PINS[i], INPUT_PULLUP);
  //}
  pinMode(pinSensorProximity, INPUT_PULLUP);
  pinMode(13, OUTPUT);
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
  /*
    //Serial.println(digitalRead(6));
    if (digitalRead(pinSensorProximity) == LOW) {
    Serial.println("ON");
    //digitalWrite(pinButtonStart, HIGH);
    } else {
    Serial.println("");
    //digitalWrite(pinButtonStart, LOW);
    }
  */
  //for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
  if (proximity.updateHotState() == 1) {
    //Serial.println("PRESSED 0");
    if (proximity.debounceByTimePress() == 1) {
      //Serial.println("PRESSED 1");
      if (proximity.debounceByPositionPress() == 1) {
        //Serial.println("PRESSED 2");
        if (proximity.debounceByBlockPress() == 1) {
          //Serial.println("PRESSED 3");
          if (proximity.debounceByTargetPress() == 1) {
            if (state.isRunning() == 1) {
              //Serial.println("PRESSED 4 (Running)");
            } else if (state.isWaiting() == 1) {
              //Serial.println("PRESSED 4 (Waiting)");
            }
          }
          proximity.delegateFunctionPress();
        }
      }
    }
    //buttons[i].debounceByPosition();
  } else {
    //Serial.println("RELEASED 0");
    if (proximity.debounceByTimeRelease() == 1) {
      //Serial.println("RELEASED 1");
      if (proximity.debounceByPositionRelease() == 1) {
        //Serial.println("RELEASED 2");
        if (proximity.debounceByBlockRelease() == 1) {
          //Serial.println("RELEASED 3");
          if (proximity.debounceByTargetRelease() == 1) {
            if (state.isRunning() == 1) {
              //Serial.println("RELEASED 4 (Running)");
              proximity.stopTargeting();
              proximity.delegateFunctionPress();
              // Do something else.
            } else if (state.isWaiting() == 1) {
              //Serial.println("RELEASED 4 (Waiting)");
              proximity.stopTargeting();
              //buttons[i].delegateFunctionRelease();
            }
          }
          proximity.delegateFunctionRelease();
        }
      }
      proximity.reset();
    }
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
  IS_LOGGING = false;
}

void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  IS_LOGGING = true;
}

////////////////////////////////////////////////////////////////////////
// Delegates ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startButtonFunctionPress() {
  digitalWrite(13, HIGH);
  Serial.println("startButtonFunction()");
  if (!IS_DEBUGGING) {
    if (!isBlocked) {
      // Replace this section with automatic connection to the network.
      Keyboard.press(KEY_LEFT_ALT);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.press(KEY_TAB);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_TAB);
      Keyboard.press('a');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('a');
      Keyboard.press('d');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('d');
      Keyboard.press('m');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('m');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('n');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('n');
      Keyboard.press(KEY_TAB);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_TAB);
      Keyboard.press('p');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('p');
      Keyboard.press('a');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('a');
      Keyboard.press('s');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('s');
      Keyboard.press('s');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('s');
      Keyboard.press('w');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('w');
      Keyboard.press('o');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('o');
      Keyboard.press('r');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('r');
      Keyboard.press('d');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('d');
      Keyboard.press(KEY_RETURN);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_RETURN);

      delay(5000);
      Keyboard.press(KEY_LEFT_CTRL);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.press('q');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release('q');

      // Keep this section below.
      delay(5000);
      Keyboard.press(KEY_LEFT_CTRL);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.press(KEY_LEFT_ALT);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.press('t');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release('t');

      delay(10000);
      Keyboard.press('.');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('.');
      Keyboard.press('/');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('/');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('o');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('o');
      Keyboard.press('t');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('t');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('v');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('v');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('t');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('t');
      Keyboard.press('y');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('y');
      Keyboard.press('-');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('-');
      Keyboard.press('l');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('l');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('t');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('t');
      Keyboard.press('e');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('e');
      Keyboard.press('/');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('/');
      Keyboard.press('p');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('p');
      Keyboard.press('o');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('o');
      Keyboard.press('r');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('r');
      Keyboard.press('t');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('t');
      Keyboard.press('/');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('/');
      Keyboard.press('l');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('l');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('n');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('n');
      Keyboard.press('u');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('u');
      Keyboard.press('x');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('x');
      Keyboard.press('/');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('/');
      Keyboard.press('s');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('s');
      Keyboard.press('i');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('i');
      Keyboard.press('m');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('m');
      Keyboard.press('p');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('p');
      Keyboard.press('l');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('l');
      Keyboard.press('e');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('e');
      Keyboard.press('s');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('s');
      Keyboard.press('e');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('e');
      Keyboard.press('r');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('r');
      Keyboard.press('v');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('v');
      Keyboard.press('e');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('e');
      Keyboard.press('r');
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release('r');
      Keyboard.press(KEY_RETURN);
      delay(DELAY_BETWEEN_KEY_PRESS);
      Keyboard.release(KEY_RETURN);
      isBlocked = true;
    }
  }
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

void proximityButtonFunctionPress() {
  Serial.println("proximityButtonFunctionPress()");
  lights[lightDebug].turnOn();
}

void proximityButtonFunctionRelease() {
  Serial.println("proximityButtonFunctionRelease()");
  lights[lightDebug].turnOff();
}
