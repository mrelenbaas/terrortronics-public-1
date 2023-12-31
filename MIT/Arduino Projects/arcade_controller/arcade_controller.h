////////////////////////////////////////////////////////////////////////
// Doxygen Comments ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @file arcade_controller.h

   @mainpage Arcade Controller Project

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
   - Empty.

   @section notes Notes
   - Empty.

   @section warnings WARNINGS
   - Pin 35 releases slowly.

   @section libraries Libraries
   - Serial

   @section circuit Circuit
   - Board
    + Arduino Due
     - The Arduino Due uses "weak" pull-up resistors that are 50k-150k Ohm.
   - Buttons
   \image html arcade_controller_buttons_pullup_resistors.png
   \image latex arcade_controller_buttons_pullup_resistors.eps

   @section pins Pins
   - Pin 2. The start button.
   - Pin 3. The red, top button.
   - Pin 4. The red, bottom button.
   - Pin 5. The green, top button.
   - Pin 6. The green, bottom button.
   - Pin 7. The blue, top button.
   - Pin 8. The blue, bottom button.
   - Pin 9. The yellow, top button.
   - Pin 10. The yellow, bottom button.
   - Pin 11. The black, top button.
   - Pin 12. The black, bottom button.
   - Pin 13. The white, top, button.
   - Pin 14. The white, bottom button.

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
   - Interrupts
    + https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

   @section ut Unit Tests
   - Button shall respond promptly.
    + Set IS_DEBUGGING to true. Observe buttons responding as expected in the usb.exe application.

   @section UMLUseCase UML 2.0 - Use Case Diagram
   Possible Boards
   @startuml
     skinparam shadowing true
     (Arduino)
     (Arduino) --> (Uno)
     (Uno) --> (AVR)
     (Arduino) --> (Micro)
     (Micro) --> (AVR)
     (Arduino) --> (Nano)
     (Nano) --> (AVR)
     (Arduino) --> (Due)
     (Due) --> (ARM)
     (Teensy) --> (LC)
     (LC) --> (ARM)
     (Adafruit) --> (Feather)
     (Feather) --> (ESP32)
   @enduml
   Possible People
   - Natural language description:
    1. The arcade controller automatically starts.
    2. The arcade controller runs forever.
   @startuml
     skinparam shadowing  true
     skinparam actorShadowing false
     Player --> Employee
     Spectator --> Employee
     Attendant --> Employee
     Employee --> (Automatically Start)
     skinparam shadowing<<with_shadow>> true
     Clock --> (Automatically Start)
     Clock --> (Run Forever)
   @enduml

   @section UMLClassDiagram UML 2.0 - Class Diagram
   In this context, the arcade_controller.ino file is equivalent to a
   class.
   @startuml
   package arcade_controller {
     class arcade_controller {
       + {static} BAUD_RATE : const int = 9600
       + {static} OUTGOING_START : const char[0..*] = [
         t,
         y,
         p,
         e,
         :,
         v,
         o,
         n,
         f,
         i,
         ,,
         f,
         i,
         l,
         e,
         n,
         a,
         ,
         e,
         :,
         f,
         p,
         s,
         ,,
         f,
         u,
         n,
         c,
         t,
         i,
         o,
         n,
         :,
         r,
         e,
         e,
         t,
         ,,
         d,
         e,
         l,
         i,
         m,
         i,
         t,
         e,
         r,
         s,
         :,
          ,
         c,
         m,
         0,
         ;,
          ,
         c,
         m,
         l,
         ;,
          ,
         c,
         m,
         2,
         ;,
          ,
         c,
         m,
         3,
         ;,
          ,
         c,
         m,
         4,
         ;,
         \,
         n,
         \0
       ]
       + {static} incomingMessage : int
       + {static} isLogging : bool = false
       + {static} timePrevious : unsigned long
       + {static} timeCurrent : unsigned long
       + {static} timeDelta : unsigned long
       + {static} timeAccumulated : unsigned long
       + {static} TIME_ONE_SECOND : unsigned long = 1000
       + {static} fpsCurrent : unsigned long
       + {static} fpsPrevious : unsigned long
       + {static} DEBOUNCE_PERIOD_START : unsigned long = 10
       + {static} DEBOUNCE_PERIOD_STOP : unsigned long = 5
       + {static} buttons : ButtonARM[0..*] = [
         ButtonARM,
         ButtonARM
       ]
       + {static} state : State
       ]
       --
       + {static} setup()
       + {static} loop()
       + {static} resetFunction()
       + {static} startFunction()
       + {static} timer()
       + {static} interruptFunction()
       + {static} startButtonFunction()
       + {static} otherButtonFunction()
     }
     enum pinEnum {
       pinButtonStart = 2
     }
     enum messages {
       startMessage = pinSound1
       resetmessage = pinSound2
     }
     enum buttonEnum {
       buttonStart,
       bottonOther
     }
   }
   @enduml

   @section todo TODO
   - Replace the discovery code with IoTivity code.
*/

