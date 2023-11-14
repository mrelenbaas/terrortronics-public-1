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
   - Empty.

   @section todo TODO
   - Empty.

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
        https://docs.arduino.cc/hardware/due
    + Software:
        https://www.arduino.cc/reference/en/
   - Debouncing
    + Time Based:
        https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
    + Current/Previous Based:
        https://docs.arduino.cc/built-in-examples/digital/Debounce

   @section warnings WARNINGS
   - empty
*/

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void calculateResults();
void debounceSwitchByTime(int i);
void debounceSwitchesByTime();
void debounceSwitchesByPosition();
bool errorCheckContactSwitches();
bool errorCheckPluralInput();
void playSound();
void routeButtons();
void routeResults();
void setTarget(int index);
void stopOneSecondTimer();
void stopFourSecondTimer();
void stopFiveSecondTimer();
void stopTenSecondTimer();
void stopTugSegment();
void stopSoundTimer();
void stopToggleTimer();
void stopTugSequence();
void updateButtons();
void updateTimers();
void updateSwitches();
void stopStopTimer();
void routeResults2();
void routeResults3();
bool preRouteResults();
void stopReadyTimer();
void stopWinnerTimer();
void stopFiveSecondTimer2();
void randomWinner();
void startFunction();
void resetFunction();
void hardReset();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
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
   Redundant. This button wasn't working on the previous board.
*/
const int SKIPPED_BUTTON_1 = 36;
/**
   Redundant. This button wasn't working on the previous board.
*/
const int SKIPPED_BUTTON_2 = 40;
/**
 * The first pin in a set of switch pins.
 */
const int FIRST_SWITCH_PIN = 42;
/**
 * The last pin in a set of switch pins.
 */
const int LAST_SWITCH_PIN = 50;
/**
   Redundant. This button wasn't working on the previous board.
*/
const int SKIPPED_SWITCH_1 = 44;
/**
   Redundant. This button wasn't working on the previous board.
*/
const int SKIPPED_SWITCH_2 = 48;
/**
   The board's pins.

   @section details Details
   This enumeration uses "pin" as a prefix. The other enumerations do
   not use any prefix.
   - Sounds: 2-13.
   - Super Tug-of-War: 14-21.
   - Lights: 22-33.
   - Buttons: 35-41.
   - Switches: 42-50.
   - Motor. 51-52.
*/
enum pinEnum {
  // Sounds.
  pinSoundReady = 2,              ///< Pin 2. Ready sound.
  pinSoundCatWinner = 3,           ///< Pin 3. Winner (Cat) sound.
  pinSoundDogWinner = 4,           ///< Pin 4. Winner (Dog) sound.
  pinSoundCatChampion = 5,           ///< Pin 5. Champion (Cat) sound.
  pinSoundDogChampion = 6,           ///< Pin 6. Champion (Dog) sound.
  pinSoundTie = 7,                ///< Pin 7. Tie sound.
  pinSoundStop = 8,               ///< Pin 8. Stop sound.
  pinSoundOne = 9,                ///< Pin 9. One sound.
  pinSoundTwo = 10,               ///< Pin 10. Two sound.
  pinSoundThree = 11,             ///< Pin 11. Three sound.
  pinSoundTug = 12,               ///< Pin 12. Tug sound.
  pinSoundSuddenDeath = 13,       ///< Pin 13. Sudden Death sound.
  // Super Pins.
  //pinButtonTouch = 14,          ///< Pin 14. ERROR. Unresponsive.
  //pinLightError = 15,           ///< Pin 15. ERROR. Always high.
  pinBuzzer = 16,                 ///< Pin 16. Buzzer pin.
  pinButtonTouch = 17,            ///< Pin 17. Reset button.
  pinLightError = 18,             ///< Pin 18. Red debug LED.
  pinReset = 19,                  ///< Pin 19. Reset by connecting run pin to ground.
  pinLightDebug = 20,             ///< Pin 20. Blue debug LED.
  // Lights.
  pinLightWinnerLeft = 22,        ///< Pin 22. Left Winner light.
  pinLightWinnerRight = 23,       ///< Pin 23. Right Winner light.
  pinLightSuddenDeathLeft = 24,   ///< Pin 24. Left Sudden Death light.
  pinLightSuddenDeathRight = 25,  ///< Pin 25. Right Sudden Death light.
  pinLightChampionLeft = 26,      ///< Pin 26. Left Champion light.
  pinLightChampionRight = 27,     ///< Pin 27. Right Champion light.
  pinLightReady = 28,             ///< Pin 28. Ready light.
  pinLightOne = 29,               ///< Pin 29. One light.
  pinLightTwo = 30,               ///< Pin 30. Two light.
  pinLightThree = 31,             ///< Pin 31. Three light.
  pinLightTug = 32,               ///< Pin 32. Tug light.
  pinLightStop = 33,              ///< Pin 33. Stop light.
  // Buttons.
  pinButtonStart = 35,            ///< Pin 35. Start button.
  pinButtonPlayer1Left = 37,      ///< Pin 37. Left Player 1 button.
  pinButtonPlayer1Right = 38,     ///< Pin 38. Right Player 1 button.
  pinButtonPlayer2Left = 39,      ///< Pin 39. Left Player 2 button.
  pinButtonPlayer2Right = 41,     ///< Pin 41. Right Player 2 button.
  // Switches.
  pinSwitchLeftMax = 42,          ///< Pin 42. Left leaf-switch.
  pinSwitchLeft3 = 43,            ///< Pin 43. Leftmost micro-switch.
  pinSwitchLeft1 = 45,            ///< Pin 44. First micro-switch left-of-center.
  pinSwitchCenter = 46,           ///< Pin 46. Center micro-switch.
  pinSwitchRight1 = 47,           ///< Pin 47. First micro-switch right-of-center.
  pinBlankExtra5 = 48,            ///< Pin 48. Error. Unresponsive.
  pinSwitchRight3 = 49,           ///< Pin 49. Rightmist micro-switch.
  pinSwitchRightMax = 50,         ///< Pin 50. Right leaf-switch.
  // Motor.
  pinMotorLeft = 51,              ///< Pin 51. Set HIGH (and set Pin 52 LOW) to move motor clockwise and to move trigger right.
  pinMotorRight = 52              ///< Pin 52. Set HIGH (and set Pin 51 LOW) to move motor anti-clockwise and to move trigger left.
};

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Debounce ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) from the beginning of a button (or switch)
   press until it is considered valid.
