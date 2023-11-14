#include "WiFi.h"
#include "AsyncUDP.h"

#include "pitches.h"

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

// TODO: Remember that this is the only .ino file that uses the #define convention. Other .ino files use const ints.
// Rotary Encoder Inputs
#define CLK 22
#define DT 12
// TODO: Preserve this button setup in another prohject, but migrate this project to use interrupt pins.
#define RED_BUTTON 13
#define YELLOW_BUTTON 19
#define BLUE_BUTTON 18
#define GREEN_BUTTON 5
#define RED_LED 23
#define YELLOW_LED 32
#define BLUE_LED 15
#define GREEN_LED 33
#define BUZZER 14

int counter2 = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
bool currentStateCLK3Flag;

int counter3 = 0;
int lastStateCLK3;
String currentDir3 = "-";

// Serial.
const int SERIAL_DELAY = 10;

int INDEX_MAX = 9;
int counter = 0;

const float STEPS = 600.0f;
const float STEP = 0.6f; // 360 diveded by 600
float angle;

const long TIME_PERIOD = 1000;
long timeAtStart;
long timeSinceStart;
float timePercentage;
bool isRecording;
bool isRecordingFlag;

int specialCounter;
float totalSteps;

bool clkSet[1000];
bool dwSet[1000];

int fps;
int btnState;
int btnState0;
int btnState1;
int btnState2;
int btnState3;

float rps;
char angleBuffer[6];
char rpsBuffer[6];
char totalStepsBuffer[6];
//char stepsBuffer[6];

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
bool isBlinkOn;

const char * ssid = "NETGEAR08";
const char * password = "largeskates190";
AsyncUDP udp;
bool isWifiConnected;
char udpBuffer[40];

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
  'r',
  'o',
  't',
  'a',
  'r',
  'y',
  '_',
  'e',
  'n',
  'c',
  'o',
  'd',
  'e',
  'r',
  '_',
  'r',
  'p',
  'm',
  '_',
  'c',
  'o',
  'n',
  't',
  'r',
  'o',
  'l',
  'l',
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
