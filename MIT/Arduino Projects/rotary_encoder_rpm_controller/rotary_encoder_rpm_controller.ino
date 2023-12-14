/**
   @file rotary_encoder_rpm_controller.ino

   @mainpage rotary_encoder_rpm_controller

   @section author Attribution
   - Title: Rotary Encoder RPM Controller file.
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
    + Adafruit Feather HUZZAH ESP32
   - Buttons

   @section libraries Libraries
   - Serial

   @section description Description
   Empty.

   @section pins Pins
   - empty

   @section resources Resources
   - https://www.adafruit.com/product/3405
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
   - https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
   - https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview
   - https://github.com/espressif/arduino-esp32
   - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
   - https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
   - https://docs.arduino.cc/built-in-examples/digital/toneMelody

   @section warnings WARNINGS
   - empty
*/

// Include 2nd-party libraries.
#include "rotary_encoder_rpm_controller.h"

void IRAM_ATTR updateEncoder() {
  currentStateCLK3Flag = true;
  clkSet[specialCounter] = digitalRead(CLK);
  dwSet[specialCounter] = digitalRead(DT);
  specialCounter++;
}

// Pseudo-constructor.
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(RED_BUTTON, INPUT_PULLUP); //  Yellow.
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT); //  Yellow.
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(21, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!isWifiConnected) {
    //delay(1000);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.print(millis());
      Serial.println(": WiFi Failed");
      WiFi.begin(ssid, password);
      delay(1000);
    } else {
      isWifiConnected = true;
    }
  }

  // Play "Shave and a Haircut".
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    if (isBlinkOn) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
    isBlinkOn = !isBlinkOn;
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Set encoder pins as inputs
  pinMode(CLK, INPUT_PULLUP); // Green.
  pinMode(DT, INPUT_PULLUP); // Blue.
  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  attachInterrupt(CLK, updateEncoder, CHANGE);
  attachInterrupt(DT, updateEncoder, CHANGE);

  pinMode(21, INPUT_PULLUP);
}

/**
   The main function.
*/
void loop() {
  /*
    if (digitalRead(21) == LOW) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    }
  */
  for (int i = 0; i < (sizeof(buttons) / sizeof(Button)); ++i) {
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
    if (isRecordingFlag) {
    isRecordingFlag = false;
    // TODO: Remember that this block needs to modified to the needs of a project.
    }

    btnState = digitalRead(RED_BUTTON);
    if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      //Serial.print("Button pressed!");
      btnState0 = true;
      digitalWrite(RED_LED, HIGH);
    }
    lastButtonPress = millis();
    } else {
    btnState0 = false;
    digitalWrite(RED_LED, LOW);
    }
    btnState = digitalRead(YELLOW_BUTTON);
    if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState1 = true;
      digitalWrite(YELLOW_LED, HIGH);
    }
    lastButtonPress = millis();
    } else {
    btnState1 = false;
    digitalWrite(YELLOW_LED, LOW);
    }
    btnState = digitalRead(BLUE_BUTTON);
    if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState2 = true;
      digitalWrite(BLUE_LED, HIGH);
    }
    lastButtonPress = millis();
    } else {
    btnState2 = false;
    digitalWrite(BLUE_LED, LOW);
    }
    btnState = digitalRead(GREEN_BUTTON);
    if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btnState3 = true;
      digitalWrite(GREEN_LED, HIGH);
    }
    lastButtonPress = millis();
    } else {
    btnState3 = false;
    digitalWrite(GREEN_LED, LOW);
    }

    if (digitalRead(21) == LOW) {
    Serial.println("ON");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    } else {
    Serial.println("OFF");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    }

    if (counter > INDEX_MAX) {
    counter = 0;
    }

    specialCounter++;
    timeSinceStart = millis() - timeAtStart;
    if (timeSinceStart >= TIME_PERIOD) {
    timePercentage = abs(counter2) / STEPS;
    rps = totalSteps / STEPS;
    isRecording = false;
    counter2 = 0;
    angle = 0.0f;
    specialCounter = 0;
    totalSteps = 0.0f;
    fps = 0;
    timeAtStart = millis();
    }
    else {
    //Serial.println("");
    }

    lastStateCLK = currentStateCLK;
    for (int i = 0; i < specialCounter; i++) {
    if (currentStateCLK3Flag) {
      if (clkSet[i] != lastStateCLK3  && clkSet[i] == 1) {
        if (dwSet[i] != clkSet[i]) {
          counter3--;
          angle -= STEP;
          currentDir3 = "CCW";
          totalSteps += (float)specialCounter / 2.0f;
          specialCounter = 0;
        } else {
          counter3++;
          angle += STEP;
          currentDir3 = "CW";
          totalSteps += (float)specialCounter / 2.0f;
          specialCounter = 0;
        }
        if (!isRecording) {
          isRecordingFlag = true;
          isRecording = true;
          timeAtStart = millis();
        }
      }
      lastStateCLK3 = clkSet[i];
    }
    currentStateCLK3Flag = false;
    specialCounter = 0;
    }

    sprintf(
    udpBuffer,
    "%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%s",
    millis(),
    btnState0,
    btnState1,
    btnState2,
    btnState3,
    counter3,
    String(angle),
    currentDir3,
    String(totalSteps),
    fps,
    String(rps));
    Serial.println(udpBuffer);
    udp.broadcastTo(udpBuffer, 9875);

    fps++;

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

    delay(SERIAL_DELAY);
  */
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

void startButtonFunctionPress() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  Serial.println("startButtonFunction()");
}

void startButtonFunctionRelease() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

/**
   Empty. The function to call then the Reset button is pressed.
*/
void resetButtonFunctionPress() {
  Serial.println("reset()");
}

void resetButtonFunctionRelease() {

}
