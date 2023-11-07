/*
   Title: udp_client file.
   Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   Version: 2
   Date: September 15, 2023

   Intellectual Property:
   Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   License:
   This file is owned by Terrortronics / Bradley Elenbaas.
   This file observes the MIT License.
*/

/**
   @file udp_client.ino

   @mainpage udp_client

   @section author Attribution
   - Title: UDP Client file.
   - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
   - Version: 2
   - Date: November 6, 2023.

   @section ip Intellectual Property
   - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.

   @section license License
   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation files
   (the “Software”), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - empty

   @section warnings WARNINGS
   - empty
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

const char * ssid = "YOUR WIFI NAME";
const char * password = "YOUR WIFI PASSWORD";

AsyncUDP udp;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:AsyncUDPClient,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void setup()
{
  Serial.begin(BAUD_RATE);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(10000);
    }
  }
  if (udp.connect(IPAddress(192, 168, 1, 4), 1234)) {
    Serial.println("UDP connected");
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      //reply to the client
      packet.printf("Got %u bytes of data", packet.length());
      delay(1000);
    });
    //Send unicast
    udp.print("Hello Server!");
  }
}

/**
   The main function.
*/
void loop()
{
  delay(10000000);
  //Send broadcast on port 1234
  udp.broadcastTo("Anyone here?", 1234);

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
