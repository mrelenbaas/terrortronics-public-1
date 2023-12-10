#include "Arduino.h"
#include "common.h"

////////////////////////////////////////////////////////////////////////
// Constructors ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
ThumbStick::ThumbStick(int pinHorizontal, int pinVertical) {
  this->pinHorizontal = pinHorizontal;
  this->pinVertical = pinVertical;
  pinMode(pinHorizontal, INPUT);
  pinMode(pinVertical, INPUT);
}

Button::Button(int pin,
               Timer timer,
               unsigned long periodStart,
               unsigned long periodStop,
               void (*delegateFunction)()) {
  this->pin = pin;
  this->timer = timer;
  this->timer.pseudoConstructor(periodStart, periodStop);
  this->delegateFunction = (*delegateFunction);
  //this->thisButton = this;
  pinMode(pin, INPUT_PULLUP);
}

ButtonARM::ButtonARM(int pin,
                     Timer timer,
                     unsigned long periodStart,
                     unsigned long periodStop,
                     void (*delegateFunction)()) 
          : Button(pin,
                   timer,
                   periodStart,
                   periodStop,
                   delegateFunction) {
  attachInterrupt(
    digitalPinToInterrupt(pin),
    interruptFunction,
    CHANGE);
}

ButtonAVR::ButtonAVR(int pin,
                     Timer timer,
                     unsigned long periodStart,
                     unsigned long periodStop,
                     void (*delegateFunction)())
          : Button(pin,
                   timer,
                   periodStart,
                   periodStop,
                   delegateFunction) {
  // Empty.
}

//Timer::Timer(const unsigned long period) {
//}

void Timer::pseudoConstructor(unsigned long periodStart,
                              unsigned long periodStop) {
  this->periodStart = periodStart;
  this->periodStop = periodStop;
}

////////////////////////////////////////////////////////////////////////
// Print Statements ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int Button::printDefinitions() {
  //Serial.print("pin=");
  //Serial.print(this->pin);
  int result = 0;
  if (this->stateHot) {
    Serial.print(this->stateHot);
    result = 1;
  }
  return result;
}

////////////////////////////////////////////////////////////////////////
// Interrupts //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void ButtonARM::interruptFunction() {
  //this->updateHotState();
}

////////////////////////////////////////////////////////////////////////
// Updates /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void ThumbStick::updateHotState() {
  stateHotHorizontal = analogRead(pinHorizontal);
  stateHotVertical = analogRead(pinVertical);
}

int Button::updateHotState() {
  stateHot = !digitalRead(pin);
  return stateHot;
}

int Button::debounceByBlockPress() {
  int result = 0;
  if (isBlocked == 0) {
    isBlocked = 1;
    result = 1;
  }
  return result;
}

int Button::debounceByBlockRelease() {
  int result = 0;
  if (isBlocked == 1) {
    isBlocked = 0;
    result = 1;
  }
  return result;
}

int Button::debounceByPositionPress() {
  int result = 0;
  statePositionPrevious = statePositionCurrent;
  statePositionCurrent = stateDebouncedByTime;
  if (statePositionCurrent != statePositionPrevious) {
    if (statePositionCurrent && !statePositionPrevious) {
      result = 1;
    } else {
      // Empty.
    }
  }
  return result;
}

int Button::debounceByPositionRelease() {
  int result = 0;
  statePositionPrevious = statePositionCurrent;
  statePositionCurrent = stateDebouncedByTime;
  if (statePositionCurrent != statePositionPrevious) {
    // Empty.
  } else {
    result = 1;
  }
  return result;
}

int Button::debounceByTimePress() {
  int result = 0;
  if (stateHot) {
    result = timer.updateStart(true, &stateDebouncedByTime);
    if (result == 1) {
      stateDebouncedByTime = true;
    }
  }
  return result;
}

int Button::debounceByTimeRelease() {
  int result = 0;
  if (!stateHot) {
    result = timer.updateStop(true, &stateDebouncedByTime);
    if (result == 1) {
      stateDebouncedByTime = true;
    }
  }
  return result;
}

int Timer::updateStart(bool isRunning, int *stateDebouncedByTime) {
  int result = -1;
  //if (!isRunning) {
  //  return -1;
  //}
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0) {
    delta = 0;
    result = -1;
  }
  count += delta;
  //Serial.println(count);
  if (count >= periodStart) {
    reset();
    result = 1;
  } else {
    stateDebouncedByTime = 0;
  }
  return result;
}

int Timer::updateStop(bool isRunning, int *stateDebouncedByTime) {
  int result = -1;
  //if (!isRunning) {
  //  return -1;
  //}
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0) {
    delta = 0;
    result = -1;
  }
  count += delta;
  //Serial.println(count);
  if (count >= periodStop) {
    reset();
    result = 1;
  } else {
    stateDebouncedByTime = 0;
  }
  return result;
}

////////////////////////////////////////////////////////////////////////
// Targeting ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void Button::startTargeting() {
  isTarget = true;
}

void Button::stopTargeting() {
  isTarget = false;
}

int Button::debounceByTargetPress() {
  int result = 0;
  if (isTarget) {
    result = 1;
  }
  return result;
}

int Button::debounceByTargetRelease() {
  int result = 0;
  if (isTarget) {
    result = 1;
  }
  isTarget = false;
  return result;
}

////////////////////////////////////////////////////////////////////////
// Resets //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void Button::reset() {
  statePositionPrevious = 0;
  statePositionCurrent = 0;
}

void Timer::reset() {
  count = 0L;
}

////////////////////////////////////////////////////////////////////////
// State Machine ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void State::startRunning() {
  state = stateRunning;
}

void State::startWaiting() {
  state = stateWaiting;
}

int State::isRunning() {
  int result = 0;
  if (state == stateRunning) {
    result = true;
  }
  return result;
}

int State::isWaiting() {
  int result = 0;
  if (state == stateWaiting) {
    result = true;
  }
  return result;
}
