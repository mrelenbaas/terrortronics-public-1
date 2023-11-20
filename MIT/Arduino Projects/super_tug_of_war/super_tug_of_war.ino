// https://docs.arduino.cc/built-in-examples/digital/Debounce

#include <MemoryFree.h>;

#include "super_tug_of_war.h"

/**
   - Instantiate local variables.
   - Setup the Serial library.
   - Setup timers.
   - Setup taps.
   - Setup button debounces.
   - Setup sounds.
   - Setup lights.
   - Setup buttons.
   - Setup switches.
   - Setup motor.
   - Setup Super Tug-of-War pins.
*/
void setup() {
  // Instantiate local variables.
  int index = 0;
  // Setup the //Serial library.
  Serial.begin(BAUD_RATE);
  // Setup timers.
  timers[toggle].timeout = 100L;
  timers[oneSecond].timeout = 1000L;
  timers[fiveSecond].timeout = 5000L;
  timers[tenSecond].timeout = 10000L;
  timers[sequence].timeout = sequenceTimeout[0][0];
  timers[tieSpecial].timeout = 4000L;
  timers[stopSpecial].timeout = 1.515L;
  timers[readySpecial].timeout = 2500L;
  timers[winnerSpecial].timeout = 4000L;
  // Setup taps.
  for (int i = 0; i < TAPS_MAX; ++i) {
    player1Taps[i] = 0;
  }
  // Setup button debounces.
  for (unsigned int i = 0; i < BUTTON_SIZE; ++i) {
    buttonDebounces[i] = 0L;
  }
  // Setup sounds.
  for (int i = FIRST_SOUND_PIN; i < LAST_SOUND_PIN + 1; i++) {
    sounds[index].pin = i;
    pinMode(sounds[index].pin, OUTPUT);
    index++;
  }
  index = 0;
  // Setup lights.
  for (int i = FIRST_LIGHT_PIN; i < LAST_LIGHT_PIN + 1; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  // Setup buttons.
  for (int i = FIRST_BUTTON_PIN; i < LAST_BUTTON_PIN + 1; i++) {
    if (i == SKIPPED_BUTTON_1 || i == SKIPPED_BUTTON_2) {
      continue;
    }
    buttons[index].pin = i;
    pinMode(buttons[index].pin, INPUT_PULLUP);
    ++index;
  }
  // Setup switches.
  index = 0;
  for (int i = FIRST_SWITCH_PIN; i < LAST_SWITCH_PIN + 1; i++) {
    if (i == SKIPPED_SWITCH_1 || i == SKIPPED_SWITCH_2) {
      continue;
    }
    switches[index].pin = i;
    pinMode(switches[index].pin, INPUT_PULLUP);
    ++index;
  }
  // Setup motor.
  motor.left = pinMotorLeft;
  motor.right = pinMotorRight;
  pinMode(motor.left, OUTPUT);
  pinMode(motor.right, OUTPUT);
  if (random(0, 1)) {
    motor.moveLeft();
  } else {
    motor.moveRight();
  }
  // Setup Super Tug-of-War pins.
  pinMode(pinButtonTouch, INPUT_PULLUP);
  pinMode(pinLightError, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinReset, OUTPUT);
  digitalWrite(pinReset, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);
  pinMode(pinLightDebug, OUTPUT);
}

/**
   - Update timers.
   - Update input.
   - Update tug sequences and segments.
   - If not-isSequenceOn state, then update, debounce, and error
   correct switches.
   - Check timers.
*/
void loop() {
  // Update timers.
  updateTimers();
  // Update input.
  updateButtons();
  // Update tug sequences and segments.
  if (timers[fiveSecond].total > SEQUENCE_TIMEOUT && isSequenceOn) {
    stopTugSequence();
  } else if (timers[sequence].total >= timers[sequence].timeout && isSequenceOn) {
    stopTugSegment();
  }
  // If not-isSequenceIn state, then update, debounce, and error
  // correct switches.
  if (!isSequenceOn) {
    updateSwitches();
    debounceSwitchesByTime();
    if (errorCheckPluralInput()) {
      return;
    }
    debounceSwitchesByPosition();
  }
  // Check timers.
  if (timers[sound].total >= SOUND_TIMEOUT && soundCurrent != -1) {
    stopSoundTimer();
  }
  if (timers[toggle].total >= TOGGLE_TIMEOUT) {
    stopToggleTimer();
  }
  if (timers[oneSecond].total >= ONE_SECOND_TIMEOUT) {
    stopOneSecondTimer();
  }
  // DOXYGEN
  if (timers[fiveSecond].total >= timers[fiveSecond].timeout) {
    stopFiveSecondTimer();
  }
  if (timers[winnerSpecial].total >= WINNER_TIMEOUT) {
    stopWinnerTimer();
  }
  if (timers[tenSecond].total >= TEN_SECOND_TIMER) {
    stopTenSecondTimer();
  }
  if (timers[readySpecial].total >= READY_TIMEOUT) {
    stopReadyTimer();
  }
  if (timers[stopSpecial].total >= STOP_SPECIAL_TIMEOUT) {
    stopStopTimer();
  } else if (isStopTimerOn && timers[stopSpecial].total > STOP_TIMEOUT) {
    routeResults2();
    routeResults();
    digitalWrite(pinLightStop, LOW);
  } else if (isStopTimerOn && timers[stopSpecial].total < STOP_SPECIAL_TIMEOUT) {
    motor.moveStop();
  }
  if (errorCheckContactSwitches()) {
    //  return;
  }
  // Route Buttons;
  routeButtons();
}

////////////////////////////////////////////////////////////////////////
// Private Functions ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   - Update current/previous switches if a normal number (0 or 1) of
   switches are pressed.
*/
void debounceSwitchesByPosition() {
  // Update current/previous switches if a normal number (0 or 1) of
  // switches are pressed.
  if (singleSwitch != currentSwitch) {
    previousSwitch = currentSwitch;
    currentSwitch = singleSwitch;
  }
}

/**
   - Loop through each switch, and debounce it.
*/
void debounceSwitchesByTime() {
  for (int i = 0; i < SWITCH_SIZE; i++) {
    debounceSwitchByTime(i);
  }
}
/**
   @param i The switch index to debounce.

   - If switch is LOW and blocked, then update debounce.
   - If switch is HIGH and not-blocked, then reset block and debounce.
*/
void debounceSwitchByTime(int i) {
  if (hotSwitches[i] == LOW && !switchBlocks[i]) {
    switchDebounces[i] += delta;
    if (switchDebounces[i] > DEBOUNCE_TIME) {
      switchBlocks[i] = true;
    }
  } else if (hotSwitches[i] && switchBlocks[i]) {
    switchBlocks[i] = false;
    switchDebounces[i] = 0;
  }
}

/**
   - Count the number of switch input occuring.
   - Block input if plural inputs occuring.
*/
bool errorCheckPluralInput() {
  // Count the number of switch inputs occuring.
  countSwitch = 0;
  for (unsigned int i = 0; i < SWITCH_SIZE; i++) {
    if (hotSwitches[i] == LOW) {
      singleSwitch = i;
      countSwitch++;
    }
  }
  // Block input if plural switch inputs occuring.
  if (countSwitch > 1) {
    countSwitch2 = 0;
    for (unsigned int i = 0; i < SWITCH_SIZE; i++) {
      if (hotSwitches[i] == LOW) {
        Serial.print(millis());
        Serial.print(": E: Plural input, ");
        Serial.print(countSwitch2);
        Serial.print(", ");
        Serial.println(i);
        //singleSwitch = i;
        countSwitch2++;
      }
    }
    return true;
  }
  return false;
}

/**
   - Set all elements of targets to FALSE;
   - Set the element of targets[index] to TRUE.
*/
void setTarget(int index) {
  ////Serial.print("setTarget(");
  ////Serial.print(index);
  //////Serial.print(millis()); Serial.print(": "); Serial.println(")");
  isTenSecondTimerOn = true;
  timers[tenSecond].total = 0L;
  // Set all elements of targs to FALSE.
  for (unsigned int i = 0; i < SWITCH_SIZE; ++i) {
    targets[i] = false;
  }
  // Set the element of targets[index] to TRUE.
  targets[index] = true;
}

/**
   - Return if isOneSecondTimerOn state is inactive.
   - Reset state and timer.
   - Set state and timer to Two state, Three state, Tug state, or Stop
   state.
*/
void stopOneSecondTimer() {
  // Return if isOneSecondTimerOn state is inactive.
  if (!isOneSecondTimerOn) {
    return;
  }
  // Reset state and timer.
  isOneSecondTimerOn = false;
  timers[oneSecond].total = 0L;
  //
  if (isOneOn) {
    isOneOn = false;
    digitalWrite(pinLightOne, LOW);
    digitalWrite(pinLightTwo, HIGH);
    playSound(two);
    isTwoOn = true;
    isOneSecondTimerOn = true;
  } else if (isTwoOn) {
    isTwoOn = false;
    digitalWrite(pinLightTwo, LOW);
    digitalWrite(pinLightThree, HIGH);
    playSound(three);
    isThreeOn = true;
    isOneSecondTimerOn = true;
  } else if (isThreeOn) {
    isThreeOn = false;
    digitalWrite(pinLightThree, LOW);
    digitalWrite(pinLightTug, HIGH);
    playSound(tug);
    isTugOn = true;
    isSequenceOn = true;
    timers[fiveSecond].total = 0L;
    isFiveSecondTimerOn = true;
    player1Index = 0;
    player2Index = 0;
    player1Score = 0;
    player2Score = 0;
    for (int i = 0; i < TAPS_MAX; i++) {
      player1Taps[i] = 0;
      player2Taps[i] = 0;
    }
  } else if (isStopOn) {
    digitalWrite(pinLightStop, LOW);
    isStopOn = false;
  }
}

/**
   - Return if isSoundTimerOn is off.
   - Reset sound timer.
*/
void stopSoundTimer() {
  // Return if isSoundTimerOn is off.
  if (!isSoundTimerOn) {
    return;
  }
  // Reset sound timer.
  isSoundTimerOn = false;
  timers[sound].total = 0L;
  digitalWrite(sounds[soundCurrent].pin, LOW);
  soundCurrent = -1;
}

/**
   - Reset timer if not blinking states are active.
   - Reset timer.
   - If blinking state is on and toggle is on, then turn on light. If
   blinking state is on and toggle state is off, the turn off light.
   - Toggle isToggleOn.
*/
void stopToggleTimer() {
  // Reset timer if no blinking states are active.
  if (!isReadyBlinking
      && !isWinnerLeftBlinking
      && !isWinnerRightBlinking
      && !isChampionLeftBlinking
      && !isChampionRightBlinking
      && !isSuddenDeathLeftBlinking
      && !isSuddenDeathRightBlinking) {
    timers[toggle].total = 0L;
    return;
  }
  // Reset timer.
  timers[toggle].total = 0L;
  // If blinking state is on and toggle is on, then turn on light. If
  // blinking state is on and toggle state is off, the turn off light.
  if (isReadyBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightReady, HIGH);
    } else {
      digitalWrite(pinLightReady, LOW);
    }
  } else if (isWinnerLeftBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightWinnerLeft, HIGH);
    } else {
      digitalWrite(pinLightWinnerLeft, LOW);
    }
  } else if (isWinnerRightBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightWinnerRight, HIGH);
    } else {
      digitalWrite(pinLightWinnerRight, LOW);
    }
  } else if (isChampionLeftBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightChampionLeft, HIGH);
    } else {
      digitalWrite(pinLightChampionLeft, LOW);
    }

  } else if (isChampionRightBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightChampionRight, HIGH);
    } else {
      digitalWrite(pinLightChampionRight, LOW);
    }
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    if (isToggleOn) {
      digitalWrite(pinLightSuddenDeathLeft, HIGH);
      digitalWrite(pinLightSuddenDeathRight, HIGH);
    } else {
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
    }
  }
  // Toggle isToggleOn.
  if (isToggleOn) {
    isToggleOn = false;
  } else {
    isToggleOn = true;
  }
}

