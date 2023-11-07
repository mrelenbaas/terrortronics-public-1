/*
   Title: startup_manager file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

// https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide?gclid=CjwKCAjwh4ObBhAzEiwAHzZYU9fWXPNZrw8oHU1V8xxeILSFGz1O_08SyU8i6gU0pNtaYeBZTgg0exoCMEQQAvD_BwE
// https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
// https://arduinogetstarted.com/faq/how-to-reset-arduino-by-programming

// WARNING: DO NO USE THIS EXAMPLE (1): The readString function may cause memory problems.
// WARNING: DO NO USE THIS EXAMPLE (2): The Serial blocking code breaks on Unity Standalone Windows builds.
// https://reference.arduino.cc/reference/en/language/functions/communication/serial/readstring/

// Unit Tests
// 1a. Expected shutdown (with power supply spin down).
// 2a. Expected shutdown (Standalone, no power loss).
// 2b. Expected shutdown (Unity Editor, no power loss).
// 3a. Unexpected shutdown (with power supply spin down).
// 4a. Unexpected shutdown (without power supply spin down).

#include "Keyboard.h"

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

enum messages {
  startMessage = 48,
  resetMessage = 49,
};

// Keys.
const char KEY_SPACE = ' ';
const int KEYS_SIZE = 4;
char KEYS[] = {
  0,
  0,
  0,
  0
};

const int PIN_BIKE_LOCK_DIGIT_ZERO = A1;
const int PIN_BIKE_LOCK_DIGIT_ONE = A2;
const int PIN_BIKE_LOCK_DIGIT_TWO = A3;
const int PIN_BIKE_LOCK_DIGIT_THREE = A4;
int bikeLockDigits[] = {
  0,
  0,
  0,
  0
};

// Pins.
const long DELAY_AFTER_HARD_SHUTDOWN_DETECTION = 60000;
const int PIN_FRONT_LIGHT = 2;
const int FRONT_LIGHT_POLLS_BEFORE_HARD_SHUTDOWN_DETECTION = 10;
int frontLightPollsCount;
int frontLightPoll;
bool isBlockedAfterHardShutdownDetection;

// Login.
const long DELAY_BETWEEN_LOGIN_ATTEMPTS = 60000;
const long DELAY_DEBOUNCE = 2000;
const long DELAY_AFTER_SPACE = 2000;
bool isStartMessageReceived;



// Timer.
unsigned long previousTime;
unsigned long currentTime;
unsigned long deltaTime;
unsigned long delayTime;

// Serial.
const int SERIAL_DELAY = 200;

// Messages.
const String OUTGOING_START = "type:config,filename:startup_manager,function:reset\n";
int incomingMessage;

bool isArcadeCabinetExited;
bool isArcadeCabinetStarted;
bool isSecondAttempt;


// Pseudo-constructor.
void setup() {
  Keyboard.begin();
  Serial.begin(BAUD_RATE);
  pinMode(PIN_FRONT_LIGHT, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  currentTime = millis();
}

// Display output from either attract or from direct input.
/**
   The main function.
*/
void loop() {
  delay(SERIAL_DELAY);
  previousTime = currentTime;
  currentTime = millis();
  deltaTime = currentTime - previousTime;
  delayTime += deltaTime;
  bikeLockDigits[0] = analogRead(PIN_BIKE_LOCK_DIGIT_ZERO);
  bikeLockDigits[1] = analogRead(PIN_BIKE_LOCK_DIGIT_ONE);
  bikeLockDigits[2] = analogRead(PIN_BIKE_LOCK_DIGIT_TWO);
  bikeLockDigits[3] = analogRead(PIN_BIKE_LOCK_DIGIT_THREE);
  /*
  Serial.print(delayTime);
  Serial.print(", ");
  Serial.print(digitalRead(PIN_FRONT_LIGHT));
  Serial.print(", ");
  Serial.print((char)((int)(bikeLockDigits[0] * 4.0f / 1000.0f) + 48));
  Serial.print(", ");
  Serial.print((char)((int)(bikeLockDigits[1] * 4.0f / 1000.0f) + 48));
  Serial.print(", ");
  Serial.print((char)((int)(bikeLockDigits[2] * 4.0f / 1000.0f) + 48));
  Serial.print(", ");
  Serial.println((char)((int)(bikeLockDigits[3] * 4.0f / 1000.0f) + 48));
  */
  if (isBlockedAfterHardShutdownDetection && delayTime < DELAY_AFTER_HARD_SHUTDOWN_DETECTION) {
    return;
  } else if (isBlockedAfterHardShutdownDetection && delayTime >= DELAY_AFTER_HARD_SHUTDOWN_DETECTION) {
    Serial.println("hard shutdown recovery, following hard shutdown delay");
    enterPin();
    delayTime = 0;
  }
  if (frontLightPollsCount >= FRONT_LIGHT_POLLS_BEFORE_HARD_SHUTDOWN_DETECTION) {
    delayTime = 0;
    isStartMessageReceived = false;
    isBlockedAfterHardShutdownDetection = true;
    isArcadeCabinetExited = false;
  }
  if (!isStartMessageReceived && delayTime >= DELAY_BETWEEN_LOGIN_ATTEMPTS) {
    Serial.println("start message not received, following delay");
    enterPin();
    delayTime = 0;
    isSecondAttempt = true;
  }
  if (Serial.available() > 0) {
    incomingMessage = Serial.read();
    Serial.flush();
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

// Enter the pin for logging into Windows.
void enterPin() {
  /*
  if (isArcadeCabinetExited
      || isArcadeCabinetStarted) {
    return;
  }
  digitalWrite(6, HIGH);
  delay(DELAY_AFTER_SPACE);
  KEYS[0] = (char)((int)(analogRead(A1) * 4.0f / 1000.0f) + 48);
  KEYS[1] = (char)((int)(analogRead(A2) * 4.0f / 1000.0f) + 48);
  KEYS[2] = (char)((int)(analogRead(A3) * 4.0f / 1000.0f) + 48);
  KEYS[3] = (char)((int)(analogRead(A4) * 4.0f / 1000.0f) + 48);
  if (KEYS[0] == 0) {
    return;
  }
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(DELAY_AFTER_SPACE);
  Keyboard.write(KEY_SPACE);
  delay(DELAY_AFTER_SPACE);
  for (int i = 0; i < KEYS_SIZE; i++) {
    Keyboard.write(KEYS[i]);
  }
  delay(DELAY_DEBOUNCE);
  digitalWrite(6, LOW);
  delay(DELAY_AFTER_SPACE);
  */
}

void reset() {
  //isStartMessageReceived = false;
  isBlockedAfterHardShutdownDetection = false;
  //isArcadeCabinetStarted = false;
  isArcadeCabinetExited = true;
  isSecondAttempt = false;
}

void start() {
  Serial.println("start message received from Unity");
  isBlockedAfterHardShutdownDetection = false;
  isArcadeCabinetStarted = false;
  isArcadeCabinetExited = false;
  Serial.println(OUTGOING_START);
  if (!isSecondAttempt) {
    enterPin();
    isSecondAttempt = true;
  }
  isArcadeCabinetStarted = true;
  isStartMessageReceived = true;
}
