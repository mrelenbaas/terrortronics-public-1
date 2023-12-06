/**
 * @file arcade_controller.h
 * 
 * @mainpage Arcade Controller Project
 * 
 * @section description Description
 * The Arcade Controller.
 * 
 * @section notes Notes
 * - The Overview section of the Doxygen docs does not include print
 * statements. The inline comments are the same as the Overview
 * section, but they do include print statements.
 * 
 * @section author Author
 * - Bradley Elenbaas (mr.elenbaas@gmail.com)
 * - Version: 2
 * - Date: November 29, 2023
 * 
 * @section ip Intellectual Property
 * Copyright (c) 2023 Bradley Elenbaas. All rights
 * reserved.
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
 * @section circuit Circuit
 * - Buttons.
 * - Switches.
 * 
 * @section libraries Libraries
 * - Serial
 * 
 * @section description Description
 * Empty.

 * @section pins Pins
 * - empty
 * 
 * @section reference Resources
 * - Documentation
 *  + Arduino Due Hardware:
 *      - Incomplete pinout. https://docs.arduino.cc/hardware/due
 *      - Complete pinout. https://forum.arduino.cc/t/due-pinout-diagram/129258
 *  + Software:
 *      - https://www.arduino.cc/reference/en/
 * - Debouncing
 *  + Time Based:
 *      - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
 *  + Current/Previous Based:
 *      - https://docs.arduino.cc/built-in-examples/digital/Debounce
 * - Interrupts
 *  + https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * @section warnings WARNINGS
 * - empty
 * 
 * @section ut Unit Tests
 * - empty
 * 
 * @section UMLUseCase UML 2.0 - Use Case Diagram
 * Possible Boards
 * @startuml
 *   skinparam shadowing true
 *   (Arduino)
 *   (Arduino) --> (Uno)
 *   (Uno) --> (AVR)
 *   (Arduino) --> (Micro)
 *   (Micro) --> (AVR)
 *   (Arduino) --> (Nano)
 *   (Nano) --> (AVR)
 *   (Arduino) --> (Due)
 *   (Due) --> (ARM)
 *   (Teensy) --> (LC)
 *   (LC) --> (ARM)
 *   (Adafruit) --> (Feather)
 *   (Feather) --> (ESP32)
 * @enduml
 * Possible People
 * - Natural language description:
 *  1. The arcade controller automatically starts.
 *  2. The arcade controller runs forever.
 * @startuml
 *   skinparam shadowing  true
 *   skinparam actorShadowing false
 *   Player --> Employee
 *   Spectator --> Employee
 *   Attendant --> Employee
 *   Employee --> (Automatically Start)
 *   skinparam shadowing<<with_shadow>> true
 *   Clock --> (Automatically Start)
 *   Clock --> (Run Forever)
 * @enduml
 * 
 * @section UMLClassDiagram UML 2.0 - Class Diagram
 * In this context, the arcade_controller.ino file is equivalent to a 
 * class.
 * @startuml
 * package arcade_controller {
 *   class arcade_controller {
 *     + {static} BAUD_RATE : const int = 9600
 *     + {static} OUTGOING_START : const char[0..*] = [
 *       t,
 *       y,
 *       p,
 *       e,
 *       :,
 *       v,
 *       o,
 *       n,
 *       f,
 *       i,
 *       ,,
 *       f,
 *       i,
 *       l,
 *       e,
 *       n,
 *       a,
 *       ,
 *       e,
 *       :,
 *       f,
 *       p,
 *       s,
 *       ,,
 *       f,
 *       u,
 *       n,
 *       c,
 *       t,
 *       i,
 *       o,
 *       n,
 *       :,
 *       r,
 *       e,
 *       e,
 *       t,
 *       ,,
 *       d,
 *       e,
 *       l,
 *       i,
 *       m,
 *       i,
 *       t,
 *       e,
 *       r,
 *       s,
 *       :,
 *        ,
 *       c,
 *       m,
 *       0,
 *       ;,
 *        ,
 *       c,
 *       m,
 *       l,
 *       ;,
 *        ,
 *       c,
 *       m,
 *       2,
 *       ;,
 *        ,
 *       c,
 *       m,
 *       3,
 *       ;,
 *        ,
 *       c,
 *       m,
 *       4,
 *       ;,
 *       \,
 *       n,
 *       \0
 *     ]
 *     + {static} incomingMessage : int
 *     + {static} isLogging : bool = false
 *     + {static} timePrevious : unsigned long
 *     + {static} timeCurrent : unsigned long
 *     + {static} timeDelta : unsigned long
 *     + {static} timeAccumulated : unsigned long
 *     + {static} TIME_ONE_SECOND : unsigned long = 1000
 *     + {static} fpsCurrent : unsigned long
 *     + {static} fpsPrevious : unsigned long
 *     + {static} DEBOUNCE_PERIOD_START : unsigned long = 10
 *     + {static} DEBOUNCE_PERIOD_STOP : unsigned long = 5
 *     + {static} buttons : ButtonARM[0..*] = [
 *       ButtonARM,
 *       ButtonARM
 *     ]
 *     + {static} state : State
 *     ]
 *     --
 *     + {static} setup()
 *     + {static} loop()
 *     + {static} resetFunction()
 *     + {static} startFunction()
 *     + {static} timer()
 *     + {static} interruptFunction()
 *     + {static} startButtonFunction()
 *     + {static} otherButtonFunction()
 *   }
 *   enum pinEnum {
 *     pinButtonStart = 2
 *   }
 *   enum messages {
 *     startMessage = pinSound1
 *     resetmessage = pinSound2
 *   }
 *   enum buttonEnum {
 *     buttonStart,
 *     bottonOther
 *   }
 * }
 * @enduml
 * 
 * @section todo TODO
 * - Replace the discovery code with IoTivity code.
 */

