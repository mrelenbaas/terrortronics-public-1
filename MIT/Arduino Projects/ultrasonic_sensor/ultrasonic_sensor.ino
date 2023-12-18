/**
   @file ultrasonic_sensors.ino

   @mainpage ultrasonic_sensors

   @section author Attribution
   - Title: Ultrasonic Sensors file.
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

   @section circuit Circuit
   - Board
    + Teensy LC
   - Buttons

   @section libraries Libraries
   - Serial

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
   - https://learn.sparkfun.com/tutorials/installing-an-arduino-library/all
   - https://stackoverflow.com/questions/1637332/static-const-vs-define

   @section warnings WARNINGS
   - empty
*/

// Include 2nd-party libraries.
#include "ultrasonic_sensor.h"

void setup() {
  Serial.begin(BAUD_RATE);
  //timeCurrent = millis();
  //timePrevious = timeCurrent;
  //timeCurrent = millis();
  //timeDelta = timeCurrent - timePrevious;
  //timeThisSecond = timeDelta;
  //pinMode(AVOID_PIN, INPUT);
  //pinMode(METAL_PIN, INPUT);
  //pinMode(LED, OUTPUT);
  //pinMode(SOUND_ANALOG, INPUT);
  //pinMode(SOUND_DIGITAL, INPUT_PULLUP);
  //pinMode(PAPER, INPUT_PULLUP);
  //pinMode(4, INPUT_PULLUP);
  pinMode(pinLightDebug, OUTPUT); // Remember that the Teensy doesn't let you do pinMode early, or something? Because I need to do it again for it to work.
}

/**
   The main function.
*/
void loop() {
  for (unsigned int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) { // TODO: Use unsigned int for other for loops.
    if (buttons[i].updateHotState() == 1) {
      //Serial.println("PRESSED 0");
      if (buttons[i].debounceByTimePress() == 1) {
        //Serial.println("PRESSED 1");
        if (buttons[i].debounceByPositionPress() == 1) {
          //Serial.println("PRESSED 2");
          if (buttons[i].debounceByBlockPress() == 1) {
            //Serial.println("PRESSED 3");
            if (buttons[i].debounceByTargetPress() == 1) {
              if (state.isRunning() == 1) {
                //Serial.println("PRESSED 4 (Running)");
              } else if (state.isWaiting() == 1) {
                //Serial.println("PRESSED 4 (Waiting)");
              }
            }
            buttons[i].delegateFunctionPress();
          }
        }
      }
      //buttons[i].debounceByPosition();
    } else {
      //Serial.println("PRESSED 0");
      if (buttons[i].debounceByTimeRelease() == 1) {
        //Serial.println("RELEASED 1");
        if (buttons[i].debounceByPositionRelease() == 1) {
          //Serial.println("RELEASED 2");
          if (buttons[i].debounceByBlockRelease() == 1) {
            //Serial.println("RELEASED 3");
            if (buttons[i].debounceByTargetRelease() == 1) {
              if (state.isRunning() == 1) {
                //Serial.println("RELEASED 4 (Running)");
                buttons[i].stopTargeting();
                buttons[i].delegateFunctionPress();
                // Do something else.
              } else if (state.isWaiting() == 1) {
                //Serial.println("RELEASED 4 (Waiting)");
                buttons[i].stopTargeting();
                //buttons[i].delegateFunctionRelease();
                state.startRunning();
                buttons[buttonReset].startTargeting();
              }
            }
            buttons[i].delegateFunctionRelease();
          }
        }
        buttons[i].reset();
      }
    }
  }
  /*
  if (digitalRead(4) == LOW) {
    //digitalWrite(13, HIGH);
    lights[lightDebug].turnOn();
  } else {
    //digitalWrite(13, LOW);
    lights[lightDebug].turnOff();
  }
  */
  /*
  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  timeThisSecond += timeDelta;
  if (timeThisSecond >= PERIOD) {
    fpsPrevious = fpsCurrent;
    fpsCurrent = 0;
    timeThisSecond -= PERIOD;
    if (led) {
      //digitalWrite(LED, HIGH);
    } else {
      //digitalWrite(LED, LOW);
    }
    led = !led;
    Serial.print("FPS: ");
    Serial.println(fpsPrevious);
  }// else {
  //  ++fpsCurrent;
  //}
  //delay(50);
  */
  //avoid = digitalRead(AVOID_PIN);
  //metal = analogRead(METAL_PIN);
  //soundAnalog = analogRead(SOUND_ANALOG);
  //soundDigital = digitalRead(SOUND_DIGITAL);
  //paper = digitalRead(PAPER);
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
  /*
  Serial.print(paper);
  Serial.println(" cm8");
  ++sonarIndex;
  if (sonarIndex >= SONAR_MAX) {
    sonarIndex = 0;
  } else {
    //++fpsCurrent;
  }

  ++fpsCurrent;
  */
  if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame
    // application.
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case messageStart:
        startFunction();
        break;
      case messageReset:
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
  IS_LOGGING = false;
}

void startFunction() {
  Serial.print(millis());
  Serial.print(": start(), ");
  Serial.println(OUTGOING_START);
  IS_LOGGING = true;
}

void startButtonFunctionPress() {
  Serial.println("startButtonFunction()");
  lights[lightDebug].turnOn();
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
}

/**
   Empty. The function to call then the Reset button is pressed.
*/
void resetButtonFunctionPress() {
  Serial.println("reset()");
}

void resetButtonFunctionRelease() {

}
