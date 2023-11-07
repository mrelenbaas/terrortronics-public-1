/*
   Title: hall_effect_sensor file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the Arduino License.
*/

#include "WiFi.h"
#include "AsyncUDP.h"

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

// Network constants.
const char SERVICE_SET_IDENTIFIER[] = "[AP NAME]";
const char PASSWORD[] = "[AP PASSWORD]";
const int IP_0 = 192;
const int IP_1 = 168;
const int IP_2 = 1;
const int IP_3 = 8;
const int PORT = 50007;
const int DELAY = 10;

char output[] = "0\r\n";

// Network components.
AsyncUDP udp;

int buttonpin = 14;
int val;//Define numeric variable val

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:adafruit_huzzah32_esp_32_feather,function:reset\n";
int incomingMessage;

void setup()
{
  Serial.begin(BAUDE_RATE);
  pinMode(buttonpin, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SERVICE_SET_IDENTIFIER, PASSWORD);
  WiFi.waitForConnectResult();
  udp.connect(IPAddress(IP_0, IP_1, IP_2, IP_3), PORT);
}

/**
 * The main function.
 */
void loop()
{
  val = digitalRead(buttonpin);
  if (val == HIGH)
  {
    Serial.println("HIGH");
    //output = "1\r\n";
    output[0] = '1';
  }
  else
  {
    Serial.println("LOW");
    //output = "0\r\n";
    output[0] = '0';
  }
  udp.broadcastTo(output, PORT);

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

  delay(DELAY);
}

void reset() {
  Serial.println("reset()");
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
