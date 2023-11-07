/**
 * @file inputer.h
 * 
 * Click manager.
 * 
 * @section author Author
 * - Created by Bradley Elenbaas on 12/23/2020.
 * - Modified by Bradley Elenbaas on 12/30/2020.
 *
 * Copyright (c) 2020 Bradley Elenbaas. All rights reserved.
 */

// 1st-party libraries.
#include <Arduino.h>

class Inputer {
public:
  // Constants.
  const int PIN = 8;
  // Functions.
  int updater();
  int get_analog_counter();
private:
  // Constants.
  const int ID = 1;               ///< Profile ID.
  const String PRINT = "Click: "; ///< Print before click count.
  // Variables.
  bool block = false; ///< Blocks button input from press to release.
  int count = 0;      ///< Button press count.
  int analog_counter;
  // Functions.
  void increment();
  bool is_pressed(int);
  void output();
};

int Inputer::get_analog_counter() {
  return analog_counter;
}

/**
 * Increment count.
 */
void Inputer::increment() {
  ++count;
}

/**
 * Filters raw input.
 * 
 * @param pressed Raw input.
 *
 * @return Filtered input.
 */
bool Inputer::is_pressed(int pressed) {
  bool result = false;
  if (!block && pressed) {
    result = true;
    block = true;
  } else if(block && !pressed) {
    block = false;
  }
  return result;
}

/**
 * Print click count.
 */
void Inputer::output() {
  Serial.print(PRINT);
  Serial.println(count);
}

/**
 * Increment count if button is pressed.
 * 
 * @param pressed Raw input.
 */
int Inputer::updater() {
  if(count > 0) {
    --count;
  }
  int pressed = digitalRead(PIN);
  if(is_pressed(pressed)) {
    increment();
    output();
    // added this
    analog_counter++;
    //analog_counter += 5;
    Serial.print("ANALOG_COUNTER: ");
    Serial.println(analog_counter);
    if (analog_counter >= 20) {
      analog_counter = 0;
    }
  }
  return count;
}
