/**
 * @file ultrasonic_sensors.ino
 * 
 * @mainpage ultrasonic_sensors
 * 
 * @section author Attribution
 * - Title: Ultrasonic Sensors file.
 * - Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * - Version: 2
 * - Date: November 6, 2023.
 * 
 * @section ip Intellectual Property
 * - Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 * 
 * @section license License
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section description Description
 * Empty.
 * 
 * @section pins Pins
 * - empty
 * 
 * @section resources Resources
 * - https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 * - https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all
 * - https://stackoverflow.com/questions/1637332/static-const-vs-define
 * 
 * @section warnings WARNINGS
 * - empty
*/

#include "ultrasonic_sensor.h"

void setup() {
  Serial.begin(BAUD_RATE);
  timeCurrent = millis();
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  timeThisSecond = timeDelta;
  pinMode(AVOID_PIN, INPUT);
  pinMode(METAL_PIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(SOUND_ANALOG, INPUT);
  pinMode(SOUND_DIGITAL, INPUT_PULLUP);
  pinMode(PAPER, INPUT_PULLUP);
}

/**
 * The main function.
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
    if (led) {
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
    led = !led;
    Serial.print("FPS: ");
    Serial.println(fpsPrevious);
  }// else {
  //  ++fpsCurrent;
  //}
  //delay(50);
  avoid = digitalRead(AVOID_PIN);
  metal = analogRead(METAL_PIN);
  soundAnalog = analogRead(SOUND_ANALOG);
  soundDigital = digitalRead(SOUND_DIGITAL);
  paper = digitalRead(PAPER);
  /*
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
  */
  /*
  Serial.print(avoid);
  Serial.println(" cm5");
  */
  /*
  Serial.print(metal);
  Serial.println(" cm6");
  */
  /*
  Serial.print(soundAnalog);
  Serial.print(", ");
  Serial.print(soundDigital);
  Serial.println(" cm7");
  */
  Serial.print(paper);
  Serial.println(" cm8");
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
    // The error does occur when reading/writing in a PyGame 
    // application.
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case startMessage:
        startFunction();
        break;
      case resetMessage:
        resetFunction();
        break;
      default:
        break;
    }
  }
  //delay(10);
}

void resetFunction() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
  isLogging = false;
}

void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  isLogging = true;
}
