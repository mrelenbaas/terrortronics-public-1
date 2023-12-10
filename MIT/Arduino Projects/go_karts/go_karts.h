/**
 * @file go_karts.h
 * 
 * @mainpage go_karts
 * 
 * @section author Attribution
 * - Title: GoKarts file.
 * - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * - Version: 2
 * - Date: November 6, 2023.
 * 
 * @section ip Intellectual Property
 * - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 * 
 * @section license License
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section description Description
 * Empty.
 * 
 * @section pins Pins
 * - empty
 * 
 * @section resources Resources
 * - empty
 * 
 * @section warnings WARNINGS
 * - empty
 */

// Include 1st-party libraries.
#include "Keyboard.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction();
void startFunction();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The serial baud rate.
 */
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * An enum of possible message codes.
 */
enum messages {
  startMessage = 48,
  resetMessage = 49
};
/**
 * The default outgoing message.
 */
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
  'g',
  'o',
  '_',
  'k',
  'a',
  'r',
  't',
  's',
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
  ',',
  'd',
  'e',
  'l',
  'i',
  'm',
  'i',
  't',
  'e',
  'r',
  's',
  ':',
  ' ',
  'c',
  'm',
  '0',
  ';',
  ' ',
  'c',
  'm',
  '1',
  ';',
  ' ',
  'c',
  'm',
  '2',
  ';',
  ' ',
  'c',
  'm',
  '3',
  ';',
  ' ',
  'c',
  'm',
  '4',
  ';',
  '\\',
  'n',
  '"',
  '\0'
};
/**
 * The incoming message.
 */
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * If TRUE, then print tracer statements.
 */
bool isLogging;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

const int PINS_SIZE = 4;
const int ORANGE = 2;
const int GREEN = 3;
const int PURPLE = 4;
const int WHITE = 5;
int PINS[] = {
  ORANGE,
  GREEN,
  PURPLE,
  WHITE
};

const long DELAY_AFTER_SPACE = 2000;
const long DELAY_AFTER_BUTTON_RELEASE = 20; // Debounce.
const long DELAY_BETWEEN_KEY_PRESS = 10;

bool buttonBlock;
bool buttonBlockResult;

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
