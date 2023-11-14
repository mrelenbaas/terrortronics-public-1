#include "Keyboard.h"

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

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
int incomingMessage;
