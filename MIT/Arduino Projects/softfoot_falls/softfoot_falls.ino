/*
   Title: SoftfootFalls file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

/**
 * @file SoftfootFalls.ino
 *
 * @mainpage SoftfootFalls Arduino Project
 *
 * @section description Description
 * The Arduino component to SoftfootFalls.
 *
 * @section circuit Circuit
 * - D2 - Input. Momentary push button, 68 Ohms resistor, and LED.
 * - D3 - Output. 68 Ohm resistor, and LED.
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
