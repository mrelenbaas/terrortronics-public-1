/**
   @file super_tug_of_war.h

   @mainpage Super Tug-of-War Project

   @section description Description
   The Super Tug-of-War game.

   @section circuit Circuit
   - Buttons.
   - Switches.

   @section libraries Libraries
   - Serial

   @section notes Notes
   - The Overview section of the Doxygen docs does not include print 
   statements. The inline comments are the same as the Overview 
   section, but they do include print statements.

   @section todo TODO
   - TODO: Test count pin.
   - TODO: Remove uses of "Details" in Doxygen.
   - TODO: Prefix the enums the same as the pinEnum.
   - TODO: Dismantle the one, five, and ten second timers for
     individual timers.
   - TODO: Wrap print statements behind a bool.
   - TODO: Implement the startFunction() function.
   - TODO: Implement the resetFunction() function.

   @section author Author
   - Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 8, 2023

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
    + Hardware:
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
*/

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Sounds.
void playSound();
// Lights.
// Buttons.
void updateButtons();
// Switches.
void updateSwitches();
// Motor.
void setTarget(int index);
// Serial.
// Debounce by time.
void debounceSwitchByTime(int i);
void debounceSwitchesByTime();
// Debounce by position.
void debounceSwitchesByPosition();
// Debounce by frame.
// States.
// Scores.
void calculateResults();
// Tug sequences.
void stopTugSegment();
void stopTugSequence();
// Routing.
bool preRouteResults();
void routeResults();
void routeResults2();
void routeResults3();
// Timers.
void startReadyFromWinnerStop15();
void startReadyFromWinnerStop234();
void stopChampion();
void stopCount();
void stopIsTugOn();
void stopReadyTimer();
void stopSoundTimer();
void stopStopTimer();
void stopSuddenDeathBlinking();
void stopTie();
void stopWinnerTimer();
// Messages.
void resetFunction();
void startFunction();
// Multi-color LED.
// Errors.
bool errorCheckContactSwitches();
bool errorCheckPluralInput();
// Debug.

void routeButtons();
void startStop();
void stopFiveSecondTimer();
void stopFiveSecondTimer2();
void stopFourSecondTimer();
void stopOneSecondTimer();
void stopTenSecondTimer();
void stopToggleTimer();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The board's pins.

   This enumeration uses "pin" as a prefix. The other enumerations do
   not use any prefix.

   Overview:
   - Sounds: 2-13.
   - Super Tug-of-War: 14-21.
   - Lights: 22-33.
   - Buttons: 35-41.
   - Switches: 42-50.
   - Motor: 51-52.
   - Unsused (broken): 14, 15, 36, 40, 44, and 48.
   - Reserved: 34 and 53.
