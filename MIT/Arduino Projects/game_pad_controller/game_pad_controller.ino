/*
 * Title: game_pad_controller file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the Arduino License.
 */
 
////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

const int SERIAL_DELAY = 10;

// Pin constants.
const int HORIZONTAL = A0;
const int VERTICAL = A1;
const int BUTTON = 2;

// Hot keyboard.
int horizontal;
int vertical;
int button;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:game_pad_controller,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  
  pinMode(HORIZONTAL, INPUT);
  pinMode(VERTICAL, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

/**
 * The main function.
 */
void loop() {
  horizontal = analogRead(HORIZONTAL);
  vertical = analogRead(VERTICAL);
  button = digitalRead(BUTTON);

  Serial.flush();
  Serial.print(horizontal);
  Serial.print(", ");
  Serial.print(vertical);
  Serial.print(", ");
  Serial.println (button);

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

  delay(SERIAL_DELAY);
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
