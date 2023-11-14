////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;
 
// Pins.
const int PIN_ONE = 2;
const int PIN_TWO = 4;
const int PIN_THREE = 7;
const int PIN_FOUR = 8;
const int PINS_SIZE = 4;
const int PINS[] = {
  PIN_ONE,
  PIN_TWO,
  PIN_THREE,
  PIN_FOUR
};
int pinIndex;

// Joysticks.
const long DELAY_BETWEEN_JOYSTICKS = 10000;
bool isTurningJoysticksOn;
bool isTurningJoysticksOff;

// Timer.
unsigned long previousTime;
unsigned long currentTime;
unsigned long deltaTime;
unsigned long delayTime;

// Serial.
const int SERIAL_DELAY = 200;

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
  'j',
  'o',
  'y',
  's',
  't',
  'i',
  'c',
  'k',
  '_',
  'm',
  'a',
  'n',
  'a',
  'g',
  'e',
  'r',
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
  '\\',
  'n',
  '\0'
};
int incomingMessage;
