/*
 * Title: udp_broadcast file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the Arduino License.
 */

// TODO: Think about using the PS/2 joystick input from this file.

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
const char SERVICE_SET_IDENTIFIER[] = "YOUR WIFI NAME";
const char PASSWORD[] = "YOUR WIFI PASSWORD";
const int IP_0 = 192;
const int IP_1 = 168;
const int IP_2 = 1;
const int IP_3 = 70;
const int PORT = 50007;
const int DELAY = 10;

// Pin constants.
const int PIN_LED = 14;
const int PIN_UP = 13;
const int PIN_DOWN = 12;
const int PIN_LEFT = 27;
const int PIN_RIGHT = 15;
const int PIN_X = A2;
const int PIN_Y = A3;
const int PIN_LEFT_3 = 21;
const int ANALOG_LOWER = 800;
const int ANALOG_UPPER = 2800;

// Output constants.
const char OUTPUT_ORIGINAL[] = "feather,00000000000000000000000000000000000000\r\n";
const int OUTPUT_SIZE = 48;
const char DATA_UP[] = "up000,";
const char DATA_DOWN[] = "down0,";
const char DATA_LEFT[] = "left0,";
const char DATA_RIGHT[] = "right,";
const char DATA_MIDDLE[] = "l3000,";
const char DATA_ZERO = '0';
const int DATA_SIZE = 6;
const int DATA_START = 8;

// Output.
char output[] = "feather,00000000000000000000000000000000000000\r\n";
int output_index = 0;

// Pin states.
int up_digital;
int down_digital;
int left_digital;
int right_digital;
int x_analog;
int y_analog;
int up_analog;
int down_analog;
int left_analog;
int right_analog;
int left3_digital;

// Network components.
AsyncUDP udp;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const String OUTGOING_START = "type:config,filename:adafruit_huzzah32_esp_32_feather,function:reset\n";
int incomingMessage;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_LEFT_3, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SERVICE_SET_IDENTIFIER, PASSWORD);
  WiFi.waitForConnectResult();
  udp.connect(IPAddress(IP_0, IP_1, IP_2, IP_3), PORT);
  digitalWrite(PIN_LED, HIGH);
}

/**
 * The main function.
 */
void loop() {
  update_state();
  update_output(DATA_UP, (up_digital || up_analog));
  update_output(DATA_DOWN, (down_digital || down_analog));
  update_output(DATA_LEFT, (left_digital || left_analog));
  update_output(DATA_RIGHT, (right_digital || right_analog));
  update_output(DATA_MIDDLE, left3_digital != 0);
  udp.broadcastTo(output, PORT);
  reset();
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

void reset()
{
  delay(DELAY);
  output_index = 0;
  for (int i = 0; i < OUTPUT_SIZE; i++)
  {
    output[i] = OUTPUT_ORIGINAL[i];
  }
}

void update_state()
{
  up_digital = !digitalRead(PIN_UP);
  down_digital = !digitalRead(PIN_DOWN);
  left_digital = !digitalRead(PIN_LEFT);
  right_digital = !digitalRead(PIN_RIGHT);
  x_analog = analogRead(PIN_X);
  y_analog = analogRead(PIN_Y);
  up_analog = !analog_above_threshold(y_analog);
  down_analog = !analog_below_threshold(y_analog);
  left_analog = !analog_above_threshold(x_analog);
  right_analog = !analog_below_threshold(x_analog);
  left3_digital = !digitalRead(PIN_LEFT_3);
}

bool analog_above_threshold(int axis)
{
  if (axis < ANALOG_LOWER)
  {
    return false;
  }
  return true;
}

bool analog_below_threshold(int axis)
{
  if (axis > ANALOG_UPPER)
  {
    return false;
  }
  return true;
}

void update_output(const char text[], bool active)
{
  if (active)
  {
    write_data(text);
  }
  else
  {
    clear_data();
  }
  ++output_index;
}

void write_data(const char text[])
{
  for (int i = (DATA_START + (DATA_SIZE * output_index)), j = 0; j < DATA_SIZE; ++i, ++j)
  {
    output[i] = text[j];
  }
}

void clear_data()
{
  for (int i = (DATA_START + (DATA_SIZE * output_index)), j = 0; j < DATA_SIZE; ++i, ++j)
  {
    output[i] = DATA_ZERO;
  }
}

void start() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}