*/
enum pinEnum {
  // Sounds.
  pinSoundReady = 2,             ///< Pin 2. Ready sound.
  pinSoundCatWinner = 3,         ///< Pin 3. Winner (Cat) sound.
  pinSoundDogWinner = 4,         ///< Pin 4. Winner (Dog) sound.
  pinSoundCatChampion = 5,       ///< Pin 5. Champion (Cat) sound.
  pinSoundDogChampion = 6,       ///< Pin 6. Champion (Dog) sound.
  pinSoundTie = 7,               ///< Pin 7. Tie sound.
  pinSoundStop = 8,              ///< Pin 8. Stop sound.
  pinSoundOne = 9,               ///< Pin 9. One sound.
  pinSoundTwo = 10,              ///< Pin 10. Two sound.
  pinSoundThree = 11,            ///< Pin 11. Three sound.
  pinSoundTug = 12,              ///< Pin 12. Tug sound.
  pinSoundSuddenDeath = 13,      ///< Pin 13. Sudden Death sound.
  // Super pins.
  pinUnused5 = 14,               ///< Pin 14. Unused pin #5.
  pinUnused6 = 15,               ///< Pin 15. Unused pin #6.
  pinBuzzer = 16,                ///< Pin 16. Buzzer pin.
  pinButtonTouch = 17,           ///< Pin 17. Reset button.
  pinLightError = 18,            ///< Pin 18. Red debug LED. TODO: Make this player 2C (Left).
  pinReset = 19,                 ///< Pin 19. Connect pin to ground.
  pinLightDebug = 20,            ///< Pin 20. Blue debug LED. TODO: Make this player 2C (Right).
  pinCount = 21,                 ///< Pin 21. The game count.
  // Lights.
  pinLightWinnerLeft = 22,       ///< Pin 22. Left Winner light.
  pinLightWinnerRight = 23,      ///< Pin 23. Right Winner light.
  pinLightSuddenDeathLeft = 24,  ///< Pin 24. Left Sudden Death light.
  pinLightSuddenDeathRight = 25, ///< Pin 25. Right Sudden Death light.
  pinLightChampionLeft = 26,     ///< Pin 26. Left Champion light.
  pinLightChampionRight = 27,    ///< Pin 27. Right Champion light.
  pinLightReady = 28,            ///< Pin 28. Ready light.
  pinLightOne = 29,              ///< Pin 29. One light.
  pinLightTwo = 30,              ///< Pin 30. Two light.
  pinLightThree = 31,            ///< Pin 31. Three light.
  pinLightTug = 32,              ///< Pin 32. Tug light.
  pinLightStop = 33,             ///< Pin 33. Stop light.
  pinReserved = 34,              ///< Pin 34. Reserved pin #1.
  // Buttons.
  pinButtonStart = 35,           ///< Pin 35. Start button.
  pinUnused1 = 36,               ///< Pin 36. Unused pin #1.
  pinButtonPlayer1Left = 37,     ///< Pin 37. Left Player 1 button.
  pinButtonPlayer1Right = 38,    ///< Pin 38. Right Player 1 button.
  pinButtonPlayer2Left = 39,     ///< Pin 39. Left Player 2 button.
  pinUnused2 = 40,               ///< Pin 40. Unused pin #2.
  pinButtonPlayer2Right = 41,    ///< Pin 41. Right Player 2 button.
  // Switches.
  pinSwitchLeftMax = 42,         ///< Pin 42. Left leaf-switch.
  pinSwitchLeft3 = 43,           ///< Pin 43. Leftmost micro-switch.
  pinUnused3 = 44,               ///< Pin 44. Unused pin #3.
  pinSwitchLeft1 = 45,           ///< Pin 44. 1st left-of-center.
  pinSwitchCenter = 46,          ///< Pin 46. Center micro-switch.
  pinSwitchRight1 = 47,          ///< Pin 47. 1st right-of-center.
  pinUnused4 = 48,               ///< Pin 48. Unused pin #4.
  pinSwitchRight3 = 49,          ///< Pin 49. Right-most micro-switch.
  pinSwitchRightMax = 50,        ///< Pin 50. Right leaf-switch.
  // Motor.
  pinMotorLeft = 51,             ///< Pin 51. Move left.
  pinMotorRight = 52,            ///< Pin 52. Move right.
  // Misc.
  pinReserved2 = 53              ///< Pin 53. Reserved pin #2.
};
/**
   The first sound pin.
*/
const int FIRST_SOUND_PIN = 2;
/**
   The last sound pin.
*/
const int LAST_SOUND_PIN = 13;
/**
   The first light pin.
*/
const int FIRST_LIGHT_PIN = 22;
/**
   The last light pin.
*/
const int LAST_LIGHT_PIN = 33;
/**
   The first button pin.
*/
const int FIRST_BUTTON_PIN = 35;
/**
   The last button pin.
*/
const int LAST_BUTTON_PIN = 41;
/**
   The first pin in a set of switch pins.
 */
const int FIRST_SWITCH_PIN = 42;
/**
   The last pin in a set of switch pins.
 */
const int LAST_SWITCH_PIN = 50;

