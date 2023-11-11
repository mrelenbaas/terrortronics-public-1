/*
 * Title: joystick_manager file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the MIT License.
 */

 /**
   @file joystick_manager.ino

   @mainpage joystick_manager

   @section author Attribution
   - Title: Joystick Manager file.
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

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;
 
// Pins.
const int PIN_ONE = 2;
const int PIN_TWO = 4;
const int PIN_THREE = 7;
const int PIN_FOUR = 8;
const int PINS_SIZE = 4;
const int PINS[] = {
  PIN_ONE,
  PIN_TWO,
  PIN_THREE,
  PIN_FOUR
};
int pinIndex;

// Joysticks.
const long DELAY_BETWEEN_JOYSTICKS = 10000;
bool isTurningJoysticksOn;
bool isTurningJoysticksOff;

// Timer.
unsigned long previousTime;
unsigned long currentTime;
unsigned long deltaTime;
unsigned long delayTime;

// Serial.
const int SERIAL_DELAY = 200;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
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
  'j',
  'o',
  'y',
  's',
  't',
  'i',
  'c',
  'k',
  '_',
  'm',
  'a',
  'n',
  'a',
  'g',
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
  '\\',
  'n',
  '\0'
};
int incomingMessage;

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  //Serial.flush();
  for (int i = 0; i < PINS_SIZE; i++) {
    pinMode(PINS[i], OUTPUT);
  }
  currentTime = millis();
}

/**
 * The main function.
 */
void loop() {
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
  } else if (isTurningJoysticksOff /*&& delayTime >= DELAY_BETWEEN_JOYSTICKS*/) { 
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
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case startMessage:
        start();
        break;
      case resetMessage:
        reset();
        break;
      default:
        break;
    }
  }
}

void reset() {
  Serial.println("reset()");
  isTurningJoysticksOn = false;
  isTurningJoysticksOff = true;
  delayTime = 0;
  pinIndex = 0;
}

void start() {
  Serial.println("start()");
  Serial.println(OUTGOING_START);
  isTurningJoysticksOff = false;
  isTurningJoysticksOn = true;
  delayTime = 0;
  pinIndex = 0;
}