#include "Arduino.h"
#include "common.h"

SoundAnalog::SoundAnalog(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

SoundDigital::SoundDigital(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

Water::Water(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

ThumbStick::ThumbStick(int pinHorizontal, int pinVertical) {
  this->pinHorizontal = pinHorizontal;
  this->pinVertical = pinVertical;
  pinMode(pinHorizontal, INPUT);
  pinMode(pinVertical, INPUT);
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

Button::Button(int pin,
               Timer timer,
               unsigned long periodStart,
               unsigned long periodStop,
               void (*delegateFunctionPress)(),
               void (*delegateFunctionRelease)()) {
  this->pin = pin;
  this->timer = timer;
  this->timer.pseudoConstructor(periodStart, periodStop);
  this->delegateFunctionPress = (*delegateFunctionPress);
  this->delegateFunctionRelease = (*delegateFunctionRelease);
  pinMode(pin, INPUT_PULLUP);
}

ButtonARM::ButtonARM(int pin,
                     Timer timer,
                     unsigned long periodStart,
                     unsigned long periodStop,
                     void (*delegateFunctionPress)(),
                     void (*delegateFunctionRelease)()) 
          : Button(pin,
                   timer,
                   periodStart,
                   periodStop,
                   delegateFunctionPress,
                   delegateFunctionRelease) {
  attachInterrupt(
    digitalPinToInterrupt(pin),
    interruptFunction,
    CHANGE);
}

ButtonAVR::ButtonAVR(int pin,
                     Timer timer,
                     unsigned long periodStart,
                     unsigned long periodStop,
                     void (*delegateFunctionPress)(),
                     void (*delegateFunctionRelease)())
          : Button(pin,
                   timer,
                   periodStart,
                   periodStop,
                   delegateFunctionPress,
                   delegateFunctionRelease) {
  // Empty.
}

Proximity::Proximity(int pin,
                    Timer timer,
                    unsigned long periodStart,
                    unsigned long periodStop,
                    void (*delegateFunctionPress)(),
                    void (*delegateFunctionRelease)()) 
          : Button(pin,
                   timer,
                   periodStart,
                   periodStop,
                   delegateFunctionPress,
                   delegateFunctionRelease) {
  pinMode(pin, INPUT);
}

//Timer::Timer(const unsigned long period) {
//}

void Timer::pseudoConstructor(unsigned long periodStart,
                              unsigned long periodStop) {
  this->periodStart = periodStart;
  this->periodStop = periodStop;
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

Light::Light(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Light::turnOn() {
  digitalWrite(pin, HIGH);
}

void Light::turnOff() {
  digitalWrite(pin, LOW);
}

////////////////////////////////////////////////////////////////////////
// Print Statements ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int SoundDigital::printDefinitions() {
  int result = 0;
  if (this->stateHot) {
    Serial.print(this->stateHot);
    result = 1;
  }
  return result;
}

int SoundAnalog::printDefinitions() {
  int result = 0;
  if (this->stateHot) {
    Serial.print(this->stateHot);
    result = 1;
  }
  return result;
}

/*
int Proximity::printDefinitions() {
  int result = 0;
  if (this->stateHot) {
    Serial.print(this->stateHot);
    result = 1;
  }
  return result;
}
*/

int Water::printDefinitions() {
  int result = 0;
  if (this->stateHot) {
    Serial.print(this->stateHot);
    result = 1;
  }
  return result;
}

int ThumbStick::printDefinitions() {
  int result = 0;
  if (this->stateHotHorizontal) {
    Serial.print(this->stateHotHorizontal);
    if (this->stateHotVertical) {
      Serial.print(", ");
    }
    result = 1;
  }
  if (this->stateHotVertical) {
    if (!this->stateHotHorizontal) {
      Serial.print("0.0, ");
    }
    Serial.print(this->stateHotVertical);
    result = 1;
  }
  return result;
}

int Button::printDefinitions() {
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
  // Empty.
}

////////////////////////////////////////////////////////////////////////
// Updates /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void SoundDigital::updateHotState() {
  stateHot = digitalRead(pin);
}

void SoundAnalog::updateHotState() {
  stateHot = analogRead(pin);
}

void Water::updateHotState() {
  stateHot = analogRead(pin);
}

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
