/*
   Title: fps file.
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
const String OUTGOING_START = "type:config,filename:fps,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
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
    Serial.println(fpsPrevious);
  } else {
    ++fpsCurrent;
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