////////////////////////////////////////////////////////////////////////
// Sounds //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The index of the current song being played.
*/
int soundCurrent = -1;
/**
   A single sound.
*/
struct Sound {
  int pin;  ///< The sounds pin. Set HIGH to play sound.
};
/**
   A set of sounds.

   Only one sound (per sound card) can play at one time. The 1st sound
   card handles sounds 0-6, and the second handles sounds 7-13.
   
   Hold pin HIGH for 500 milliseconds (or more) to ensure that the
   sound plays. The pin needs to be held HIGH for at least 200
   milliseconds, but it may be inconsistent about playing.
*/
Sound sounds[] = {
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound(),
  Sound()
};
/**
   A set of sound blocks.
*/
long soundBlocks[] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
/**
   An enum paired with the sounds array and the soundBlocks array.

   Overview:
   - Sound Card #1 (Top Sound Card): 0-6.
   - Sound Card #2 (Bottom Sound Card): 7-13.
*/
enum soundEnum {
  ready,      ///< Ready sound.
  catFirst,   ///< Winner (Cat) sound.
  dogFirst,   ///< Winner (Dog) sound.
  catThird,   ///< Champion (Cat) sound.
  dogThird,   ///< Champion (Dog) sound.
  tie,        ///< Tie sound.
  stop,       ///< Stop sound.
  tug,        ///< Tug sound.
  one,        ///< One sound.
  two,        ///< Two sound.
  three,      ///< Three sound.
  suddenDeath ///< Sudden Death sound.
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Is the "One" light on?
 */
bool isOneOn = false;
/**
   Is the "Two" light on?
 */
bool isTwoOn = false;
/**
   Is the "Three" light on?
 */
bool isThreeOn = false;
/**
   Is the "Tug" light on?
 */
bool isTugOn = false;
/**
   Is the "Stop" light on?
 */
bool isStopOn = false;
/**
   Is the "Game Over" light on?
 */
bool isGameOver = false;
/**
   Is the "Toggle" light on?
 */
bool isToggleOn = false;
/**
   Is the "Ready" light blinking?
 */
bool isReadyBlinking = false;
/**
   Is the "Winner Left" light blinking?
 */
bool isWinnerLeftBlinking = false;
/**
   Is the "Winner Right" light blinking?
 */
bool isWinnerRightBlinking = false;
/**
   Is the "Champion Left" light blinking?
 */
bool isChampionLeftBlinking = false;
/**
   Is the "Champion Right" light blinking?
 */
bool isChampionRightBlinking = false;
/**
   Is the "Sudden Death Left" light blinking?
 */
bool isSuddenDeathLeftBlinking = false;
/**
   Is the "Sudden Death Right" light blinking?
 */
bool isSuddenDeathRightBlinking = false;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A single button.
*/
struct Button {
  int pin;  ///< The button pin. Press button to drive pin LOW.
};
/**
   A set of buttons.
*/
Button buttons[] = {
  Button(),
  Button(),
  Button(),
  Button(),
  Button()
};
/**
   This array of buttons is updated once per loop, then referenced
   throughout.
*/
bool hotButtons[] = {false, false, false, false, false};
/**
   Blocks a button debounce Press until non-debounce Release.
*/
bool buttonBlocks[] = {false, false, false, false, false};
/**
  The time (in milliseconds) since the most recent button down press.
*/
long buttonDebounces[] = {0L, 0L, 0L, 0L, 0L};
/**
   An enum paired with the buttons, hotButtons, buttonBlocks, and
   buttonDebounces arrays.
*/
enum buttonEnum {
  start,        ///< Start button.
  player1Left,  ///< Player 1 (Left) button.
  player1Right, ///< Player 1 (Right) button.
  player2Left,  ///< Player 2 (Left) button.
  player2Right  ///< player 2 (Right) button.
};
/**
   The length of the button arrays.
 */
const int BUTTON_SIZE = 5;

////////////////////////////////////////////////////////////////////////
// Switches ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A single switch.
*/
struct Switch {
  int pin;  ///< The switch pin. Either micro-switch or contact switch.
};
/**
   A set of switches.
*/
Switch switches[] = {
  Switch(),
  Switch(),
  Switch(),
  Switch(),
  Switch(),
  Switch(),
  Switch(),
  Switch()
};
/**
   This array of switches is updated once per loop, then referenced
   throughout.
*/
bool hotSwitches[] = {false, false, false, false, false, false, false};
/**
   The debounced array of switches.
 */
bool debouncedSwitches[] = {false, false, false, false, false, false, false};
/**
   Blocks a switch from debounced Press until non-debounced Release.
*/
bool switchBlocks[] = {false, false, false, false, false, false, false};
/**
  The time (in milliseconds) since the most recent switch down press.
*/
long switchDebounces[] = {0L, 0L, 0L, 0L, 0L, 0L, 0L};
/**
   A set of target switches to be set before any motor movement.
*/
bool targets[] = {false, false, false, false, false, false, false};
/**
   An enum paired with the switches, hotSwitches, switchBlocks,
   switchDebounces, and targets arrays.
*/
enum switchEnum {
  leftMax = 0, ///< Left leaf-switch.
  left3 = 1,   ///< Left Champion (Cat) micro-switch.
  left1 = 2,   ///< Left Winner (Cat) micro-switch.
  center = 3,  ///< Center micro-switch.
  right1 = 4,  ///< Right Winner (Dog) micro-switch.
  right3 = 5,  ///< Right Champion (Dog) micro-switch.
  rightMax = 6 ///< Right leaf-switch.
};
const int SWITCH_SIZE = 7;

////////////////////////////////////////////////////////////////////////
// Motor ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A single motor.

