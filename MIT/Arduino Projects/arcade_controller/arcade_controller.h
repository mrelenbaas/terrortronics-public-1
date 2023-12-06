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
 *     + {static} timeThisSecond : unsigned long
 *     + {static} TIME_ONE_SECOND : unsigned long = 3000
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
 *     pinSound1 = 2
 *     pinSound2 = 3
 *     pinSound3 = 4
 *     pinSound4 = 5
 *     pinSound5 = 6
 *     pinSound6 = 7
 *     pinSound7 = 8
 *     pinSound8 = 9
 *     pinSound9 = 10
 *     pinSound10 = 11
 *     pinSound11 = 12
 *     pinSound12 = 13
 *     pinUnused5 = 14
 *     pinUnused6 = 15
 *     pinBuzzer = 16
 *     pinButtonTouch = 17
 *     pinLightError = 18
 *     pinReset = 19
 *     pinLightDebug = 20
 *     pinCount = 21
 *     pinLight1 = 22
 *     pinLight2 = 23
 *     pinLight3 = 24
 *     pinLight4 = 25
 *     pinLight5 = 26
 *     pinLight6 = 27
 *     pinLight7 = 28
 *     pinLight8 = 29
 *     pinLight9 = 30
 *     pinLight10 = 31
 *     pinLight11 = 32
 *     pinLight12 = 33
 *     pinReserved = 34
 *     pinStart = 35
 *     pinUnused1 = 36
 *     pinButton2 = 37
 *     pinButton3 = 38
 *     pinButton4 = 39
 *     pinUnused2 = 40
 *     pinButton5 = 41
 *     pinSwitch1 = 42
 *     pinSwitch2 = 43
 *     pinUnused3 = 44
 *     pinSwitch3 = 45
 *     pinSwitch4 = 46
 *     pinSwitch5 = 47
 *     pinUnused4 = 48
 *     pinSwitch6 = 49
 *     pinSwitch7 = 50
 *     pinMotor1 = 51
 *     pinMotor2 = 52
 *     pinReserved2 = 53
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
 * - Rename messages to messageEnum, and rename its prefixes to match.
 * - Replace the discovery code with IoTivity code.
 * - Rename timeThisSecond to timeAccumulated.
 * - Align the comment styles in CPP file.
 * - Rename isLogging to IS_LOGGING
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
void otherButtonFunction();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The board's pins.
 * 
 * This enumeration uses "pin" as a prefix. The other enumerations use
 * their own respective prefix.
 */
enum pinEnum {
  // Sounds.
  pinSound1 = 2,         ///< Pin 2. Ready sound.
  pinSound2 = 3,         ///< Pin 3. Winner (Cat) sound.
  pinSound3 = 4,         ///< Pin 4. Winner (Dog) sound.
  pinSound4 = 5,         ///< Pin 5. Champion (Cat) sound.
  pinSound5 = 6,         ///< Pin 6. Champion (Dog) sound.
  pinSound6 = 7,         ///< Pin 7. Tie sound.
  pinSound7 = 8,         ///< Pin 8. Stop sound.
  pinSound8 = 9,         ///< Pin 9. One sound.
  pinSound9 = 10,        ///< Pin 10. Two sound.
  pinSound10 = 11,       ///< Pin 11. Three sound.
  pinSound11 = 12,       ///< Pin 12. Tug sound.
  pinSound12 = 13,       ///< Pin 13. Sudden Death sound.
  // Super pins.
  pinUnused5 = 14,       ///< Pin 14. Unused pin #5.
  pinUnused6 = 15,       ///< Pin 15. Unused pin #6.
  pinBuzzer = 16,        ///< Pin 16. Buzzer pin.
  pinButtonTouch = 17,   ///< Pin 17. Reset button.
  pinLightError = 18,    ///< Pin 18. Red debug LED. TODO: Make this player 2C (Left).
  pinReset = 19,         ///< Pin 19. Connect pin to ground.
  pinLightDebug = 20,    ///< Pin 20. Blue debug LED. TODO: Make this player 2C (Right).
  pinCount = 21,         ///< Pin 21. The game count.
  // Lights.
  pinLight1 = 22,        ///< Pin 22. Left Winner light.
  pinLight2 = 23,        ///< Pin 23. Right Winner light.
  pinLight3 = 24,        ///< Pin 24. Left Sudden Death light.
  pinLight4 = 25,        ///< Pin 25. Right Sudden Death light.
  pinLight5 = 26,        ///< Pin 26. Left Champion light.
  pinLight6 = 27,        ///< Pin 27. Right Champion light.
  pinLight7 = 28,        ///< Pin 28. Ready light.
  pinLight8 = 29,        ///< Pin 29. One light.
  pinLight9 = 30,        ///< Pin 30. Two light.
  pinLight10 = 31,       ///< Pin 31. Three light.
  pinLight11 = 32,       ///< Pin 32. Tug light.
  pinLight12 = 33,       ///< Pin 33. Stop light.
  pinReserved = 34,      ///< Pin 34. Reserved pin #1.
  // Buttons.
  pinStart = 35,         ///< Pin 35. Start button.
  pinUnused1 = 36,       ///< Pin 36. Unused pin #1.
  pinButton2 = 37,       ///< Pin 37. Left Player 1 button.
  pinButton3 = 38,       ///< Pin 38. Right Player 1 button.
  pinButton4 = 39,       ///< Pin 39. Left Player 2 button.
  pinUnused2 = 40,       ///< Pin 40. Unused pin #2.
  pinButton5 = 41,       ///< Pin 41. Right Player 2 button.
  // Switches.
  pinSwitch1 = 42,       ///< Pin 42. Left leaf-switch.
  pinSwitch2 = 43,       ///< Pin 43. Leftmost micro-switch.
  pinUnused3 = 44,       ///< Pin 44. Unused pin #3.
  pinSwitch3 = 45,       ///< Pin 44. 1st left-of-center.
  pinSwitch4 = 46,       ///< Pin 46. Center micro-switch.
  pinSwitch5 = 47,       ///< Pin 47. 1st right-of-center.
  pinUnused4 = 48,       ///< Pin 48. Unused pin #4.
  pinSwitch6 = 49,       ///< Pin 49. Right-most micro-switch.
  pinSwitch7 = 50,       ///< Pin 50. Right leaf-switch.
  // Motor.
  pinMotor1 = 51,        ///< Pin 51. Move left.
  pinMotor2 = 52,        ///< Pin 52. Move right.
  // Misc.
  pinReserved2 = 53      ///< Pin 53. Reserved pin #2.
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
enum messages {
  startMessage = pinSound1, ///< Start message.
  resetMessage = pinSound2  ///< Reset message.
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
 * If TRUE, then print tracer statements.
 */
bool isLogging = false;

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
unsigned long timeThisSecond;

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Time (in milliseconds) of a single second.
 */
unsigned long TIME_ONE_SECOND = 3000L;
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
  buttonOther    ///< The Other button index.
};
/**
 * An array of Button elements. Handles the buttons hot state, 
 * debouncing, and callbacks.
 */
ButtonARM buttons[] = {
  ButtonARM(pinStart,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            startButtonFunction),
  ButtonARM(pinUnused5,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            otherButtonFunction)
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