#include "common.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction();
void startFunction();
bool timer();
void interruptFunction();
void startButtonFunction();
void redTopButtonFunction();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The board's pins.
 */
enum pinEnum {
  pinButtonStart = 2,
  pinButtonRedTop = 3
};

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
enum messageEnum {
  messageStart = 48, ///< Start message.
  messageReset = 49  ///< Reset message.
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
  'f',
  'p',
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
 * If TRUE, then print logging tracers.
 */
bool IS_LOGGING = false;
/**
 * If TRUE, then print debug tracers.
 */
bool IS_DEBUGGING = false;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Time (in milliseconds) at the start of the previous loop.
 */
unsigned long timePrevious;
/**
 * Time (in milliseconds) at the start of the current loop.
 */
unsigned long timeCurrent;
/**
 * The difference between the current and previous loops.
 */
unsigned long timeDelta;
/**
 * The accumulated time this second.
 */
unsigned long timeAccumulated;

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Time (in milliseconds) of a single second.
 */
unsigned long TIME_ONE_SECOND = 1000L;
/**
 * The current number of frames counted this second.
 */
unsigned long fpsCurrent;
/**
 * The number of frames counted over the course of the previous second.
 */
unsigned long fpsPrevious;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The debounce period before a Press is considered valid.
 */
unsigned long DEBOUNCE_PERIOD_START = 10L;
/**
 * The debounce period before a Release is considered valid.
 */
unsigned long DEBOUNCE_PERIOD_STOP = 5L;
/**
 * An enum paired with the buttons and hotButtons.
 */
enum buttonEnum {
  buttonStart,   ///< The Start button index.
  buttonRedTop   ///< The Other button index.
};
/**
 * An array of Button elements. Handles the buttons hot state, 
 * debouncing, and callbacks.
 */
ButtonARM buttons[] = {
  ButtonARM(pinButtonStart,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            startButtonFunction),
  ButtonARM(pinButtonRedTop,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            redTopButtonFunction)
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The state of the game.
 */
State state = State();

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
