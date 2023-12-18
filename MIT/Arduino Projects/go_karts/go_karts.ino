////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file go_karts.ino

   @mainpage go_karts

   @section author Attribution
   - Title: GoKarts file.
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

// 1st-part libraries.
#include "Keyboard.h"
// 2nd-party libraries.
#include "go_karts.h"
// 3rd-party libraries.
#include <MemoryFree.h>

void setup() {
  Serial.begin(BAUD_RATE);
  Keyboard.begin();
  //pinMode(pinSensorProximity, INPUT_PULLUP);
  //pinMode(13, OUTPUT);
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
    //buttons[i].debounceByPosition();
  } else {
    if (proximity.debounceByTimeRelease() == 1) {
      if (proximity.debounceByPositionRelease() == 1) {
        if (proximity.debounceByBlockRelease() == 1) {
          if (proximity.debounceByTargetRelease() == 1) {
            if (state.isRunning() == 1) {
              proximity.stopTargeting();
              proximity.delegateFunctionPress();
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
  if (!isBlocked) {
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
