/*
 * Title: joystick_manager file.
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
const String OUTGOING_START = "type:config,filename:joystick_manager,function:reset\n";
int incomingMessage;

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  //Serial.flush();
  for (int i = 0; i < PINS_SIZE; i++) {
    pinMode(PINS[i], OUTPUT);
  }
  currentTime = millis();
}

/**
 * The main function.
 */
void loop() {
  //delay(SERIAL_DELAY);
  Serial.println(millis());
  previousTime = currentTime;
  currentTime = millis();
  deltaTime = currentTime - previousTime;
  delayTime += deltaTime;
  if ((isTurningJoysticksOn && delayTime >= DELAY_BETWEEN_JOYSTICKS)
      || (isTurningJoysticksOn && pinIndex == 0)) {
    digitalWrite(PINS[pinIndex], HIGH);
    delayTime = 0;
    pinIndex++;
    if (pinIndex >= PINS_SIZE) {
      isTurningJoysticksOn = false;
    }
  } else if (isTurningJoysticksOff /*&& delayTime >= DELAY_BETWEEN_JOYSTICKS*/) { 
    //digitalWrite(PINS[pinIndex], LOW);
    delayTime = 0;
    //pinIndex++;
    //if (pinIndex >= PINS_SIZE) {
    //  isTurningJoysticksOff = false;
    //}
    for (int i = 0; i < PINS_SIZE; i++) {
      digitalWrite(PINS[i], LOW);
    }
    isTurningJoysticksOff = false;
  }
  if (Serial.available() > 0) {
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
  isTurningJoysticksOn = false;
  isTurningJoysticksOff = true;
  delayTime = 0;
  pinIndex = 0;
}

void start() {
  Serial.println("start()");
  Serial.println(OUTGOING_START);
  isTurningJoysticksOff = false;
  isTurningJoysticksOn = true;
  delayTime = 0;
  pinIndex = 0;
}