/**
   - Reset the sequence timer.
   - Setup a new segment.
   - Move motor left or right.
   - Update the sequenceI and sequenceJ indexes.
*/
void stopTugSegment() {
  // Reset the sequence timer.
  timers[sequence].total = 0L;
  // Setup new segment.
  timers[sequence].timeout = sequenceTimeout[0][sequenceI];
  isSequenceLeft = sequenceIsLeft[sequenceJ][sequenceI];
  // Move motor left or right.
  if (isSequenceLeft) {
    motor.moveLeft();
  } else {
    motor.moveRight();
  }
  // Update the sequenceI and sequenceJ indexes.
  ++sequenceI;
  if (sequenceI >= SEQUENCE_I_MAX) {
    sequenceI = 0;
    ++sequenceJ;
    if (sequenceJ >= SEQUENCE_J_MAX) {
      sequenceJ = 0;
    }
  }
}

/**
   - Stop the motor.
   - Reset sequence variables.
*/
void stopTugSequence() {
  // Stop the motor.
  motor.moveStop();
  // Reset sequence variables.
  isSequenceOn = false;
  timers[sequence].total = 0L;
}

/**
   Perform digitalRead(int) calls, and read the results into the hotSwitches.
*/
void updateSwitches() {
  hotSwitches[leftMax] = digitalRead(pinSwitchLeftMax);
  hotSwitches[left3] = digitalRead(pinSwitchLeft3);
  hotSwitches[left1] = digitalRead(pinSwitchLeft1);
  hotSwitches[center] = digitalRead(pinSwitchCenter);
  hotSwitches[right1] = digitalRead(pinSwitchRight1);
  hotSwitches[right3] = digitalRead(pinSwitchRight3);
  hotSwitches[rightMax] = digitalRead(pinSwitchRightMax);
}

