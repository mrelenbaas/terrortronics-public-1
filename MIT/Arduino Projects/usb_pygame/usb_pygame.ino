/*
   Title: usb_pygame file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

/**
   @file tug_of_war_controller.ino

   @section description Description
   The controller component of the Tug-of-War application.

   @section pins Pins
   - LEDs are connected to pins D22-D34.
   - Micro-Switches are connected to pins D35-D50.
   - The Motor directions are connected to pins D51-D52.

   @section warnings WARNINGS
   - DO NO USE THIS EXAMPLE (https://reference.arduino.cc/reference/en/language/functions/communication/serial/readstring/) (Reason #1): The readString function may cause memory leaks.
   - DO NO USE THIS EXAMPLE (https://reference.arduino.cc/reference/en/language/functions/communication/serial/readstring/) (Reason #2): The Serial blocking code breaks on Unity Standalone Windows builds.
   - DO NOT USE the pySerial.write() call inside any PyGame code, and instead use the Thread library to seperate their respective blocks with flags to move data back and forth.
*/

#include <Keyboard.h>

/**
   Baud rate (pair with PC).
*/
const int SERIAL_BAUD_RATE = 9600;
/**
   Delay that occurs near the end of each loop.
*/
const int SERIAL_DELAY = 10;

/**
   Command to turn the left "Winner of this Round" light on.
*/
/**
   Command to turn the "Ready" light on.
*/
const String INCOMING_LIGHT_READY_ON = "28";
/**
   Command to turn the "Ready" light off.
*/
const String INCOMING_LIGHT_READY_OFF = "41";
/**
   Command to turn the "One" light off.
*/
const String INCOMING_BUFFERS[] = {
  INCOMING_LIGHT_READY_ON,
  INCOMING_LIGHT_READY_OFF
};
/**
   Enum paired with the INCOMING_BUFFERS array.
*/
enum IncomingCommands {
  LIGHT_READY_ON,
  LIGHT_READY_OFF
};
/**
   A 2 byte buffer for incoming data in the form of a byte array.
*/
byte incomingBufferBytes[2];
/**
   A 2 byte buffer for incoming data in the form of a String.
*/
String incomingBufferString = "00";

/**
   Delimites the start of a set of data.
*/
const String OUTGOING_BUFFER_DELIMITER_START = "8";
/**
   Delimites the end of a set of data.
*/
const String OUTGOING_BUFFER_DELIMITER_STOP = "9";
/**
   Delimites a single set of data.
*/
const String OUTGOING_BUFFER_DELIMITER_SPLITTER = ",";
/**
   A 14 byte buffer updated during the interrupt functions and used as part of the 32 byte outgoing data sent to Serial during 
   the loop() function.
*/
bool outgoingBuffer[1];
/**
   Enum paired with the outgoingBuffer array.
 */
enum OutgoingCommands {
  BUTTON_START
};

/**
   Pin controlling the trigger of the relay gating 5-12 volt input to the "Ready" light bulb.
 */
const int PIN_LIGHT_READY = 28;

/**
   Pin monitoring the micro-switch connected to the Start arcade button.
 */
const int PIN_START = 35;

bool isStartBlocked;

long timeCurrent;
long timePrevious;
long timeDelta;
long timeFPS;
long timeFPSPrevious;
long timeSinceStart;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:usb_pygame,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

/**
   Set up Serial, pinMode(int, int), digitalWrite(int, int), attachInterrupt(int, function, int) calls.
*/
void setup() {
  Keyboard.begin();
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.flush();
  pinMode(PIN_LIGHT_READY, OUTPUT);
  pinMode(PIN_START, INPUT_PULLUP);
  digitalWrite(PIN_LIGHT_READY, LOW);
  timeCurrent = millis();
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timePrevious - timeCurrent;
  timeSinceStart += timeDelta;
}

/**
   The main loop.
*/
void loop() {
  if (digitalRead(PIN_START) && isStartBlocked) {
    isStartBlocked = false;
  }
  if (!digitalRead(PIN_START) && !isStartBlocked) {
    Keyboard.press('b');
    Keyboard.release('b');
    isStartBlocked = true;
  }
  
  if (Serial.available() > 1) {
    Serial.readBytes(incomingBufferBytes, sizeof(incomingBufferBytes));
    incomingBufferString[0] = incomingBufferBytes[0];
    incomingBufferString[1] = incomingBufferBytes[1];
    if (incomingBufferString == INCOMING_BUFFERS[LIGHT_READY_ON]) {
      digitalWrite(PIN_LIGHT_READY, HIGH);
    }
    if (incomingBufferString == INCOMING_BUFFERS[LIGHT_READY_OFF]) {
      digitalWrite(PIN_LIGHT_READY, LOW);
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
  delay(SERIAL_DELAY);
  Serial.flush();
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
