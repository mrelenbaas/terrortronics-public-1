/*
   Title: game_pad_controller file.
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
  @file game_pad_controller.ino

  @mainpage game_pad_controller

  @section author Attribution
  - Title: Gamepad Controller file.
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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <HardwareSerial.h>

// this can be used to turn profiling on and off
#define PROFILING 1
// this needs to be true in at least ONE .c, .cpp, or .ino file in your sketch
#define PROFILING_MAIN 1
// override the number of bins
#define MAXPROF 8
#include "profiler.h"

// some handy macros for printing debugging values
//#define DL(x) Serial.print(x)
//#define DLn(x) Serial.println(x)
//#define DV(m, v) do{Serial.print(m);Serial.print(v);Serial.print(" ");}while(0)
//#define DVn(m, v) do{Serial.print(m);Serial.println(v);}while(0)

// more handy macros but unused in this example
#define InterruptOff  do{TIMSK2 &= ~(1<<TOIE2)}while(0)
#define InterruptOn  do{TIMSK2 |= (1<<TOIE2)}while(0)

// stuff used for time keeping in our ISR
volatile unsigned int int_counter;
volatile unsigned char seconds, minutes;
unsigned int tcnt2; // used to store timer value

// Arduino runs at 16 Mhz, so we have 1000 overflows per second...
// this ISR will get hit once a millisecond
ISR(TIMER2_OVF_vect) {

  int_counter++;
  if (int_counter == 1000) {
    seconds++;
    int_counter = 0;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
    }
  }
#if PROFILING
  prof_array[prof_line]++;
#endif
  TCNT2 = tcnt2;  // reset the timer for next time
}

// Timer setup code borrowed from Sebastian Wallin
// http://popdevelop.com/2010/04/mastering-timer-interrupts-on-the-arduino/
// further borrowed from: http://www.desert-home.com/p/super-thermostat.html
void setupTimer (void) {
  //Timer2 Settings:  Timer Prescaler /1024
  // First disable the timer overflow interrupt while we're configuring
  TIMSK2 &= ~(1 << TOIE2);
  // Configure timer2 in normal mode (pure counting, no PWM etc.)
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  // Select clock source: internal I/O clock
  ASSR &= ~(1 << AS2);
  // Disable Compare Match A interrupt enable (only want overflow)
  TIMSK2 &= ~(1 << OCIE2A);

  // Now configure the prescaler to CPU clock divided by 128
  TCCR2B |= (1 << CS22)  | (1 << CS20); // Set bits
  TCCR2B &= ~(1 << CS21);           // Clear bit

  /* We need to calculate a proper value to load the timer counter.
     The following loads the value 131 into the Timer 2 counter register
     The math behind this is:
     (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
     (desired period) / 8us = 125.
     MAX(uint8) - 125 = 131;
  */
  /* Save value globally for later reload in ISR */
  tcnt2 = 131;

  /* Finally load end enable the timer */
  TCNT2 = tcnt2;
  TIMSK2 |= (1 << TOIE2);
  sei();
}

volatile long long_waste;

// because this has "PF(2)", when the processor is executing here, it
// will cause the value in bin "2" to increase.
// "__attribute__ ((noinline))" needed to prevent inlining of these
// trivial functions.  The inlining by the compiler broke the profiling.
void __attribute__ ((noinline)) big_cpu_fn_1 (void) {
  long lo;
  PF(2);
  for (lo = 1L ; lo < 8600L ; lo++) {
    long_waste += lo;
  }
  // DVn("1 lw ", long_waste);
}

// because this has "PF(3)", when the processor is executing here, it
// will cause the value in bin "3" to increase.
// "__attribute__ ((noinline))" needed to prevent inlining of these
// trivial functions.  The inlining by the compiler broke the profiling.
void __attribute__ ((noinline)) big_cpu_fn_2 (void) {
  long lo;
  PF(3);
  for (lo = 1L ; lo < 29900L ; lo++) {
    long_waste -= lo;
  }
  // DVn("2 lw ", long_waste);
}

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

const int SERIAL_DELAY = 10;