/**
   - Update previous, current, and delta variables.
   - Error handle millis() clock rollover by ignoring frame where delta
   is a negative number.
   - Error handle millis() clock rollover by ignorimg frame where
   current is less than previous.
   - Update debug timer (seperately from the other timers).
   - Update normal timers (if their associated state is active).
   - Update sequence and toggle timers regardless of state.
*/
void updateTimers() {
  // Update previous, current, and delta variables.
  previous = current;
  current = millis();
  delta = current - previous;
  // Error handle millis() clock rollover by ignoring frame where delta
  // is a negative number.
  if (delta < 0L) {
    return;
  }
  // Error handle millis() clock rollover by ignorimg frame where
  // current is less than previous.
  if (current < previous) {
    return;
  }
  // Update debug timer (seperately from the other timers).
  debugTimer += delta;
  if (debugTimer >= DEBUG_TIMEOUT) {
    Serial.print(millis()); Serial.print(": "); Serial.println(freeMemory());
    debugTimer = 0L;
    digitalWrite(pinLightDebug, !digitalRead(pinLightDebug));
  }
  // Update normal timers (if their associated state is active).
  if (isSoundTimerOn) {
    timers[sound].total += delta;
  }
  if (isOneSecondTimerOn) {
    timers[oneSecond].total += delta;
  }
  if (isFiveSecondTimerOn) {
    timers[fiveSecond].total += delta;
  }
  if (isTenSecondTimerOn) {
    timers[tenSecond].total += delta;
  }
  if (isStopTimerOn) {
    timers[stopSpecial].total += delta;
  }
  if (isReadyTimerOn) {
    timers[readySpecial].total += delta;
  }
  if (isWinnerTimerOn) {
    timers[winnerSpecial].total += delta;
  }
  // Update sequence and toggle timers regardless of state.
  timers[sequence].total += delta;
  timers[toggle].total += delta;
}

////////////////////////////////////////////////////////////////////////
// Undocumented Functions //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction() {
  Serial.print(millis()); Serial.print(": "); Serial.println("reset()");
}

void startFunction() {
  Serial.print("start(): ");
  Serial.print(millis()); Serial.print(": "); Serial.println(OUTGOING_START);
}

bool errorCheckContactSwitches() {
  if (hotSwitches[leftMax] == LOW) {
    if (!emergencyLeft) {
      emergencyLeft = true;
      //return false;
    } else if (emergencyLeft && !emergencyLeft2) {
      emergencyLeft2 = true;
    } else {
      emergencyLeft = false;
      emergencyLeft2 = false;
      Serial.println("E: emergency switches (Left)");
      //motor.moveStop();
      //motor.moveRight();
      //ditigalWrite(resetPin, LOW);
      //delay(50);
      return true;
    }
  } else {
    emergencyLeft = false;
    emergencyLeft2 = false;
  }
  if (hotSwitches[rightMax] == LOW) {
    if (!emergencyRight) {
      emergencyRight = true;
      //return false;
    } else if (emergencyRight && !emergencyRight2) {
      emergencyRight2 = true;
    } else {
      emergencyRight = false;
      emergencyRight2 = false;
      Serial.println("E: emergency switches (Right)");
      //motor.moveStop();
      //motor.moveLeft();
      //digitalWrite(resetPin, LOW);
      //delay(50);
      return true;
    }
  } else {
    emergencyRight = false;
    emergencyRight2 = false;
  }
  return false;
}

