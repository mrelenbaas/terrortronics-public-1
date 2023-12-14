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
  // open the serial port:
  Serial.begin(BAUD_RATE);
  // initialize control over the keyboard:
  Keyboard.begin();

  //for (int i = 0; i < PINS_SIZE; i++) {
  //  pinMode(PINS[i], INPUT_PULLUP);
  //}
  pinMode(pinButtonStart, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  //Keyboard.write("HERE");
}

/**
   The main function.
*/
void loop() {
  if (digitalRead(2) == LOW) {
    digitalWrite(13, HIGH);
    //Keyboard.write("HERE");
    //Keyboard.press('p');
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
  } else {
    digitalWrite(13, LOW);
    //Keyboard.press('p');
  }
  /*
    buttonBlockResult = true;
    if (buttonBlock) {
    for (int i = 0; i < PINS_SIZE; i++) {
      if (digitalRead(PINS[i]) == LOW) {
        buttonBlockResult = false;
        delay(DELAY_AFTER_BUTTON_RELEASE);
      }
    }
    if (buttonBlockResult) {
      buttonBlock = false;
    }
    }
    if (buttonBlock == false) {
    if (digitalRead(ORANGE) == LOW) {
      //openNewTerminal();
      pressKeys("cd ~/iotivity-lite/port/linux/");
      pressKeys("python3 gokarts.py");
    }
    else if (digitalRead(GREEN) == LOW) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      delay(DELAY_AFTER_SPACE);
      Keyboard.releaseAll();
      delay(DELAY_AFTER_SPACE);
    }
    else if (digitalRead(PURPLE) == LOW) {
      //openNewTerminal();
      pressKeys("cd ~/iotivity-lite/port/linux/");
      pressKeys("./simpleserver");
    }
    else if (digitalRead(WHITE) == LOW) {
      openNewTerminal();
    }
    }
  */
  //Serial.println(millis());

  if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame
    // application.
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case startMessage:
        startFunction();
        break;
      case resetMessage:
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
  isLogging = false;
}

void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  isLogging = true;
}
