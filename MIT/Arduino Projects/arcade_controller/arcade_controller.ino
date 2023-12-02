/**
   @file arcade_controller.h

   @mainpage Arcade Controller Project

   @section description Description
   The Arcade Controller.

   @section circuit Circuit
   - Buttons.
   - Switches.

   @section libraries Libraries
   - Serial

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

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section reference Resources
   - Documentation
    + Arduino Due Hardware:
        - Incomplete pinout. https://docs.arduino.cc/hardware/due
        - Complete pinout. https://forum.arduino.cc/t/due-pinout-diagram/129258
    + Software:
        - https://www.arduino.cc/reference/en/
   - Debouncing
    + Time Based:
        - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
    + Current/Previous Based:
        - https://docs.arduino.cc/built-in-examples/digital/Debounce

   @section warnings WARNINGS
   - empty

   @section ut Unit Tests
   - empty
*/

#include "arcade_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  // Sounds.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  // Super pins.
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, OUTPUT);
  // Lights.
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, INPUT_PULLUP);
  // Buttons.
  pinMode(35, INPUT_PULLUP);
  // 36
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  // 40
  pinMode(41, INPUT_PULLUP);
  // Switches.
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
  // Motor.
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  // Misc.
  pinMode(53, INPUT_PULLUP);
  
  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(31, HIGH);
  digitalWrite(32, HIGH);
  digitalWrite(33, HIGH);
  digitalWrite(34, HIGH);
}

/**
 * The main function.
 */
void loop() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.print(digitalRead(18));
  Serial.print(",");
  Serial.print(digitalRead(20));
  Serial.print(",");
  Serial.print(digitalRead(34));
  Serial.print(",");
  Serial.println(digitalRead(53));
  /* Group B
  Serial.print(digitalRead(14));
  Serial.print(",");
  Serial.print(digitalRead(15));
  Serial.print(",");
  Serial.print(digitalRead(44));
  Serial.print(",");
  Serial.println(digitalRead(48));
  */
  /* Group A
  Serial.print(",");
  Serial.print(digitalRead(35));
  Serial.print(",");
  Serial.print(digitalRead(37));
  Serial.print(",");
  Serial.print(digitalRead(38));
  Serial.print(",");
  Serial.print(digitalRead(39));
  Serial.print(",");
  Serial.println(digitalRead(41));
  */
}

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Empty. Reset the application.

   RUSCAL:
   - print (Millis ())
   - print (": ")
   - print ("reset()")
*/
void resetFunction() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
}

/**
   Empty. Start the application.

   RUSCAL:
   - print (Millis ())
   - print (": reset(), ")
   - print (OUTGOING_START)
*/
void startFunction() {
  Serial.print(millis());
  Serial.print(": reset(), ");
  Serial.println(OUTGOING_START);
}
