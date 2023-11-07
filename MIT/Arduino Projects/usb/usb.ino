/*
   Title: usb file.
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
   @file usb.ino

   @mainpage usb

   @section author Attribution
   - Title: USB file.
   - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: September 25, 2023.

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
   The USB library.

   @section pins Pins
   - empty

   @section resources Resources
   - https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide?gclid=CjwKCAjwh4ObBhAzEiwAHzZYU9fWXPNZrw8oHU1V8xxeILSFGz1O_08SyU8i6gU0pNtaYeBZTgg0exoCMEQQAvD_BwE
   - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
   - https://arduinogetstarted.com/faq/how-to-reset-arduino-by-programming

   @section warnings WARNINGS
   - DO NO USE THIS EXAMPLE (https://reference.arduino.cc/reference/en/language/functions/communication/serial/readstring/) (Reason #1): The readString function may cause memory leaks.
   - DO NO USE THIS EXAMPLE (https://reference.arduino.cc/reference/en/language/functions/communication/serial/readstring/) (Reason #2): The Serial blocking code breaks on Unity Standalone Windows builds.
   - DO NOT USE the pySerial.write() call inside any PyGame code, and instead use the Thread library to seperate their respective blocks with flags to move data back and forth.
*/

/*
 * Unit Test #1: Does this work with the USB Unity project?
 */


////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;
///////////////////////////////////////////////////////////////////////////////
// endregion Serial ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// region Incoming Data ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * Associated with the \ref start() function.
 */
const int START_MESSAGE = 48;
/**
 * Associated with the \ref reset() function.
 */
const int RESET_MESSAGE = 49;
/**
 * An enum for parsing an incoming byte.
 * Starts with ASCII 0 (48) and goes up from there.
 */
enum messages {
  startMessage = START_MESSAGE,
  resetMessage = RESET_MESSAGE
};
/**
 * A single incoming byte.
 */
int incomingMessage;
///////////////////////////////////////////////////////////////////////////////
// endregion Incoming Data ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// region Outgoing Data ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * The config to be parsed by a PC application.
 */
const String CONFIG = "type:config,filename:joystick_manager,function:reset,delimiters: cm0;\n";
/**
 * The maximum count for \ref counter.
 */
int COUNTER_MAX = 4;
/**
 * The counter to be output.
 */
int counter;
///////////////////////////////////////////////////////////////////////////////
// endregion Outgoing Data ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// region Arduino Structure Functions /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
   Set up Serial.
*/
void setup() {
  Serial.begin(BAUD_RATE);
}

/**
 * The main function.
 * 
 * @section warning WARNING
 * - Remember to consume the incoming bytes.
 *   - The error does not occur when using the usb.c or usb.py files.
 *   - The error does occur when reading/writing in a PyGame application.
 */
void loop() {
  Serial.print(counter);
  Serial.println(" cm0");
  counter++;
  if (counter > COUNTER_MAX) {
    counter = 0;
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
///////////////////////////////////////////////////////////////////////////////
// endregion Arduino Structure Functions //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// region Private Functions ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * A stub function to be populated on a per-project basis.
 */
void reset() {
  Serial.println("reset()");
}

/**
 * Outputs the \ref CONFIG string.
 */
void start() {
  Serial.println("start()");
  Serial.println(CONFIG);
}
///////////////////////////////////////////////////////////////////////////////
// region Private Functions ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