void routeResults() {
  if (player1Score == player2Score && player1Index > 0 && player2Index > 0) {
    if (random(0, 1)) {
      if (random(0, 1)) {
        player1Score = 1;
        player2Score = 0;
      } else {
        player1Score = 0;
        player2Score = 1;
      }
    }
  }
  if (player1Score > player2Score) {
    if (preRouteRoundCurrent > 4) {
      //digitalWrite(pinLightWinnerLeft, HIGH);
      //isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      motor.moveLeft();
      setTarget(1);
    } else if (preRouteRoundCurrent == 4) {
      if (currentSwitch == 2) {
        //digitalWrite(pinLightWinnerLeft, HIGH);
        //isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        motor.moveLeft();
        setTarget(1);
      } else if (currentSwitch == 3) {
        //isSuddenDeathLeftBlinking = true;
        //isSuddenDeathRightBlinking = true;
        setTarget(3);
      } else if (currentSwitch == 4) {
        //isSuddenDeathLeftBlinking = true;
        //isSuddenDeathRightBlinking = true;
        motor.moveLeft();
        setTarget(3);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 4) {
        setTarget(3);
      } else if (currentSwitch == 3) {
        setTarget(2);
      } else if (currentSwitch == 2) {
        //digitalWrite(pinLightWinnerLeft, HIGH);
        //isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        setTarget(1);
      }
      motor.moveLeft();
    }
  } else if (player1Score < player2Score) {
    if (preRouteRoundCurrent > 4) {
      //digitalWrite(pinLightWinnerRight, HIGH);
      //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 4) {
      if (currentSwitch == 2) {
        //isSuddenDeathLeftBlinking = true;
        //isSuddenDeathRightBlinking = true;
        motor.moveRight();
        setTarget(3);
      } else if (currentSwitch == 3) {
        //isSuddenDeathLeftBlinking = true;
        //isSuddenDeathRightBlinking = true;
        setTarget(3);
      } else if (currentSwitch == 4) {
        //digitalWrite(pinLightWinnerRight, HIGH);
        //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        motor.moveRight();
        setTarget(5);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        setTarget(3);
      } else if (currentSwitch == 3) {
        setTarget(4);
      } else if (currentSwitch == 4) {
        //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        //digitalWrite(pinLightWinnerRight, HIGH);
        setTarget(5);
      }
      motor.moveRight();
    }
  } else {
    if (preRouteRoundCurrent > 4) {
      //digitalWrite(pinLightWinnerRight, HIGH);
      //isChampionRightBlinking = true;
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 4) {
      //isSuddenDeathLeftBlinking = true;
      //isSuddenDeathRightBlinking = true;
      if (currentSwitch == 2) {
        motor.moveRight();
        setTarget(3);
      } else if (currentSwitch == 3) {
        setTarget(3);
      } else if (currentSwitch == 4) {
        motor.moveLeft();
        setTarget(3);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        setTarget(2);
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
      } else if (currentSwitch == 3) {
        setTarget(3);
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
      } else if (currentSwitch == 4) {
        setTarget(4);
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
      }
    }
    timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
  }
}