   - The left and right pins actually move the motor clockwise and
   counter-clockwise respectively.
   - The right pin spins to the motor clockwise, which spins screw
   clockwise, which moves the trigger platform right.
   - The left pin spins the motor counter-clockwise, which  spins the
   screw counter-clockwise, which moves the trigger platform left.
*/
struct Motor {
  int left;             ///< A motor pin. Set HIGH to move left.
  int right;            ///< A motor pin. Set HIGH to move right.
  bool isMovingStopped; ///< Is the motor stopped?
  bool isMovingLeft;    ///< Is the motor moving left?
  bool isMovingRight;   ///< Is the motor moving right?

  /**
     Stop moving the motor.
  */
  void moveStop() {
    isMovingStopped = true;
    isMovingLeft = false;
    isMovingRight = false;
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
  }

  /**
     Move motor right.
  */
  void moveLeft() {
    isMovingStopped = false;
    isMovingLeft = true;
    isMovingRight = false;
    digitalWrite(right, LOW);
    digitalWrite(left, HIGH);
  }

  /**
     Move motor left.
  */
  void moveRight() {
    isMovingStopped = false;
    isMovingLeft = false;
    isMovingRight = true;
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH);
  }
};
/**
   An instance of the motor struct.
*/
Motor motor = Motor();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Debounce by Time ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) from the beginning of a Player 1/2 Left/Right 
   button press until it is considered valid.
*/
long const DEBOUNCE_TIME = 20L;
/**
   Time (in milliseconds) from the beginning of a micro-switch press 
   until it is considered valid.
 */
long const DEBOUNCE_TIME_MICRO_SWITCHES = 20L;
/**
   Time (in milliseconds) from the beginning of a Start button press 
   until it is considered valid.
 */
long const DEBOUNCE_TIME_START = 50L;
/**
   The time at the beginning of the current loop.
*/
unsigned long current;
/**
   The time at the beginning of the previous loop.
*/
unsigned long previous;
/**
   The time between the previous loop and the current loop.
*/
unsigned long delta;
/**
   A single reusable timer.

   The buttons and switches also have individual debounce 
   STOP_SPECIAL_TIMEOUT.
*/
struct Timer {
  unsigned long total;    ///< Time since timer reset.
  unsigned long timeout;  ///< Timer length.
};
/**
   A set of reusable STOP_SPECIAL_TIMEOUT.
*/
Timer timers[] = {
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer(),
  Timer()
};
/**
   An enum paired with the STOP_SPECIAL_TIMEOUT array.
*/
enum timerEnum {
  sound,         ///< Sound timer.
  toggle,        ///< Toggle timer.
  oneSecond,     ///< One second timer.
  fiveSecond,    ///< Five second timer.
  tenSecond,     ///< Ten second timer.
  sequence,      ///< Sequence timer.
  tieSpecial,    ///< Tie timer.
  stopSpecial,   ///< Stop timer.
  readySpecial,  ///< Ready timer.
  winnerSpecial, ///< Winner timer.
  countSpecial   ///< Game count timer.
};

