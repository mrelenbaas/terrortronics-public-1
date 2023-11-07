/*
   Title: power_manager file.
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

//const long DELAY_BEFORE_FIRST_JOYSTICK = 60000;
const int DELAY = 1000;
const int PIN_ONE_OUT = 2;
const int PIN_TWO_OUT = 3;
const int PIN_THREE_OUT = 4;
const int PIN_ONE_IN = 5;
const int PIN_TWO_IN = 6;
const int PIN_THREE_IN = 7;

const int PIN_WINDOWS_PHOTODIODE = A0;
int const PIN_WINDOWS_PHOTODIODE_SIZE = 20;
const float PIN_WINDOWS_PHOTODIODE_THRESHOLD = 20.0f;
int pinWindowsPhotodiodeHistory[PIN_WINDOWS_PHOTODIODE_SIZE];
int pinWindowsPhotodiodeIndex;
float pinWindowsPhotodiodeAverage;
float pinWindowsPhotodiodeReference;
long timeAtReference;
long const CONFIRMATION_PERIOD = 10000;

int hotKeyboard[] = { -1, -1, -1 };
int currentOut = -1;

bool isPowerOn;
bool isPowerOnConfirmed;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:power_manager,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(PIN_ONE_OUT, OUTPUT);
  pinMode(PIN_TWO_OUT, OUTPUT);
  pinMode(PIN_THREE_OUT, OUTPUT);
  pinMode(PIN_ONE_IN, INPUT_PULLUP);
  pinMode(PIN_TWO_IN, INPUT_PULLUP);
  pinMode(PIN_THREE_IN, INPUT_PULLUP);
  pinMode(PIN_WINDOWS_PHOTODIODE, INPUT);
  delay(1000);
  //powerOn();
}

/**
   The main function.
*/
void loop() {
  hotKeyboard[0] = digitalRead(PIN_ONE_IN);
  hotKeyboard[1] = digitalRead(PIN_TWO_IN);
  hotKeyboard[2] = digitalRead(PIN_THREE_IN);
  //Serial.print(hotKeyboard[0]);
  //Serial.print(",");
  //Serial.print(hotKeyboard[1]);
  //Serial.print(",");
  //Serial.println(hotKeyboard[2]);
  //Serial.flush();
  pinWindowsPhotodiodeHistory[pinWindowsPhotodiodeIndex] = analogRead(PIN_WINDOWS_PHOTODIODE);
  pinWindowsPhotodiodeIndex++;
  if (pinWindowsPhotodiodeIndex >= PIN_WINDOWS_PHOTODIODE_SIZE) {
    pinWindowsPhotodiodeIndex = 0;
    if (!isPowerOn) {
      pinWindowsPhotodiodeReference = pinWindowsPhotodiodeAverage;
      timeAtReference = millis();
      isPowerOn = true;
      powerOn();
    }
  }
  pinWindowsPhotodiodeAverage = 0.0f;
  for (int i = 0; i < PIN_WINDOWS_PHOTODIODE_SIZE; i++) {
    pinWindowsPhotodiodeAverage += pinWindowsPhotodiodeHistory[i];
  }
  pinWindowsPhotodiodeAverage /= PIN_WINDOWS_PHOTODIODE_SIZE;
  Serial.println(pinWindowsPhotodiodeAverage);
  if (isPowerOn && !isPowerOnConfirmed && millis() - timeAtReference > CONFIRMATION_PERIOD) {
    if (pinWindowsPhotodiodeAverage >= pinWindowsPhotodiodeReference + PIN_WINDOWS_PHOTODIODE_THRESHOLD) {
      isPowerOnConfirmed = true;
    } else {
      isPowerOn = false;
      timeAtReference = millis();
    }
  }
  delay(100);

  if (currentOut == PIN_ONE_IN && hotKeyboard[0] != LOW) {
    currentOut = -1;
    delay(30000);
    powerOn();
  } else if (currentOut == PIN_TWO_IN && hotKeyboard[1] != LOW) {
    digitalWrite(PIN_TWO_OUT, LOW);
    currentOut = -1;
    delay(30000);
    powerOn();
  } else if (currentOut == PIN_THREE_IN && hotKeyboard[2] != LOW) {
    currentOut = -1;
    delay(30000);
    powerOn();
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

void powerOn() {
  if (digitalRead(PIN_ONE_IN) == LOW) {
    delay(DELAY);
    digitalWrite(PIN_ONE_OUT, HIGH);
    delay(DELAY);
    digitalWrite(PIN_ONE_OUT, LOW);
    currentOut = PIN_ONE_IN;
  } else if (digitalRead(PIN_TWO_IN) == LOW) {
    delay(DELAY);
    digitalWrite(PIN_TWO_OUT, HIGH);
    currentOut = PIN_TWO_IN;
  } else if (digitalRead(PIN_THREE_IN) == LOW) {
    delay(DELAY);
    digitalWrite(PIN_THREE_OUT, HIGH);
    delay(DELAY);
    digitalWrite(PIN_THREE_OUT, LOW);
    currentOut = PIN_THREE_IN;
  }
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