// 2nd-party libraries.
#include "common.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool timer();
void interruptFunction();
void redTopButtonFunctionPress();
void redTopButtonFunctionRelease();
void redBottomButtonFunctionPress();
void redBottomButtonFunctionRelease();
void blueTopButtonFunctionPress();
void blueTopButtonFunctionRelease();
void blueBottomButtonFunctionPress();
void blueBottomButtonFunctionRelease();
void greenTopButtonFunctionPress();
void greenTopButtonFunctionRelease();
void greenBottomButtonFunctionPress();
void greenBottomButtonFunctionRelease();
void yellowTopButtonFunctionPress();
void yellowTopButtonFunctionRelease();
void yellowBottomButtonFunctionPress();
void yellowBottomButtonFunctionRelease();
void blackTopButtonFunctionPress();
void blackTopButtonFunctionRelease();
void blackBottomButtonFunctionPress();
void blackBottomButtonFunctionRelease();
void whiteTopButtonFunctionPress();
void whiteTopButtonFunctionRelease();
void whiteBottomButtonFunctionPress();
void whiteBottomButtonFunctionRelease();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The board's pins. Named with the [pin + type + name] convention,
   while other enums are named with the [type + name] convention.
*/
enum pinEnum {
  // A4. Avoid - I2C.
  // A5. Avoid - I2C.
  // 2. Avoid - I2C.
  // 3. Avoid - I2C.
  pinButtonStart = 4,          ///< Pin 2. Start button.
  pinButtonReset = 5,          ///< Pin 3. Reset button.
  pinButtonRedTop = 6,         ///< Pin 4. Red button (top).
  pinButtonRedBottom = 7,      ///< Pin 5. Red button (bottom).
  pinButtonGreenTop = 8,       ///< Pin 6. Green button (top).
  pinButtonGreenBottom = 9,    ///< Pin 7. Green button (bottom).
  pinButtonBlueTop = 10,       ///< Pin 8 Blue button (top).
  pinButtonBlueBottom = 11,    ///< Pin 9. Blue button (bottom).
  pinButtonYellowTop = 12,     ///< Pin 10. Yellow button (top).
  pinLightDebug = 13,
  pinButtonYellowBottom = 14,  ///< Pin 11. Yellow button (bottom).
  pinButtonBlackTop = 15,      ///< Pin 12. Black button (top).
  pinButtonBlackBottom = 16,   ///< Pin 13. Black button (bottom).
  pinButtonWhiteTop = 17,      ///< Pin 14. White button (top).
  pinButtonWhiteBottom = 18,   ///< Pin 15. White button (bottom).
  // 20. Avoid - I2C. Used on Feather.
  // 21. Avoid - I2C. Used on Feather.
  pinGround = 53
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Logging logging = Logging();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The incoming message.
*/
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
SentinelTimer sentinelTimer = SentinelTimer();

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
FPS fps = FPS();

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The debounce period before a Press is considered valid.
*/
unsigned long DEBOUNCE_PERIOD_START = 10L;
/**
   The debounce period before a Release is considered valid.
*/
unsigned long DEBOUNCE_PERIOD_STOP = 5L;
/**
   An enum paired with the buttons and hotButtons.
*/
enum buttonEnum {
  buttonStart,   ///< The Start button index.
  buttonRedTop   ///< The Other button index.
};
/**
   An array of Button elements. Handles the buttons hot state,
   debouncing, and callbacks.
*/
ButtonARM buttons[] = {
  ButtonARM(
    pinButtonStart,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    startButtonFunctionPress,
    startButtonFunctionRelease),
  ButtonARM(
    pinButtonReset,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    resetButtonFunctionPress,
    resetButtonFunctionRelease),
  ButtonARM(
    pinButtonRedTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    redTopButtonFunctionPress,
    redTopButtonFunctionRelease),
  ButtonARM(
    pinButtonRedBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    redBottomButtonFunctionPress,
    redBottomButtonFunctionRelease),
  ButtonARM(
    pinButtonGreenTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    blueTopButtonFunctionPress,
    blueTopButtonFunctionRelease),
  ButtonARM(
    pinButtonGreenBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    blueBottomButtonFunctionPress,
    blueBottomButtonFunctionRelease),
  ButtonARM(
    pinButtonBlueTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    greenTopButtonFunctionPress,
    greenTopButtonFunctionRelease),
  ButtonARM(
    pinButtonBlueBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    greenBottomButtonFunctionPress,
    greenBottomButtonFunctionRelease),
  ButtonARM(
    pinButtonYellowTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    yellowTopButtonFunctionPress,
    yellowTopButtonFunctionRelease),
  ButtonARM(
    pinButtonYellowBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    yellowBottomButtonFunctionPress,
    yellowBottomButtonFunctionRelease),
  ButtonARM(
    pinButtonBlackTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    blackTopButtonFunctionPress,
    blackTopButtonFunctionRelease),
  ButtonARM(
    pinButtonBlackBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    blackBottomButtonFunctionPress,
    blackBottomButtonFunctionRelease),
  ButtonARM(
    pinButtonWhiteTop,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    whiteTopButtonFunctionPress,
    whiteTopButtonFunctionRelease),
  ButtonARM(
    pinButtonWhiteBottom,
    Timer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    whiteBottomButtonFunctionPress,
    whiteBottomButtonFunctionRelease)
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum lightEnum {
  lightDebug
};

Light lights[] = {
  Light(pinLightDebug)
};

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int result;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