void routeResults2() {
  if (player1Score > player2Score) {
    if (preRouteRoundCurrent > 4) {
      //isToggleOn = true;
      //digitalWrite(pinLightChampionLeft, HIGH);
      timers[toggle].total = 0L;
      digitalWrite(pinLightWinnerLeft, HIGH);
      isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //isGameOver = true;
      motor.moveLeft();
      playSound(catThird);
    } else if (preRouteRoundCurrent == 4) {
      if (preRouteSwitch == 2) {
        //isToggleOn = true;
        //digitalWrite(pinLightChampionLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightWinnerLeft, HIGH);
        isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        //motor.moveLeft();
        playSound(catThird);
      } else if (preRouteSwitch == 3) {
        //isToggleOn = true;
        //digitalWrite(pinLightSuddenDeathLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        //isToggleOn = true;
        //digitalWrite(pinLightSuddenDeathLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        //motor.moveLeft();
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (preRouteSwitch == 4) {
        //isToggleOn = true;
        //digitalWrite(pinLightWinnerLeft, HIGH);
        timers[toggle].total = 0L;
        isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(catFirst);
      } else if (preRouteSwitch == 3) {
        //isToggleOn = true;
        //digitalWrite(pinLightWinnerLeft, HIGH);
        timers[toggle].total = 0L;
        isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(catFirst);
      } else if (preRouteSwitch == 2) {
        //isToggleOn = true;
        //digitalWrite(pinLightChampionLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightWinnerLeft, HIGH);
        isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        playSound(catThird);
      }
      //motor.moveLeft();
    }
  } else if (player1Score < player2Score) {
    if (preRouteRoundCurrent > 4) {
      //isToggleOn = true;
      //digitalWrite(pinLightChampionRight, HIGH);
      timers[toggle].total = 0L;
      digitalWrite(pinLightWinnerRight, HIGH);
      isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //isGameOver = true;
      //motor.moveRight();
      playSound(dogThird);
    } else if (preRouteRoundCurrent == 4) {
      if (preRouteSwitch == 2) {
        //isToggleOn = true;
        //digitalWrite(pinLightSuddenDeathLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        //motor.moveRight();
      } else if (preRouteSwitch == 3) {
        //isToggleOn = true;
        //digitalWrite(pinLightSuddenDeathLeft, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        //isToggleOn = true;
        //digitalWrite(pinLightChampionRight, HIGH);
        timers[toggle].total = 0L;
        digitalWrite(pinLightWinnerRight, HIGH);
        isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        //motor.moveRight();
        playSound(dogThird);
      }
    } else {
      if (preRouteSwitch == 2) {
        //isToggleOn = true;
        //digitalWrite(pinLightWinnerRight, HIGH);
        timers[toggle].total = 0L;
        isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(dogFirst);
      } else if (preRouteSwitch == 3) {
        //isToggleOn = true;
        //digitalWrite(pinLightWinnerRight, HIGH);
        timers[toggle].total = 0L;
        isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(dogFirst);
      } else if (preRouteSwitch == 4) {
        //isToggleOn = true;
        //digitalWrite(pinLightChampionRight, HIGH);
        timers[toggle].total = 0L;
        isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        digitalWrite(pinLightWinnerRight, HIGH);
        playSound(dogThird);
      }
      //motor.moveRight();
    }
  } else {
    if (preRouteRoundCurrent > 4) {
      //isToggleOn = true;
      digitalWrite(pinLightWinnerRight, HIGH);
      timers[toggle].total = 0L;
      digitalWrite(pinLightChampionRight, HIGH);
      isChampionRightBlinking = true;
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      //isGameOver = true;
      //motor.moveRight();
      playSound(dogThird);
    } else if (preRouteRoundCurrent == 4) {
      //isToggleOn = true;
      timers[toggle].total = 0L;
      digitalWrite(pinLightSuddenDeathLeft, HIGH);
      digitalWrite(pinLightSuddenDeathRight, HIGH);
      isSuddenDeathLeftBlinking = true;
      isSuddenDeathRightBlinking = true;
      playSound(suddenDeath);
      if (preRouteSwitch == 2) {
        //motor.moveRight();
        playSound(suddenDeath);
      } else if (preRouteSwitch == 3) {
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        //motor.moveLeft();
        playSound(suddenDeath);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (preRouteSwitch == 2) {
        playSound(tie);
      } else if (preRouteSwitch == 3) {
        playSound(tie);
      } else if (preRouteSwitch == 4) {
        playSound(tie);
      }
    }
  }
}

void routeResults3() {
  if (player1Score > player2Score) {
    if (roundCurrent > 4) {
      digitalWrite(pinLightWinnerLeft, HIGH);
      isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      isGameOver = true;
      motor.moveLeft();
      playSound(catThird);
      setTarget(1);
    } else if (roundCurrent == 4) {
      if (currentSwitch == 2) {
        digitalWrite(pinLightWinnerLeft, HIGH);
        isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        motor.moveLeft();
        playSound(catThird);
        setTarget(1);
      } else if (currentSwitch == 3) {
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        setTarget(3);
      } else if (currentSwitch == 4) {
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        motor.moveLeft();
        setTarget(3);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 4) {
        isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(catFirst);
        setTarget(3);
      } else if (currentSwitch == 3) {
        isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(catFirst);
        setTarget(2);
      } else if (currentSwitch == 2) {
        digitalWrite(pinLightWinnerLeft, HIGH);
        isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        //////Serial.print(millis()); Serial.print(": "); Serial.println("YOU ARE HERE");
        playSound(catThird);
        //////Serial.print(millis()); Serial.print(": "); Serial.println("YOU ARE THERE");
        setTarget(1);
      }
      motor.moveLeft();
    }
  } else if (player1Score < player2Score) {
    if (roundCurrent > 4) {
      digitalWrite(pinLightWinnerRight, HIGH);
      isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      isGameOver = true;
      motor.moveRight();
      playSound(dogThird);
      setTarget(5);
    } else if (roundCurrent == 4) {
      if (currentSwitch == 2) {
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        motor.moveRight();
        setTarget(3);
      } else if (currentSwitch == 3) {
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        playSound(suddenDeath);
        setTarget(3);
      } else if (currentSwitch == 4) {
        digitalWrite(pinLightWinnerRight, HIGH);
        isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        motor.moveRight();
        playSound(dogThird);
        setTarget(5);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(dogFirst);
        setTarget(3);
      } else if (currentSwitch == 3) {
        isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        playSound(dogFirst);
        setTarget(4);
      } else if (currentSwitch == 4) {
        isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
        digitalWrite(pinLightWinnerRight, HIGH);
        playSound(dogThird);
        setTarget(5);
      }
      motor.moveRight();
    }
  } else {
    if (roundCurrent > 4) {
      digitalWrite(pinLightWinnerRight, HIGH);
      isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      isGameOver = true;
      motor.moveRight();
      playSound(dogThird);
      setTarget(5);
    } else if (roundCurrent == 4) {
      isSuddenDeathLeftBlinking = true;
      isSuddenDeathRightBlinking = true;
      playSound(suddenDeath);
      if (currentSwitch == 2) {
        motor.moveRight();
        playSound(suddenDeath);
        setTarget(3);
      } else if (currentSwitch == 3) {
        playSound(suddenDeath);
        setTarget(3);
      } else if (currentSwitch == 4) {
        motor.moveLeft();
        playSound(suddenDeath);
        setTarget(3);
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        setTarget(2);
        isTie = true;
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.print(millis()); Serial.print(": "); Serial.println("333");
      } else if (currentSwitch == 3) {
        setTarget(3);
        isTie = true; timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.print(millis()); Serial.print(": "); Serial.println("444");
      } else if (currentSwitch == 4) {
        setTarget(4);
        isTie = true; timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.print(millis()); Serial.print(": "); Serial.println("555");
      }
    }
    timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
  }
}

bool preRouteResults() {
  preRouteSwitch = currentSwitch;
  preRouteRoundCurrent = roundCurrent;
  bool result = false;
  if (player1Score > player2Score) {
    if (roundCurrent > 4) {
      result = true;
      isGameOver = true;
    } else if (roundCurrent == 4) {
      if (currentSwitch == 2) {
        result = true;
      } else if (currentSwitch == 3) {
        result = true;
      } else if (currentSwitch == 4) {
        result = true;
      }
    } else {
      if (currentSwitch == 4) {
      } else if (currentSwitch == 3) {
      } else if (currentSwitch == 2) {
        result = true;
      }
    }
  } else if (player1Score < player2Score) {
    if (roundCurrent > 4) {
      result = true;
      isGameOver = true;
    } else if (roundCurrent == 4) {
      if (currentSwitch == 2) {
        result = true;
      } else if (currentSwitch == 3) {
        result = true;
      } else if (currentSwitch == 4) {
        result = true;
      }
    } else {
      if (currentSwitch == 2) {
      } else if (currentSwitch == 3) {
      } else if (currentSwitch == 4) {
        result = true;
      }
    }
  } else {
    if (roundCurrent > 4) {
      result = true;
      isGameOver = true;
    } else if (roundCurrent == 4) {
      result = true;
      if (currentSwitch == 2) {
      } else if (currentSwitch == 3) {
      } else if (currentSwitch == 4) {
      }
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        result = true;
        isTie = true; timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 3) {
        result = true;
        isTie = true; timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 4) {
        result = true;
        isTie = true; timers[fiveSecond].timeout = 3500L;
      }
    }
  }
  ////Serial.print("result: ");
  //////Serial.print(millis()); Serial.print(": "); Serial.println(result);
  //return result; Uncomment this to turn the results code back on.
  return false;
}

void playSound(int index) {
  soundCurrent = index;
  digitalWrite(sounds[soundCurrent].pin, HIGH);
  timers[sound].total = 0L;
  isSoundTimerOn = true;
}

void calculateResults() {
  //Serial.print(millis());
  //Serial.print(": ");
  if (player1Index > 0) {
    for (int i = 0; i < player1Index - 1; i++) {
      //Serial.print(player1Taps[i]);
      if ((player1Taps[i] == 0) && (player1Taps[i + 1] == 1)) {
        player1Score++;
        //Serial.print("+");
      }
      //Serial.print(",");
    }
  }
  Serial.print("player1Score: ");
  Serial.println(player1Score);
  //Serial.println("");
  //Serial.print(millis());
  //Serial.print(": ");
  if (player2Index > 0) {
    for (int i = 0; i < player2Index - 1; i++) {
      //Serial.print(player2Taps[i]);
      if ((player2Taps[i] == 0) && (player2Taps[i + 1] == 1)) {
        player2Score++;
        //Serial.print("+");
      }
      //Serial.print(",");
    }
  }
  //Serial.println("");
  Serial.print("player2Score: ");
  Serial.println(player2Score);
}

void stopFiveSecondTimer() {
  if (!isFiveSecondTimerOn) {
    return;
  }
  isFiveSecondTimerOn = false;
  ////Serial.print("stopFiveSecondTimer() - ");
  ////Serial.print("timers[");
  ////Serial.print(fiveSecond);
  ////Serial.print("]: ");
  ////Serial.print(timers[fiveSecond].total);
  timers[fiveSecond].total = 0L;
  if (isTugOn) {
    //////Serial.print(millis()); Serial.print(": "); Serial.println(", isTugOn");
    digitalWrite(pinLightTug, LOW);
    isTugOn = false;
    calculateResults();
    preRouteResult = preRouteResults();
    if (preRouteResult) {
      routeResults3();
    } else {
      ////Serial.print("preRouteResult: ");
      //////Serial.print(millis()); Serial.print(": "); Serial.println(preRouteResult);
      playSound(stop);
      digitalWrite(pinLightStop, HIGH);
      isStopTimerOn = true;
      timers[stopSpecial].total = 0L;
      routeResults();
      isStopOn = true;
    }
    roundCurrent++;
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    //////Serial.print(millis()); Serial.print(": "); Serial.println(", isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking");
    timers[toggle].total -= 200L;
    isToggleOn = true;
    timers[oneSecond].total = 0L;
    isOneSecondTimerOn = true;
    timers[fiveSecond].total = 0L;
    //timers[fiveSecond].total -= 5000L;
    isFiveSecondTimerOn = true;
    isReadyBlinking = true;
    timers[fiveSecond].timeout = 2500L;
    playSound(ready);
    isSuddenDeathLeftBlinking = false;
    isSuddenDeathRightBlinking = false;
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (isReadyBlinking) {
    isReadyTimerOn = true;
    stopReadyTimer();
    timers[fiveSecond].timeout = 5000L;
  } else if (isTie) {
    timers[fiveSecond].total = 0L;
    timers[fiveSecond].timeout = 2500L;
    isFiveSecondTimerOn = true;
    isReadyBlinking = true;
    isReadyTimerOn = true;
    timers[readySpecial].total = 0L;
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
    isTie = false;
  }
}

void stopTenSecondTimer() {
  if (!isTenSecondTimerOn) {
    return;
  }
  isTenSecondTimerOn = false;
  timers[tenSecond].total = 0L;
  if (isChampionLeftBlinking || isChampionRightBlinking) {
    isReadyBlinking = false;
    isWinnerLeftBlinking = false;
    isWinnerRightBlinking = false;
    isChampionLeftBlinking = false;
    isChampionRightBlinking = false;
    isSuddenDeathLeftBlinking = false;
    isSuddenDeathRightBlinking = false;
    isCentering = true;
    isReset = false;
    digitalWrite(pinLightChampionLeft, LOW);
    digitalWrite(pinLightChampionRight, LOW);
    digitalWrite(pinLightWinnerLeft, LOW);
    digitalWrite(pinLightWinnerRight, LOW);
    digitalWrite(pinLightSuddenDeathLeft, LOW);
    digitalWrite(pinLightSuddenDeathRight, LOW);
    digitalWrite(pinLightReady, LOW);
    digitalWrite(pinLightOne, LOW);
    isOneOn = false;
    digitalWrite(pinLightTwo, LOW);
    isTwoOn = false;
    digitalWrite(pinLightThree, LOW);
    isThreeOn = false;
    digitalWrite(pinLightTug, LOW);
    isTugOn = false;
    digitalWrite(pinLightStop, LOW);
    isStopOn = false;
    roundCurrent = 0;
    isCentering = true;
    isReset = false;
    timers[toggle].total -= 200L;
    isToggleOn = true;
    timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
    timers[fiveSecond].total = 0L;
    //timers[fiveSecond].total -= 5000L;
    isFiveSecondTimerOn = true;
  }
}

void stopStopTimer() {
  if (!isStopTimerOn) {
    return;
  }
  //////Serial.print(millis()); Serial.print(": "); Serial.println("stopStopTimer() - ");
  //routeResults();
  isStopTimerOn = false;
  timers[stopSpecial].total = 0L;
  //routeResults2();
}

void stopReadyTimer() {
  if (!isReadyTimerOn) {
    return;
  }
  isReadyTimerOn = false;
  //////Serial.print(millis()); Serial.print(": "); Serial.println("stopReadyTimer() - ");
  timers[readySpecial].total = 0L;
  if (isReadyBlinking) {
    //////Serial.print(millis()); Serial.print(": "); Serial.println(", isReadyBlinking");
    isReadyBlinking = false;
    digitalWrite(pinLightReady, LOW);
    digitalWrite(pinLightOne, HIGH);
    playSound(one);
    isOneOn = true;
    timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
  }
}

void updateButtons() {
  hotButtons[start] = digitalRead(pinButtonStart);
  hotButtons[player1Left] = digitalRead(pinButtonPlayer1Left);
  hotButtons[player1Right] = digitalRead(pinButtonPlayer1Right);
  hotButtons[player2Left] = digitalRead(pinButtonPlayer2Left);
  hotButtons[player2Right] = digitalRead(pinButtonPlayer2Right);
}

void routeButtons() {
  if (isReset) {
    //Serial.print(millis()); Serial.print(": "); Serial.println("0");
    if (hotButtons[start] == LOW && !buttonBlocks[start]) {
      buttonDebounces[start] += delta;
      if (buttonDebounces[start] > 10L) {
        Serial.print(millis()); Serial.print(": "); Serial.println("start");
        timers[toggle].total = 0L;
        isToggleOn = true;
        timers[oneSecond].total = 0L;
        isOneSecondTimerOn = true;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        isReadyBlinking = true;
        timers[fiveSecond].timeout = 2500L;
        isReadyTimerOn = true;
        timers[readySpecial].total = 0L;
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        playSound(ready);
        isReset = false;
        ////Serial.print(millis()); Serial.print(": "); Serial.println("$");
      }
    }
  } else if (isCentering) {
    //Serial.print(millis()); Serial.print(": "); Serial.println("2");
    if (hotSwitches[left3] == LOW) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isCentering, left3");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("isCentering 1");
      motor.moveRight();
    } else if (hotSwitches[right3] == LOW) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isCentering, right3");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("isCentering 5");
      motor.moveLeft();
    } else if (hotSwitches[center] == LOW) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isCentering, center");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("isCentering 3");
      motor.moveStop();
      isCentering = false;
      isReset = true;
      //////Serial.print(millis()); Serial.print(": "); Serial.println("########## NEW GAME ##########");
    }
  } else if (isTugOn) {
    //Serial.print(millis()); Serial.print(": "); Serial.println("6");
    if (hotButtons[player1Left] == LOW && !buttonBlocks[player1Left]) {
      buttonDebounces[player1Left] += delta;
      if (buttonDebounces[player1Left] > DEBOUNCE_TIME) {
        //Serial.print(millis()); Serial.print(": "); Serial.println("p1Left Down");
        buttonBlocks[player1Left] = true;
        player1Taps[player1Index] = 0;
        ////Serial.print("player1Taps[");
        ////Serial.print(player1Index);
        ////Serial.print("] (L): ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(player1Taps[player1Index]);
        ////Serial.print(", buttonDebounces[player1Left]: ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(buttonDebounces[player1Left]);
        player1Index++;
      }
    } else if (hotButtons[player1Left] == HIGH && buttonBlocks[player1Left]) {
      //Serial.print(millis()); Serial.print(": "); Serial.println("p1Left Up");
      buttonBlocks[player1Left] = false;
      buttonDebounces[player1Left] = 0;
    }

    if (hotButtons[player1Right] == LOW && !buttonBlocks[player1Right]) {
      buttonDebounces[player1Right] += delta;
      if (buttonDebounces[player1Right] > DEBOUNCE_TIME) {
        //Serial.print(millis()); Serial.print(": "); Serial.println("p1Right Down");
        buttonBlocks[player1Right] = true;
        player1Taps[player1Index] = 1;
        ////Serial.print("player1Taps[");
        ////Serial.print(player1Index);
        ////Serial.print("] (R): ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(player1Taps[player1Index]);
        ////Serial.print(", buttonDebounces[player1Index]:");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(buttonDebounces[player1Right]);
        player1Index++;
      }
    }
    else if (hotButtons[player1Right] == HIGH && buttonBlocks[player1Right]) {
      //Serial.print(millis()); Serial.print(": "); Serial.println("p1Right Up");
      buttonBlocks[player1Right] = false;
      buttonDebounces[player1Right] = 0;
    }


    if (hotButtons[player2Left] == LOW && !buttonBlocks[player2Left]) {
      buttonDebounces[player2Left] += delta;
      if (buttonDebounces[player2Left] > DEBOUNCE_TIME) {
        //Serial.print(millis()); Serial.print(": "); Serial.println("p2Left Down");
        buttonBlocks[player2Left] = true;
        player2Taps[player2Index] = 0;
        ////Serial.print("player2Taps[");
        ////Serial.print(player2Index);
        ////Serial.print("] (L): ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(player2Taps[player2Index]);
        ////Serial.print(", buttonDebounces[player2Left]: ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(buttonDebounces[player2Left]);
        player2Index++;
      }
    } else if (hotButtons[player2Left] && buttonBlocks[player2Left]) {
      //Serial.print(millis()); Serial.print(": "); Serial.println("p2Left Up");
      buttonBlocks[player2Left] = false;
      buttonDebounces[player2Left] = 0;
    }

    if (hotButtons[player2Right] == LOW && !buttonBlocks[player2Right]) {
      buttonDebounces[player2Right] += delta;
      if (buttonDebounces[player2Right] > DEBOUNCE_TIME) {
        //Serial.print(millis()); Serial.print(": "); Serial.println("p2Right Down");
        buttonBlocks[player2Right] = true;
        player2Taps[player2Index] = 1;
        ////Serial.print("player2Taps[");
        ////Serial.print(player2Index);
        ////Serial.print("] (R): ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(player2Taps[player2Index]);
        ////Serial.print(", buttonDebounces[player1Right]: ");
        ////Serial.print(millis()); Serial.print(": "); Serial.println(buttonDebounces[player2Right]);
        player2Index++;
      }
    } else if (hotButtons[player2Right] == HIGH && buttonBlocks[player2Right]) {
      //Serial.print(millis()); Serial.print(": "); Serial.println("p2Right Up");
      buttonBlocks[player2Right] = false;
      buttonDebounces[player2Right] = 0;
    }

  } else if (currentSwitch == previousSwitch) {
    Serial.print(millis()); Serial.print(": "); Serial.println("INPUT BLOCKED: same switch.");
  } else if ((isGameOver || isWinnerLeftBlinking || isWinnerRightBlinking || isChampionLeftBlinking || isChampionRightBlinking)
             && (!isSequenceOn)) {
    //Serial.print(millis()); Serial.print(": "); Serial.println("15");
    if (hotSwitches[left3] == LOW && targets[1]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isGameOver, left3");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("REACHED TARGET 1");
      motor.moveStop();
      targets[1] = false;
      //isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //digitalWrite(pinLightWinnerLeft, LOW);
      isGameOver = false;
      timers[tenSecond].total = 0L;
    } else if (hotSwitches[left1] == LOW && targets[2]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isGameOver, left1");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("REACHED TARGET 2");
      motor.moveStop();
      targets[2] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[center] == LOW && targets[3]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isGameOver, center");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("REACHED TARGET 3");
      motor.moveStop();
      targets[3] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[right1] == LOW && targets[4]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isGameOver, right1");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("REACHED TARGET 4");
      motor.moveStop();
      targets[4] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[right3] == LOW && targets[5]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isGameOver, right3");
      //////Serial.print(millis()); Serial.print(": "); Serial.println("REACHED TARGET 5");
      motor.moveStop();
      targets[5] = false;
      //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //digitalWrite(pinLightWinnerLeft, LOW);
      isGameOver = false;
      timers[tenSecond].total = 0L;
    }
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    if (hotSwitches[center] == LOW && targets[3]) {
      Serial.print(millis()); Serial.print(": "); Serial.println("isSuddenDeath, center");
      motor.moveStop();
      targets[3] = false;
      //digitalWrite(pinLightSuddenDeathLeft, LOW);
      //digitalWrite(pinLightSuddenDeathRight, LOW);
    }
  }
}

void stopWinnerTimer() {
  if (!isWinnerTimerOn) {
    return;
  }
  isWinnerTimerOn = false;
  ////Serial.print("stopWinnerTimer() - ");
  ////Serial.print("timers[winnerSpecial].total: ");
  //////Serial.print(millis()); Serial.print(": "); Serial.println(timers[winnerSpecial].total);
  timers[winnerSpecial].total = 0L;
  //if (isWinnerLeftBlinking || isWinnerRightBlinking) {
  ////////Serial.print(millis()); Serial.print(": "); Serial.println(", isWinnerLeftBlinking or isWinnerRightBlinking");
  timers[toggle].total -= 200L;
  isToggleOn = true;
  timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
  timers[fiveSecond].total = 0L;
  //timers[fiveSecond].total -= 5000L;
  isFiveSecondTimerOn = true;
  if (hotSwitches[left1] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[center] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[right1] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L;// digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[left3] == LOW) {
    isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
  } else if (hotSwitches[right3] == LOW) {
    isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
  }
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  //}
}
