/*
   Title: ultrasonic_sensor file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

// https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
// https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all

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
const String OUTGOING_START = "type:config,filename:ultrasonic_sensor,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void setup() {
  Serial.begin(BAUD_RATE);
  timeCurrent = millis();
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  timeThisSecond = timeDelta;
}

/**
   The main function.
*/
void loop() {
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  timeThisSecond += timeDelta;
  if (timeThisSecond >= PERIOD) {
    fpsPrevious = fpsCurrent;
    fpsCurrent = 0;
    timeThisSecond -= PERIOD;
    Serial.print("FPS: ");
    Serial.println(fpsPrevious);
  }// else {
  //  ++fpsCurrent;
  //}
  //delay(50);
  if (sonarIndex == 0) {
    unsigned int distance = sonar.ping_cm();
    Serial.print(distance);
    Serial.println(" cm0");
  } else if (sonarIndex == 1) {
    unsigned int distance1 = sonar1.ping_cm();
    Serial.print(distance1);
    Serial.println(" cm1");
  } else if (sonarIndex == 2) {
    unsigned int distance2 = sonar2.ping_cm();
    Serial.print(distance2);
    Serial.println(" cm2");
  } else if (sonarIndex == 3) {
    unsigned int distance3 = sonar3.ping_cm();
    Serial.print(distance3);
    Serial.println(" cm3");
  } else if (sonarIndex == 4) {
    unsigned int distance4 = sonar4.ping_cm();
    Serial.print(distance4);
    Serial.println(" cm4");
  }
  ++sonarIndex;
  if (sonarIndex >= SONAR_MAX) {
    sonarIndex = 0;
  } else {
    //++fpsCurrent;
  }
  ++fpsCurrent;
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
  //delay(10);
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