// Pin constants.
const int HORIZONTAL = A0;
const int VERTICAL = A1;
const int BUTTON = 2;
const int SILICONE_BUTTON = 3;

// Hot keyboard.
int horizontal;
int vertical;
int button;
int siliconeButton;

// Messages.
enum messages {
  startMessage = 48,
  resetMessage = 49
};
const char OUTGOING_START[] = {
  't',
  'y',
  'p',
  'e',
  ':',
  'c',
  'o',
  'n',
  'f',
  'i',
  'g',
  ',',
  'f',
  'i',
  'l',
  'e',
  'n',
  'a',
  'm',
  'e',
  ':',
  'g',
  'a',
  'm',
  'e',
  '_',
  'p',
  'a',
  'd',
  '_',
  'c',
  'o',
  'n',
  't',
  'r',
  'o',
  'l',
  'l',
  'e',
  'r',
  ',',
  'f',
  'u',
  'n',
  'c',
  't',
  'i',
  'o',
  'n',
  ':',
  'r',
  'e',
  's',
  'e',
  't',
  ',',
  'd',
  'e',
  'l',
  'i',
  'm',
  'i',
  't',
  'e',
  'r',
  's',
  ':',
  ' ',
  'c',
  'm',
  '0',
  ';',
  ' ',
  'c',
  'm',
  '1',
  ';',
  ' ',
  'c',
  'm',
  '2',
  ';',
  ' ',
  'c',
  'm',
  '3',
  ';',
  ' ',
  'c',
  'm',
  '4',
  ';',
  '\\',
  'n',
  '\0'
};
int incomingMessage;

const long PERIOD = 1000;
long timePrevious;
long timeCurrent;
long timeDelta;
long timeThisSecond;
unsigned long fpsPrevious;
unsigned long fpsCurrent;

// Pseudo-constructor.
void setup() {
#if PROFILING
  PF(0);
  prof_has_dumped = 0;
  clear_profiling_data();
#endif

  Serial.begin(BAUD_RATE);

  Serial.println("setup()");

  int_counter = 0;
  seconds = 0;
  minutes = 0;

  Serial.println("setupTimer()");
  setupTimer();

  pinMode(HORIZONTAL, INPUT);
  pinMode(VERTICAL, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SILICONE_BUTTON, INPUT_PULLUP);

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
  unsigned char op;

  PF(1);
  //big_cpu_fn_1(); // goes in bin 2
  //big_cpu_fn_2(); // goes in bin 3
  //mydelay(20);  // goes in bin 7
  PF(1);  // rest of this should go in profiling bin 1
  op ^= 1;
  digitalWrite(1, op & 1);  // toggle a pin so we can see loop rate
  //if (int_counter < 110) {
    //DVn("sec ", seconds);
  //}
#if PROFILING
  if (seconds % 60 == 3 && !prof_has_dumped) {
    dump_profiling_data();  // also clears profiling data
  }
  if (seconds % 60 == 4 && prof_has_dumped) {
    prof_has_dumped = 0;
  }
#endif

  timePrevious = timeCurrent;
  timeCurrent = millis();
  timeDelta = timeCurrent - timePrevious;
  timeThisSecond += timeDelta;
  if (timeThisSecond >= PERIOD) {
    fpsPrevious = fpsCurrent;
    fpsCurrent = 0;
    timeThisSecond -= PERIOD;
    Serial.print("FPS: ");
    Serial.println(fpsPrevious);
  } else {
    ++fpsCurrent;
  }

  horizontal = analogRead(HORIZONTAL);
  vertical = analogRead(VERTICAL);
  button = digitalRead(BUTTON);
  siliconeButton = digitalRead(SILICONE_BUTTON);

  //Serial.flush();
  Serial.print(horizontal);
  Serial.print(", ");
  Serial.print(vertical);
  Serial.print(", ");
  Serial.print(button);
  Serial.print(", ");
  Serial.println(siliconeButton);

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

  //delay(SERIAL_DELAY);
}

void reset() {
  //Serial.println("reset()");
}

void start() {
  //Serial.print("start(): ");
  //Serial.println(OUTGOING_START);
}
