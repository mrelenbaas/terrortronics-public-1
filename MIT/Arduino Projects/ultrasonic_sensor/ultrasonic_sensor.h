#include <NewPing.h>

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define TRIGGER_PIN_1 9
#define ECHO_PIN_1 10
#define TRIGGER_PIN_2 7
#define ECHO_PIN_2 8
#define TRIGGER_PIN_3 5
#define ECHO_PIN_3 6
#define TRIGGER_PIN_4 3
#define ECHO_PIN_4 4
#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN_4, ECHO_PIN_4, MAX_DISTANCE);

int sonarIndex = 0;
const int SONAR_MAX = 5;

const long PERIOD = 1000;
long timePrevious;
long timeCurrent;
long timeDelta;
long timeThisSecond;
unsigned long fpsPrevious;
unsigned long fpsCurrent;

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
  'u',
  'l',
  't',
  'r',
  'a',
  's',
  'o',
  'n',
  'i',
  'c',
  '_',
  's',
  'e',
  'n',
  's',
  'o',
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
