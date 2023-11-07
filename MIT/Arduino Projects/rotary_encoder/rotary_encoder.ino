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

/*
   Posted on https://randomnerdtutorials.com
   created by http://playground.arduino.cc/Code/NewPing

   https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
   https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all
*/

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

#define CW_START_CLK 0
#define CW_START_DT 0
#define CW_END_CLK 1
#define CW_END_DT 1
#define CCW_START_CLK 0
#define CCW_START_DT 1
#define CCW_END_CLK 1
#define CCW_END_DT 0

int CLK = 2;//CLK->D2
int DT = 3;//DT->D3
int SW = 4;//SW->D4
//const int interrupt0 = 0;
const int interrupt0 = 0;
const int interrupt1 = 1;
int count = 0;
int lastCLK = 0;

int stage = -1;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:rotary_encoder,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void setup()
{
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  //attachInterrupt(interrupt0, ClockChanged, CHANGE);
  attachInterrupt(interrupt0, ClockRising, RISING);
  attachInterrupt(interrupt1, ClockFalling, FALLING);
  Serial.begin(BAUD_RATE);
}

/**
 * The main function.
 */
void loop()
{
  if (!digitalRead(SW))
  {
    count++;
    Serial.print("count:");
    Serial.println(count);
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

void ClockChanged()
{
  Serial.println("HERE");
}

void ClockRising()
{
  Serial.println("RISING");
}

void ClockFalling()
{
  Serial.println("FALLING");
}
