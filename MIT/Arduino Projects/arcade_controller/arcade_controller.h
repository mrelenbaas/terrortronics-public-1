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
   - Interrupts
    + https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

   @section warnings WARNINGS
   - empty

   @section ut Unit Tests
   - empty
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
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The board's pins.

   This enumeration uses "pin" as a prefix. The other enumerations use
   their own respective prefix.
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
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   An enum of possible message codes.
*/
enum messages {
  startMessage = pinSound1, ///< Start message.
  resetMessage = pinSound2  ///< Reset message.
};
/**
   The default outgoing message.
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
   The incoming message.
*/
int incomingMessage;

////////////////////////////////////////////////////////////////////////
// Logs ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   If TRUE, then print tracer statements.
*/
bool isLogging = false;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) at the start of the previous loop.
*/
unsigned long timePrevious;
/**
   Time (in milliseconds) at the start of the current loop.
*/
unsigned long timeCurrent;
/**
   The difference between the current and previous loops.
*/
unsigned long timeDelta;
/**
   The accumulated time this second.
*/
unsigned long timeThisSecond;

////////////////////////////////////////////////////////////////////////
// FPS /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) of a single second.
*/
unsigned long TIME_ONE_SECOND = 3000L;
/**
   The current number of frames counted this second.
*/
unsigned long fpsCurrent;
/**
   The number of frames counted over the course of the previous second.
*/
unsigned long fpsPrevious;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
unsigned long DEBOUNCE_PERIOD_START = 10L;
unsigned long DEBOUNCE_PERIOD_STOP = 5L;
enum buttonEnum {
  buttonStart,
  buttonOther
};
int hotButtons[] = { false, false };
ButtonAVR buttons[] = {
  ButtonAVR(pinStart,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            startButtonFunction),
  ButtonAVR(14,
            Timer(),
            DEBOUNCE_PERIOD_START,
            DEBOUNCE_PERIOD_STOP,
            otherButtonFunction)
};

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
State state = State();
