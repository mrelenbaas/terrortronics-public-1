/*
   Title: rotary_encoder_rpm_file file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

// https://www.adafruit.com/product/3405
// https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
// https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
// https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview
// https://github.com/espressif/arduino-esp32
// https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
// https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
// https://docs.arduino.cc/built-in-examples/digital/toneMelody

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
const String OUTGOING_START = "type:config,filename:rotary_encoder_rpm_controller,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void IRAM_ATTR updateEncoder() {
  currentStateCLK3Flag = true;
  clkSet[specialCounter] = digitalRead(CLK);
  dwSet[specialCounter] = digitalRead(DT);
  specialCounter++;
}

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(RED_BUTTON, INPUT_PULLUP); //  Yellow.
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT); //  Yellow.
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!isWifiConnected) {
    //delay(1000);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.print(millis());
      Serial.println(": WiFi Failed");
      WiFi.begin(ssid, password);
      delay(1000);
    } else {
      isWifiConnected = true;
    }
  }

  // Play "Shave and a Haircut".
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    if (isBlinkOn) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
    isBlinkOn = !isBlinkOn;
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Set encoder pins as inputs
  pinMode(CLK, INPUT_PULLUP); // Green.
  pinMode(DT, INPUT_PULLUP); // Blue.
  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  attachInterrupt(CLK, updateEncoder, CHANGE);
  attachInterrupt(DT, updateEncoder, CHANGE);
}

/**
   The main function.
*/
void loop() {
  if (isRecordingFlag) {
    isRecordingFlag = false;
    // TODO: Remember that this block needs to modified to the needs of a project.
  }

  btnState = digitalRead(RED_BUTTON);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      //Serial.print("Button pressed!");
      btnState0 = true;
      digitalWrite(RED_LED, HIGH);
    }
    lastButtonPress = millis();
  } else {
    btnState0 = false;
    digitalWrite(RED_LED, LOW);
  }
  btnState = digitalRead(YELLOW_BUTTON);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState1 = true;
      digitalWrite(YELLOW_LED, HIGH);
    }
    lastButtonPress = millis();
  } else {
    btnState1 = false;
    digitalWrite(YELLOW_LED, LOW);
  }
  btnState = digitalRead(BLUE_BUTTON);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState2 = true;
      digitalWrite(BLUE_LED, HIGH);
    }
    lastButtonPress = millis();
  } else {
    btnState2 = false;
    digitalWrite(BLUE_LED, LOW);
  }
  btnState = digitalRead(GREEN_BUTTON);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState3 = true;
      digitalWrite(GREEN_LED, HIGH);
    }
    lastButtonPress = millis();
  } else {
    btnState3 = false;
    digitalWrite(GREEN_LED, LOW);
  }

  if (counter > INDEX_MAX) {
    counter = 0;
  }
  if (Serial.available() > 0) {
    // TODO: Remember to modifiy this on a per project basis.
  }

  specialCounter++;
  timeSinceStart = millis() - timeAtStart;
  if (timeSinceStart >= TIME_PERIOD) {
    timePercentage = abs(counter2) / STEPS;
    rps = totalSteps / STEPS;
    isRecording = false;
    counter2 = 0;
    angle = 0.0f;
    specialCounter = 0;
    totalSteps = 0.0f;
    fps = 0;
    timeAtStart = millis();
  }
  else {
    //Serial.println("");
  }

  lastStateCLK = currentStateCLK;
  for (int i = 0; i < specialCounter; i++) {
    if (currentStateCLK3Flag) {
      if (clkSet[i] != lastStateCLK3  && clkSet[i] == 1) {
        if (dwSet[i] != clkSet[i]) {
          counter3--;
          angle -= STEP;
          currentDir3 = "CCW";
          totalSteps += (float)specialCounter / 2.0f;
          specialCounter = 0;
        } else {
          counter3++;
          angle += STEP;
          currentDir3 = "CW";
          totalSteps += (float)specialCounter / 2.0f;
          specialCounter = 0;
        }
        if (!isRecording) {
          isRecordingFlag = true;
          isRecording = true;
          timeAtStart = millis();
        }
      }
      lastStateCLK3 = clkSet[i];
    }
    currentStateCLK3Flag = false;
    specialCounter = 0;
  }

  sprintf(
    udpBuffer,
    "%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s",
    millis(),
    btnState0,
    btnState1,
    btnState2,
    btnState3,
    counter3,
    String(angle),
    currentDir3,
    String(totalSteps),
    fps,
    String(rps));
  Serial.println(udpBuffer);
  udp.broadcastTo(udpBuffer, 9875);

  fps++;

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
