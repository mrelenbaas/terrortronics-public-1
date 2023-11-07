/**
 * @file profiler.h
 * 
 * Profiler manager.
 * 
 * Counts function calls into bins.
 * 
 * @section author Author
 * - Created by Bradley Elenbaas on 12/28/2020.
 * - Modified by Bradley Elenbaas on 12/31/2020.
 *
 * Copyright (c) 2020 Bradley Elenbaas. All rights reserved.
 */

int ID_INPUTER = 0;
int ID_OUTPUTER = 1;
int ID_OTHER = 3;

// Functions stubs.
void profile_clear();
void profile_dump();
void profile_print();
void profile_set(int);
void profile_setup();
void timer_disable_overflow();
void timer_enable_overflow();
void timer_set_clock_to_internal_io();
void timer_set_timer_prescaler();
void timer_set_timer_to_normal_mode();
void timer_setup();
void timer_start();
// Constants.
const int ISR_DELAY_FOR_STARTUP = 3;        ///< Startup delay.
const int ISR_DELAY_FOR_DUMP = 4;           ///< Dump delay.
const int ISR_TIMER_COUNT = 131;            ///< 131=MAX(uint8)-((desiredPeriod)/(CPUFrequency/prescalerValue))
const String PRINT_PROFILE_PREFIX = "Bin["; ///< Print before bin index.
const String PRINT_PROFILE_POSTFIX = "] ";  ///< Print after bin index.
const int PROFILE_PERIOD = 1000;            ///< Period of a profile.
const int PROFILE_SIZE = 4;                 ///< Bin count.
// Variables.
int profile_array[PROFILE_SIZE]; ///< Bins.
int profile_index = 0;           ///< Bin index.

/**
 * Increments count of current bin once per millisecond.
 * 
 * @param TIMER2_OVF_vect Not used.
 */
ISR(TIMER2_OVF_vect) {
  ++profile_array[profile_index];
}

/**
 * Clear profile.
 */
void profile_clear() {  
  for(int i = 0 ; i < PROFILE_SIZE ; i++) {
    profile_array[i] = 0;
  }
}

/**
 * Print & clear profile.
 */
void profile_dump() {
  //profile_print();
  profile_clear();
}

/**
 * Print profile.
 */
void profile_print() {
  Serial.println("");
  for(int i = 0 ; i < PROFILE_SIZE ; i++) {
    Serial.print(PRINT_PROFILE_PREFIX);
    Serial.print((int)i);
    Serial.print(PRINT_PROFILE_POSTFIX);
    Serial.println((unsigned int)profile_array[i]);
  }
  Serial.println("");
}

/**
 * Set bin.
 *
 * @param index New index.
 */
void profile_set(int index) {
  profile_index = index;
}

/**
 * Setup timer.
 */
void profile_setup() {
  profile_clear();
  timer_setup();
}

/**
 * Disable timer overflow.
 */
void timer_disable_overflow() {
  TIMSK2 &= ~(1<<TOIE2);
}

/**
 * Enable timer overflow.
 */
void timer_enable_overflow() {
  TIMSK2 &= ~(1<<OCIE2A);
}

/**
 * Set clock to use the internal IO.
 */
void timer_set_clock_to_internal_io() {
  ASSR &= ~(1<<AS2);
}

/**
 * Set timer prescaler.
 */
void timer_set_timer_prescaler() {
  TCCR2B |= (1<<CS22) | (1<<CS20);
  TCCR2B &= ~(1<<CS21);
}

/**
 * Set timer mode to normal.
 */
void timer_set_timer_to_normal_mode() {
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
}

/**
 * Setup timer.
 */
void timer_setup() {
  timer_disable_overflow();
  timer_set_timer_to_normal_mode();
  timer_set_clock_to_internal_io();
  timer_enable_overflow();
  timer_set_timer_prescaler();
  timer_start();
}

/**
 * Start timer.
 */
void timer_start() {
  TCNT2 = ISR_TIMER_COUNT;
  TIMSK2 |= (1<<TOIE2);
  sei();
}