////////////////////////////////////////////////////////////////////////
// Debounce by Position ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The current switch.
 */
int currentSwitch = -1;
/**
   The previous switch.
 */
int previousSwitch = -1;
/**
   The block that prevents bouncing.
 */
bool isSwitchAlreadyBlocked = false;

////////////////////////////////////////////////////////////////////////
// Debounce by Frame ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The first frame block for a leaf-switch.
 */
bool emergencyLeft = false;
/**
   The second frame block for a leaf-switch.
 */
bool emergencyLeft2 = false;
/**
   The first frame block for a leaf-switch.
 */
bool emergencyRight = false;
/**
   The second frame block for a leaf-switch.
 */
bool emergencyRight2 = false;


////////////////////////////////////////////////////////////////////////
// States //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The application's startup state. Should resolve to isReset state. 
   During this state the application is looking for the Champion (Cat) 
   micro-switch, or the Champion (Dog) micro-switch, which causes the 
   motor to reverse direction and move toward center.
 */
bool isCentering = true;
/**
   The application's state when it is waiting for a person to press the 
   Start button. Should resolve to the isReadyTimerOn state. During this 
   state the application is looking the Center micro-switch to stop.
 */
bool isReset = false;
/**
   The application's state when in the isSequenceTimerOn state. Should 
   resolve to the isReadyTimerOn state (or the 
   isSuddenDeathLeftBlinking state, or the isSuddenDeathRightBlinking 
   state). During this state the Tie sound plays.
 */
bool isTie = 0;
/**
   The application's state when in the isReadyTimerOn state. Should 
   resolve to the isOneSecondTimerOn state. During this state the 
   Ready sound plays.
 */
bool isReadyTimerOn = false;
/**
   The application's state when in the isOneSecondTimerOn state. 
   Should proceed through the one, two, three sounds/lights, then 
   resolve to the isFiveSecondTimerOn state. During the 
   isOneSecondTimerOn state the game counts down from three to one.
 */
bool isOneSecondTimerOn = false;
/**
   The application's state when in the isSoundTimerOn state. Resolves 
   to nothing and just shuts off. During the isSoundTimerOn state the 
   game plays a sound.
 */
bool isSoundTimerOn = false;
/**
   The application's state when in the isFiveSecondTimerOn state. 
   Resolves to the stopTugSequence() function. During the 
   isFiveSecondTimerOn state the application waits to call the
   stopTugSequence() function.
 */
bool isFiveSecondTimerOn = false;
/**
   The application's state when in the isTenSecondTimerOn state. 
   Resolves to the stopTenSecondTimer() function. During the 
   isTenSecondTimerOn state the application waits to call the 
   stopTenSecondTimer() function.
 */
bool isTenSecondTimerOn = false;
/**
   The application's state when in the isStopTimerOn state. 
   Resolves first to the stopStopTimer() function. Second, it 
   resolves to the routeResults2() function, the routeResults() 
   function. During the isStopTimerOn state the Stop sound plays,
   but motor movement and the Winner light are not yet active.
 */
bool isStopTimerOn = false;
/**
   The application's state when in the isWinnerTimerOn state. 
   Resolves to the stopWinnerTimer() function.
 */
bool isWinnerTimerOn = false;

/**
   The application's state when in the isSequenceOn state. Iterates 
   through tug sequences, their segments, and finally loops back to 
   the first tug sequence.
 */
bool isSequenceOn = false;
/**
   The application's state when in the isCountOn state. Holds the 
   pinCount pin HIGH for a period of time greater than 500 
   milliseconds.
 */
bool isCountOn;

////////////////////////////////////////////////////////////////////////
// Scores //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Player 1's score. Calculated from the player1Taps array.
 */
int player1Score;
/**
   Player 2's score. Calculated from the player2Taps array.
 */
int player2Score;
/**
   The maximum number of taps.
 */
const int TAPS_MAX = 100;
/**
   Player 1's taps. Collected during the isFiveSecondTimerOn state.
 */
