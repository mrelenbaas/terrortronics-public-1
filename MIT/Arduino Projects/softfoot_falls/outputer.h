/**
 * @file outputer.h
 * 
 * Output manager.
 * 
 * @section author Author
 * - Created by Bradley Elenbaas on 12/30/2020.
 * - Modified by Bradley Elenbaas on 12/31/2020.
 *
 * Copyright (c) 2020 Bradley Elenbaas. All rights reserved.
 */

// 1st-party libraries.
#include <Arduino.h>

#include "timer.h"

class Outputer {
public:
  // Constants.
  const int PIN_ONE = 12; ///< Blue LED.
  const int PIN_TWO = 13; ///< White LED.
  //const int BIN_ONE = 11;
  const int BIN_TWO = 10;
  const int BIN_THREE = 9;
  const int BIN_FOUR = 6;
  const int BIN_FIVE = 5;
  //const int BIN_SIX = 3;
  // Functions.
  void starter();
  void updater(int, int);
  void updater_other(int, int, int, int);
private:
  // Variables.
  bool block = true; ///< Toggles if TRUE is received at update.
  int bin_one;
  int bin_two;
  int bin_three;
  int bin_four;
  Timer timer;
  // Functions.
  void draw_screen_one();
  void draw_screen_two();
  void output(int);
};

/**
 * Enable blue LED.
 */
void Outputer::draw_screen_one() {
  digitalWrite(PIN_ONE, HIGH);
  digitalWrite(PIN_TWO, LOW);
}

/**
 * Enable white LED.
 */
void Outputer::draw_screen_two() {
  digitalWrite(PIN_TWO, HIGH);
  digitalWrite(PIN_ONE, LOW);
}

void Outputer::output(int count) {
  Serial.print("Click: ");
  Serial.println(count);
}

/**
 * Pseudo-constructor.
 */
void Outputer::starter() {
  //pinMode(PIN_ONE, OUTPUT);
  pinMode(PIN_TWO, OUTPUT);
  //pinMode(BIN_ONE, OUTPUT);
  pinMode(BIN_TWO, OUTPUT);
  pinMode(BIN_THREE, OUTPUT);
  pinMode(BIN_FOUR, OUTPUT);
  pinMode(BIN_FIVE, OUTPUT);
  //pinMode(BIN_SIX, OUTPUT);
}

void Outputer::updater_other(int one, int two, int three, int four) {
  bin_one = one;
  bin_two = two;
  bin_three = three;
  bin_four = four;
}

/**
 * Toggle between two screens.
 */
void Outputer::updater(int count, int analog_counter) {
  timer.updater();
  /*
  block = !block;
  output(count);

  float one_f = 20.0 * ((float)bin_one / 1000.0);
  float two_f = 20.0 * ((float)bin_two / 1000.0);
  float three_f = 20.0 * ((float)bin_three / 1000.0);
  float four_f = 20.0 * ((float)bin_four / 1000.0);
  int one = (int)one_f;
  int two = (int)two_f;
  int three = (int)three_f;
  int four = (int)four_f;
  analogWrite(BIN_TWO, one);
  analogWrite(BIN_THREE, two);
  analogWrite(BIN_FOUR, three);
  analogWrite(BIN_FIVE, four);
  */
  if (count > 0) {
    if(block) {
      draw_screen_one();
    } else {
      draw_screen_two();
    }
  }
  else {
    digitalWrite(PIN_TWO, LOW);
    digitalWrite(PIN_ONE, LOW);
  }
}
