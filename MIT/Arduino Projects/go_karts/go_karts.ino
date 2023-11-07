/*
   Title: go_karts file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

#include "Keyboard.h"

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
const String OUTGOING_START = "type:config,filename:go_karts,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void openNewTerminal() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('t');
  Keyboard.releaseAll();
  delay(DELAY_AFTER_SPACE);
}

void pressKeys(String keys) {
  buttonBlock = true;
  for (int i = 0; i < keys.length(); i++) {
    Keyboard.press(keys[i]);
    delay(DELAY_BETWEEN_KEY_PRESS);
    Keyboard.releaseAll();
  }
  Keyboard.write(KEY_RETURN);
}

void setup() {
  // open the serial port:
  Serial.begin(BAUD_RATE);
  // initialize control over the keyboard:
  Keyboard.begin();

  for (int i = 0; i < PINS_SIZE; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
  }
}

/**
   The main function.
*/
void loop() {
  buttonBlockResult = true;
  if (buttonBlock) {
    for (int i = 0; i < PINS_SIZE; i++) {
      if (digitalRead(PINS[i]) == LOW) {
        buttonBlockResult = false;
        delay(DELAY_AFTER_BUTTON_RELEASE);
      }
    }
    if (buttonBlockResult) {
      buttonBlock = false;
    }
  }
  if (buttonBlock == false) {
    if (digitalRead(ORANGE) == LOW) {
      //openNewTerminal();
      pressKeys("cd ~/iotivity-lite/port/linux/");
      pressKeys("python3 gokarts.py");
    }
    else if (digitalRead(GREEN) == LOW) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      delay(DELAY_AFTER_SPACE);
      Keyboard.releaseAll();
      delay(DELAY_AFTER_SPACE);
    }
    else if (digitalRead(PURPLE) == LOW) {
      //openNewTerminal();
      pressKeys("cd ~/iotivity-lite/port/linux/");
      pressKeys("./simpleserver");
    }
    else if (digitalRead(WHITE) == LOW) {
      openNewTerminal();
    }
  }

  if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame application.
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case startMessage:
        start();
        break;
      case resetMessage:
        reset();
        break;
      default:
        break;
    }
  }
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
