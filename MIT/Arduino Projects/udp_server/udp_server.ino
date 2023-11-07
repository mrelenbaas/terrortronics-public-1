/*
   Title: udp_server file.
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

const char * ssid = "YOUR WIFI NAME";
const char * password = "YOUR WIFI PASSWORD";

const char * one = "1";
//unsigned char* myChar;
char myChar[2] = {'1', '\0'};

bool is_light_on = false;
int pin1 = 12;
int pin2 = 21;
int pin3 = 22;
int pin4 = 13; // works

//AsyncUDPPacket packet
AsyncUDP udp;
ip_addr_t my_ip_address;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// the dns server ip
IPAddress dnServer(192, 168, 4, 1);
// the router's gateway address:
IPAddress gateway(192, 168, 0, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(192, 168, 4, 50);

bool isToggle = false;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:AsyncUDPServer,function:reset,delimiters: cm0; cm1; cm2; cm3; cm4;\n";
int incomingMessage;

void setup()
{
  pin1 = A0;
  pin1 = A1;
  pin2 = A2;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);

  Serial.begin(BAUD_RATE);
  /*
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, dnServer, gateway, subnet);
    //WiFi.begin(ssid, password);
    WiFi.begin();
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      while(1) {
          delay(1000);
      }
    }
    if(udp.listen(80)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {
          Serial.print("UDP Packet Type: ");
          Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
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

          char* somethingRaw = (char*)packet.data();
          //char* something = somethingRaw + "\0";
          const int someSize = packet.length();
          char something[someSize + 1];
          strcpy(something, somethingRaw);
          something[someSize] = '\0';

          //String someMessage = (String)something;
          Serial.print(something);
          Serial.print(" ?= ");
          if (!strcmp(something, "up"))
          {
            Serial.print("up");
            //digitalWrite(pin, HIGH);
            digitalWrite(pin, LOW);
          }
          else if (!strcmp(something, "down"))
          {
            Serial.print("down");
            //digitalWrite(pin2, HIGH);
            digitalWrite(pin2, LOW);
          }
          else if (!strcmp(something, "left"))
          {
            Serial.print("left");
            //digitalWrite(pin3, HIGH);
            digitalWrite(pin3, LOW);
          }
          else if (!strcmp(something, "right"))
          {
            Serial.print("right");
            //digitalWrite(pin4, HIGH);
            digitalWrite(pin4, LOW);
          }
          else if (!strcmp(something, "upstop"))
          {
            Serial.print("up stop");
            //digitalWrite(pin, LOW);
            digitalWrite(pin, HIGH);
          }
          else if (!strcmp(something, "downstop"))
          {
            Serial.print("down stop");
            //digitalWrite(pin2, LOW);
            digitalWrite(pin2, HIGH);
          }
          else if (!strcmp(something, "leftstop"))
          {
            Serial.print("left stop");
            //digitalWrite(pin3, LOW);
            digitalWrite(pin3, HIGH);
          }
          else if (!strcmp(something, "rightstop"))
          {
            Serial.print("right stop");
            //digitalWrite(pin4, LOW);
            digitalWrite(pin4, HIGH);
          }
          else if (something, "stop")
          {
            //digitalWrite(pin, LOW);
            //digitalWrite(pin2, LOW);
            //digitalWrite(pin3, LOW);
            //digitalWrite(pin4, LOW);
          }
          Serial.println("");
      });
    }

    //digitalWrite(pin, LOW);
    //digitalWrite(pin2, LOW);
  */
}

/**
   The main function.
*/
void loop()
{
  delay(2000);
  if (is_light_on == true)
  {
    //udp.broadcast("true");
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    Serial.println("LOW");
  } else {
    //udp.broadcast("false");
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    Serial.println("HIGH");
  }
  is_light_on = !is_light_on;

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