*/
long const DEBOUNCE_TIME = 20L;
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

   @section Details
   The buttons and switches also have individual debounce timers.
*/
struct Timer {
  unsigned long total;    ///< Time since timer reset.
  unsigned long timeout;  ///< Timer length.
};
/**
   A set of reusable timers.
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
  Timer()
};
/**
   An enum paired with the timers array.
*/
enum timerEnum {
  sound,
  toggle,
  oneSecond,
  fiveSecond,
  tenSecond,
  sequence,
  tieSpecial,
  stopSpecial,
  readySpecial,
  winnerSpecial
};

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

   @section Details
   - Setting the Arduino pin HIGH will set the associated Sound Card pin
   LOW. Keep the Arduino pin LOW by default. Set the Arduino pin HIGH to
   tigger the relay. When triggered, the relay closes its gate and
   connects the normally open (NO) pin to the common (COM) pin.
   - Only one sound (per sound card) can play at one time. The 1st sound
   card handles sounds 0-6. The 2nd sound card handles sounds 7-13.
   Sounds 0 and 7 can play at the same time. Sounds 0 and 1 (or 7 and 8)
   cannot play at the same time.
   - Hold pin HIGH for 500 milliseconds (or more) to ensure that the
   sound plays. The pin needs to be held HIGH for at least 200
   milliseconds, but it may be inconsistent about playing. Holding the
   pin HIGH for 500 milliseconds has been a stable amount of time.
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
*/
enum soundEnum {
  ready,
  catFirst,
  dogFirst,
  catThird,
  dogThird,
  tie,
  stop,
  one,
  two,
  three,
  tug,
  suddenDeath
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Is the "One" light on?
 */
bool isOneOn = false;
/**
 * Is the "Two" light on?
 */
bool isTwoOn = false;
/**
 * Is the "Three" light on?
 */
bool isThreeOn = false;
/**
 * Is the "Tug" light on?
 */
bool isTugOn = false;
/**
 * Is the "Stop" light on?
 */
bool isStopOn = false;
/**
 * Is the "Game Over" light on?
 */
bool isGameOver = false;
/**
 * Is the "Toggle" light on?
 */
bool isToggleOn = false;
/**
 * Is the "Ready" light blinking?
 */
bool isReadyBlinking = false;
/**
 * Is the "Winner Left" light blinking?
 */
bool isWinnerLeftBlinking = false;
/**
 * Is the "Winner Right" light blinking?
 */
bool isWinnerRightBlinking = false;
/**
 * Is the "Champion Left" light blinking?
 */
bool isChampionLeftBlinking = false;
/**
 * Is the "Champion Right" light blinking?
 */
bool isChampionRightBlinking = false;
/**
 * Is the "Sudden Death Left" light blinking?
 */
bool isSuddenDeathLeftBlinking = false;
/**
 * Is the "Sudden Death Right" light blinking?
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
   Blocks a button from debounced Press until non-debounced Release.
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
  start,
  player1Left,
  player1Right,
  player2Left,
  player2Right
};
/**
 * The length of the button arrays.
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
  leftMax = 42,
  left3 = 43,
  left1 = 45,
  center = 46,
  right1 = 47,
  right3 = 49,
  rightMax = 50
};
const int SWITCH_SIZE = 7;

////////////////////////////////////////////////////////////////////////
// Switches ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   A single motor.

   @section Details
   - The left and right pins actually move the motor clockwise and
   counter-clockwise respectively.
   - The right pin spins to the motor clockwise, which spins screw
   clockwise, which moves the trigger platform right.
   - The left pin spins the motor counter-clockwise, which  spins the
   screw counter-clockwise, which moves the trigger platform left.
*/
struct Motor {
  int left;              ///< A motor pin. Set HIGH to move left.
  int right;             ///< A motor pin. Set HIGH to move right.
  bool isMovingStopped;  ///< Is the motor stopped?
  bool isMovingLeft;     ///< Is the motor moving left?
  bool isMovingRight;    ///< Is the motor moving right?
  bool isMoveLeftPrevious;

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
    isMoveLeftPrevious = true;
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
    isMoveLeftPrevious = false;
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
// States //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * The application's startup state. Should resolve to isReset state. 
 * During this state the application is looking for the Champion (Cat) 
 * micro-switch, or the Champion (Dog) micro-switch, which causes the 
 * motor to reverse direction and move toward center.
 */
bool isCentering = true;
/**
 * The application's state when it is waiting for a person to press the 
 * Start button. Should resolve to the isReadyTimerOn state. During this 
 * state the application is looking the Center micro-switch to stop.
 */
bool isReset = false;
/**
 * The application's state when in the isSequenceTimerOn state. Should 
 * resolve to the isReadyTimerOn state (or the 
 * isSuddenDeathLeftBlinking state, or the isSuddenDeathRightBlinking 
 * state). During this state the Tie sound plays.
 */
bool isTie = 0;
/**
 * The application's state when in the isReadyTimerOn state. Should 
 * resolve to the isOneSecondTimerOn state. During this state the 
 * Ready sound plays.
 */
bool isReadyTimerOn = false;
/**
 * The application's state when in the isOneSecondTimerOn state. 
 * Should proceed through the one, two, three sounds/lights, then 
 * resolve to the isFiveSecondTimerOn state. During the 
 * isOneSecondTimerOn state the game counts down from three to one.
 */
bool isOneSecondTimerOn = false;
/**
 * The application's state when in the isSoundTimerOn state. Resolves 
 * to nothing and just shuts off. During the isSoundTimerOn state the 
 * game plays a sound.
 */
bool isSoundTimerOn = false;
/**
 * The application's state when in the isFiveSecondTimerOn state. 
 * Resolves to the stopTugSequence() function. During the 
 * isFiveSecondTimerOn state the application waits to call the
 * stopTugSequence() function.
 */
bool isFiveSecondTimerOn = false;
/**
 * The application's state when in the isTenSecondTimerOn state. 
 * Resolves to the stopTenSecondTimer() function. During the 
 * isTenSecondTimerOn state the application waits to call the 
 * stopTenSecondTimer() function.
 */
bool isTenSecondTimerOn = false;
/**
 * The application's state when in the isStopTimerOn state. 
 * Resolves first to the stopStopTimer() function. Second, it 
 * resolves to the routeResults2() function, the routeResults() 
 * function. During the isStopTimerOn state the Stop sound plays,
 * but motor movement and the Winner light are not yet active.
 */
bool isStopTimerOn = false;
/**
 * The application's state when in the isWinnerTimerOn state. 
 * Resolves to the stopWinnerTimer() function.
 */
bool isWinnerTimerOn = false;

////////////////////////////////////////////////////////////////////////
// Scores //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Player 1's score. Calculated from the player1Taps array.
 */
int player1Score;
/**
 * Player 2's score. Calculated from the player2Taps array.
 */
int player2Score;
/**
 * The maximum number of taps.
 */
const int TAPS_MAX = 100;
/**
 * Player 1's taps. Collected during the isFiveSecondTimerOn state.
 */
int player1Taps[TAPS_MAX];
/**
 * Player 2's taps. Collected during the isFiveSecondTimerOn state.
 */
int player2Taps[TAPS_MAX];
/**
 * Player 1's index.
 */
int player1Index = 0;
/**
 * Player 2's index.
 */
int player2Index = 0;
/**
 * The current round.
 */
int roundCurrent = 0;
/**
 * The maximum round (the sudden death round).
 */
int roundMax = 6;

int currentSwitch = -1;
int previousSwitch = -1;
int countSwitch = -1;
int singleSwitch = -1;
bool isSwitchAlreadyBlocked = false;

bool isFirstLoop = true;

bool result;

// Unit Tests.
//bool isUnitTestingOn = true;
int testCurrent = 0;
int testMax = 2;
// #1: // Left, Right, Left, Right, Left, Right.
//bool player1Test[] = {false, true, false, true, false, true};
//bool player2Test[] = {true, false, true, false, true, false};
// #2: // Right, Left, Right, Left, Right, Left.
//bool player1Test[] = {true, false, true, false, true, false};
//bool player2Test[] = {false, true, false, true, false, true};
// 3. // Tie, Tie, Tie, Tie, Tie, Tie.
//bool player1Test[] = {0, 0, 0, 0, 0, 0};
//bool player2Test[] = {0, 0, 0, 0, 0, 0};
// 4.
//bool player1Test[] = {true, true, true, true, true, true};
//bool player2Test[] = {false, false, false, false, false, false};
// 5.
//bool player1Test[] = {10, 10, 10, 10, 10, 10};
//bool player2Test[] = {5, 5, 5, 5, 5, 5};
// 6.
//bool player1Test[6];
//bool player2Test[6];
// Total
//bool unitTests[][2][6] = {
//  {{true, false, true, false, true, false}, {false, true, false, true, false, true}}, // Left, Right, Left, Right, Left, Right.
//  {{false, true, false, true, false, true}, {true, false, true, false, true, false}}, // Right, Left, Right, Left, Right, Left.
//  {{false, true, false, true, false, true}, {false, true, false, true, false, true}} // Tie, Tie, Tie, Tie, Tie, Tie.
//};

int roundCurrent3 = 0;

const int SEQUENCE_I_MAX = 4;
const int SEQUENCE_J_MAX = 3;
bool isSequenceLeft = true;
bool isSequenceOn = false;
long sequenceTimeout[][SEQUENCE_I_MAX] = {
  {200L, 200L, 200L, 200L},
  {500L, 500L, 500L, 500L},
  {200L, 200L, 500L, 500L}
};
long sequenceIsLeft[][SEQUENCE_I_MAX] = {
  {true, false, true, false},
  {false, true, false, true},
  {true, false, true, false}
};
int sequenceI = 0;
int sequenceJ = 0;
//bool isOnlyStop = false;
//long randomTime = 500L;
const long SEQUENCE_MIN = 200L;
const long SEQUENCE_MAX = 400L;
//long sequenceTimeout[] = {100L, 200L};
int sequenceCounter = 2;
bool isFiveSecondTimerBlocked = false;

char message[] = {'a', 'b', 'c'};

bool errorPluralInput = false;

bool preRouteResult = false;
int preRouteSwitch;
int preRouteRoundCurrent;

bool emergencyStop;

long stopSpecialTimeout = 1515L;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
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
int incomingMessage;

bool emergencyLeft = false;
bool emergencyRight = false;
bool emergencyLeft2 = false;
bool emergencyRight2 = false;

const int RED = A0;
const int BLUE = A1;
const int GREEN = A2;
int val;

const unsigned long DEBUG_TIMEOUT = 1000L;
unsigned long debugTimer = 0L;
