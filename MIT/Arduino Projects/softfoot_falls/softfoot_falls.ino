/*
   Title: SoftfootFalls file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the MIT License.
*/

/**
   @file softfoot_falls.ino

   @mainpage softfoot_falls

   @section author Attribution
   - Title: SoftfootFalls file.
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
   - D2 - Input. Momentary push button, 68 Ohms resistor, and LED.
   - D3 - Output. 68 Ohm resistor, and LED.

   @section resources Resources
   - empty

   @section warnings WARNINGS
   - empty
*/

 // TODO: Use the profiler for something.
 // TODO: Use the timer to upgrade the current timer setup.
 // TODO: The *er namespace was an okay idea, but there is other (newer) documentatin to avoid overlapping names.

#include <HardwareSerial.h>

#include "game.h"

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

Game game; ///< Game manager.

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:ultrasonic_sensor,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;


/**
 * Main setup.
 */
void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);
  //profile_setup();
  //game.starter();
  
}

/**
   The main function.
*/
void loop() {
  //bool result = timer.updater();
  //if(result) {
    
    //int some_counter = 0;
    //for(int i = 0 ; i < PROFILE_SIZE ; i++) {
    //  some_counter += profile_array[i];
    //}
    //game.updater_other(0, 0, 0, 0);
    //Serial.println("something");
    
    //profile_dump();
  //}
  game.updater();
  if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame application.
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
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