int player1Taps[TAPS_MAX];
/**
   Player 2's taps. Collected during the isFiveSecondTimerOn state.
 */
int player2Taps[TAPS_MAX];
/**
   Player 1's index.
 */
int player1Index = 0;
/**
   Player 2's index.
 */
int player2Index = 0;
/**
   The current round.
 */
int roundCurrent = 0;
/**
   The maximum round (the sudden death round).
 */
int ROUND_MAX = 5;

////////////////////////////////////////////////////////////////////////
// Tug Sequences ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The tug sequence's first dimension's length.
 */
const int SEQUENCE_I_MAX = 4;
/**
   The tug sequence's second dimension's length.
 */
const int SEQUENCE_J_MAX = 3;
/**
   The the motor moving left.
 */
bool isSequenceLeft = true;
/**
   The time of each segment.
 */
long sequenceTimeout[][SEQUENCE_I_MAX] = {
  {200L, 200L, 200L, 200L},
  {500L, 500L, 500L, 500L},
  {200L, 200L, 500L, 500L}
};
/**
   The direction of each segment.
 */
long sequenceIsLeft[][SEQUENCE_I_MAX] = {
  {true, false, true, false},
  {false, true, false, true},
  {true, false, true, false}
};
/**
   The tug sequence's first dimension's index.
 */
int sequenceI = 0;
/**
   The tug sequence's second dimension's index.
 */
int sequenceJ = 0;

////////////////////////////////////////////////////////////////////////
// Routing /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The result of the preRouteResults() function.
 */
bool preRouteResult;
/**
   The current switch as of the preRouteResults() function.
 */
int preRouteSwitch;
/**
   The current round as of the preRouteResults() function.
 */
int preRouteRoundCurrent;

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The timeout for the isOneSecondTimer state.
 */
unsigned long ONE_SECOND_TIMEOUT = 1000L;
/**
  The timeout for the isFiveSecondTimer state.
 */
unsigned long FIVE_SECOND_TIMEOUT = 5000L;
/**
   The timeout for the isReadyTimerOn state.
 */
unsigned long READY_TIMEOUT = 2500L;
/**
   The timeout for the isSequenceOn state.
 */
unsigned long SEQUENCE_TIMEOUT = 4999L;
/**
   The timeout for the isSoundTimer state.
 */
unsigned long SOUND_TIMEOUT = 1000L;
/**
   The timeout for to trigger the routing of results.
 */
unsigned long STOP_TIMEOUT = 1100L;
/**
   The special timeout for the isStopTimer state.
 */
unsigned long STOP_SPECIAL_TIMEOUT = 1515L;
/**
   The timeout for the isTenSecondTimer state.
 */
unsigned long TEN_SECOND_TIMER = 10000L;
/**
   The timeout for the toggle timer.
 */
unsigned long TOGGLE_TIMEOUT = 200L;
/**
   The timeout for the isWinnerOn state.
 */
unsigned long WINNER_TIMEOUT = 4000L;
/**
   The timeout for the isCountOn state.
 */
unsigned long COUNT_TIMEOUT = 1000L;

unsigned long TIE_TIMEOUT = 3500L;

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   An enum of possible message codes.
 */
enum messages {
  startMessage = 48, ///< Start message.
  resetMessage = 49  ///< Reset message.
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
// Multi-Color LED /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The red color's pin.
 */
const int RED = A0;
/**
   The blue color's pin.
 */
const int BLUE = A1;
/**
   The green color's pin.
 */
const int GREEN = A2;

////////////////////////////////////////////////////////////////////////
// Errors //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A first counter to count how many switches are pressed.
 */
int countSwitch = -1;
/**
   A second counter to count how many switches are pressed.
 */
int countSwitch2 = -1;
/**
   The single switch (if there aren't plural switches being pressed).
 */
int singleSwitch = -1;

////////////////////////////////////////////////////////////////////////
// Debug ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The debug timer's timeout.
 */
const unsigned long DEBUG_TIMEOUT = 60000L;
/**
   The debug timer's time.
 */
unsigned long debugTimer = 0L;

// NEW THINGS
bool isDebug = false;
bool isSuper;
