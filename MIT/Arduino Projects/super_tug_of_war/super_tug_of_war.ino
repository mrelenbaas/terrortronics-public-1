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
  Serial.println("SETUP END");
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
  if (isDebug) {
    Serial.print(millis());
    Serial.print(",");
    Serial.print(digitalRead(35));
    Serial.print(",");
    Serial.print(digitalRead(37));
    Serial.print(",");
    Serial.print(digitalRead(38));
    Serial.print(",");
    Serial.print(digitalRead(39));
    Serial.print(",");
    Serial.print(digitalRead(41));
    Serial.print(",");
    Serial.print(digitalRead(42));
    Serial.print(",");
    Serial.print(digitalRead(43));
    Serial.print(",");
    Serial.print(digitalRead(45));
    Serial.print(",");
    Serial.print(digitalRead(46));
    Serial.print(",");
    Serial.print(digitalRead(47));
    Serial.print(",");
    Serial.print(digitalRead(48));
    Serial.print(",");
    Serial.print(digitalRead(49));
    Serial.print(",");
    Serial.println(digitalRead(50));
    //Serial.print(",");
    return;
  }
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
    // Print tracers.
    Serial.print(millis());
    Serial.print(": debounced switch by position: ");
    Serial.print(previousSwitch);
    Serial.print(" to ");
    Serial.println(currentSwitch);
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
    if (switchDebounces[i] > DEBOUNCE_TIME_MICRO_SWITCHES) {
      // Print tracers.
      Serial.print(millis());
      Serial.print(": debounced switch by time:  ");
      Serial.println(i);
      switchBlocks[i] = true;
      debouncedSwitches[i] = LOW;
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
    if (debouncedSwitches[i] == LOW) {
      singleSwitch = i;
      countSwitch++;
    }
  }
  // Block input if plural switch inputs occuring.
  if (countSwitch > 1) {
    countSwitch2 = 0;
    for (unsigned int i = 0; i < SWITCH_SIZE; i++) {
      if (debouncedSwitches[i] == LOW) {
        Serial.print(millis());
        Serial.print(": ERROR: Plural input, ");
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

void resetFunction() {
  // Print tracer.
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
}

void routeResults2() {
  // Route player 1 wins, player 2 wins, and tie.
  if (player1Score > player2Score) {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionLeftBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightWinnerLeft, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set sound.
      playSound(catThird);
    } else if (preRouteRoundCurrent == 5) {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isChampionLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightWinnerLeft, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(catThird);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
      }
      // Reset five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 4) {
        // Set next state.
        isWinnerTimerOn = true;
        isWinnerLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(catFirst);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isWinnerTimerOn = true;
        isWinnerLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(catFirst);
      } else if (preRouteSwitch == 2) {
        // Set next state.
        isChampionLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightWinnerLeft, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(catThird);
      }
    }
  } else if (player1Score < player2Score) {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightWinnerRight, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set sound.
      playSound(dogThird);
    } else if (preRouteRoundCurrent == 5) {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 3) {
        timers[toggle].total = 0L;
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isChampionRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightWinnerRight, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(dogThird);
      }
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isWinnerRightBlinking = true;
        isWinnerTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(dogFirst);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isWinnerRightBlinking = true;
        isWinnerTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(dogFirst);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isChampionRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        digitalWrite(pinLightWinnerRight, HIGH);
        // Set sound.
        playSound(dogThird);
      }
    }
  } else {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightWinnerRight, HIGH);
      digitalWrite(pinLightChampionRight, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set sound.
      playSound(dogThird);
    } else if (preRouteRoundCurrent == 5) {
      // Set next state.
      isSuddenDeathLeftBlinking = true;
      isSuddenDeathRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightSuddenDeathLeft, HIGH);
      digitalWrite(pinLightSuddenDeathRight, HIGH);
      // Set sound.
      playSound(suddenDeath);
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 3) {
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 4) {
        // Set sound.
        playSound(suddenDeath);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
      }
    }
  }
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
   - Set next state.
   - Set timers.
   - Set lights.
   - Set sound.
*/
void startStop() {
  // Set next state.
  isStopTimerOn = true;
  isStopOn = true;
  routeResults();
  // Set timers.
  timers[stopSpecial].total = 0L;
  // Set lights.
  digitalWrite(pinLightStop, HIGH);
  // Set sound.
  playSound(stop);
}

/**
   - Return if isFiveSecondTimerOn is FALSE.
   - Reset state.
   - Route isTugOn, isSuddenDeathLeft/RightBlinking, isReadyBlinking, and isTie.
*/
void stopFiveSecondTimer() {
  // Return if isFiveSecondTimerOn is FALSE.
  if (!isFiveSecondTimerOn) {
    return;
  }
  // Reset state.
  isFiveSecondTimerOn = false;
  timers[fiveSecond].total = 0L;
  // Route isTugOn, isSuddenDeathLeft/RightBlinking, isReadyBlinking, and isTie.
  if (isTugOn) {
    stopIsTugOn();
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    stopSuddenDeathBlinking();
  } else if (isReadyBlinking) {
    stopReadyTimer();
  } else if (isTie) {
    stopTie();
  }
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
   - Return if isReadyTimerOn is FALSE.
   - Reset state.
   - Set next state.
   - Set timers.
   - Set lights.
   - Set sound.
*/
void stopReadyTimer() {
  // Return if isReadyTimerOn is FALSE.
  if (!isReadyTimerOn) {
    return;
  }
  // Reset state.
  isReadyTimerOn = false;
  isReadyBlinking = false;
  // Set next state.
  isOneOn = true;
  isOneSecondTimerOn = true;
  // Set timers.
  timers[readySpecial].total = 0L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].timeout = 5000L;
  // Set lights.
  digitalWrite(pinLightReady, LOW);
  digitalWrite(pinLightOne, HIGH);
  // Set sound.
  playSound(one);
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
   - Reset state.
   - Set lights.
   - Process results.
   - Route results.
   - Set next state.
*/
void stopIsTugOn() {
  // Reset state.
  isTugOn = false;
  // Set lights.
  digitalWrite(pinLightTug, LOW);
  // Process results.
  calculateResults();
  preRouteResult = preRouteResults();
  // Route results.
  if (preRouteResult) {
    routeResults3();
  } else {
    startStop();
  }
  // Set next state.
  roundCurrent++;
}

/**
   - Reset state.
   - Set next state.
   - Set timers.
   - Set sound.
*/
void stopSuddenDeathBlinking() {
  // Reset state.
  isSuddenDeathLeftBlinking = false;
  isSuddenDeathRightBlinking = false;
  // Set next state.
  isToggleOn = true;
  isOneSecondTimerOn = true;
  isFiveSecondTimerOn = true;
  isReadyBlinking = true;
  isReadyTimerOn = true;
  // Set timers.
  timers[toggle].total -= 200L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].timeout = 2500L;
  // Set sound.
  playSound(ready);
  // TODO: Remember to test this for a while before removing.
  //if (isChampionLeftBlinking || isChampionRightBlinking) {
  //  isReadyBlinking = false;
  //  digitalWrite(pinLightReady, LOW);
  //}
}

/**
   - Reset state.
   - Set next state.
   - Set timers.
   - Set sound.
*/
void stopTie() {
  // Reset state.
  isTie = false;
  // Set next state.
  isFiveSecondTimerOn = true;
  isReadyBlinking = true;
  isReadyTimerOn = true;
  // Set timers.
  timers[fiveSecond].timeout = 2500L;
  timers[readySpecial].total = 0L;
  // Set sound.
  playSound(ready);
  // TODO: Remember to test this before removing.
  //if (isChampionLeftBlinking || isChampionRightBlinking) {
  //  isReadyBlinking = false;
  //  digitalWrite(pinLightReady, LOW);
  //}
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
  for (int i = 0; i < SWITCH_SIZE; i++) {
    debouncedSwitches[i] = HIGH;
  }
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
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void calculateResults() {
  Serial.print(millis());
  Serial.print(": roundCurrent: ");
  Serial.println(roundCurrent);
  // Calculate player 1 score.
  if (player1Index > 0) {
    for (int i = 0; i < player1Index - 1; i++) {
      if ((player1Taps[i] == 0) && (player1Taps[i + 1] == 1)) {
        player1Score++;
      }
    }
  }
  // Print player 1 score.
  Serial.print(millis());
  Serial.print(": player1Score: ");
  Serial.println(player1Score);
  // Calculate player 2 score.
  if (player2Index > 0) {
    for (int i = 0; i < player2Index - 1; i++) {
      if ((player2Taps[i] == 0) && (player2Taps[i + 1] == 1)) {
        player2Score++;
      }
    }
  }
  // Print player 2 score.
  Serial.print(millis());
  Serial.print(": player2Score: ");
  Serial.println(player2Score);
}

bool errorCheckContactSwitches() {
  // If the left leaf-switch is LOW.
  if (hotSwitches[leftMax] == LOW) {
    // Route the 1st, 2nd, and 3rd frames.
    if (!emergencyLeft) {
      emergencyLeft = true;
    } else if (emergencyLeft && !emergencyLeft2) {
      emergencyLeft2 = true;
    } else {
      emergencyLeft = false;
      emergencyLeft2 = false;
      Serial.println("ERROR: emergency switches (Left)");
      return true;
    }
  } else {
    emergencyLeft = false;
    emergencyLeft2 = false;
  }
  // If the right leaf-switch is LOW.
  if (hotSwitches[rightMax] == LOW) {
    // Route the 1st, 2nd, and 3rd frames.
    if (!emergencyRight) {
      emergencyRight = true;
    } else if (emergencyRight && !emergencyRight2) {
      emergencyRight2 = true;
    } else {
      emergencyRight = false;
      emergencyRight2 = false;
      Serial.println("ERROR: emergency switches (Right)");
      return true;
    }
  } else {
    emergencyRight = false;
    emergencyRight2 = false;
  }
  return false;
}

void playSound(int index) {
  // Set next state.
  isSoundTimerOn = true;
  // Set timers.
  timers[sound].total = 0L;
  // Set sound.
  soundCurrent = index;
  digitalWrite(sounds[soundCurrent].pin, HIGH);
}

bool preRouteResults() {
  // Update preRouteSwitch/preRouteRoundCurrent with currentSwitch/roundCurrent.
  preRouteSwitch = currentSwitch;
  preRouteRoundCurrent = roundCurrent;
  // Declare result.
  bool result;
  // Route player 1 wins, player 2 wins, and tie.
  if (player1Score > player2Score) {
    // Route sudden death round, final round, and normal round.
    if (roundCurrent > 5) {
      // Set result to TRUE.
      result = true;
      // Set next state.
      isGameOver = true;
    } else if (roundCurrent == 4) {
      // Route switch 2, 3, and 4.
      if (currentSwitch == 2) {
        // Set result to TRUE.
        result = true;
      } else if (currentSwitch == 3) {
        // Set result to TRUE.
        result = true;
      } else if (currentSwitch == 4) {
        // Set result to TRUE.
        result = true;
      }
    } else {
      // Route switch 2, 3, and 4.
      if (currentSwitch == 5) {
        // Empty.
      } else if (currentSwitch == 3) {
        // Empty.
      } else if (currentSwitch == 2) {
        // Set result to TRUE.
        result = true;
      }
    }
  } else if (player1Score < player2Score) {
    // Route sudden death round, final round, and normal round.
    if (roundCurrent > 5) {
      // Set result to TRUE.
      result = true;
      // Set next state.
      isGameOver = true;
    } else if (roundCurrent == 5) {
      // Route switch 2, 3, and 4.
      if (currentSwitch == 2) {
        // Set result to TRUE.
        result = true;
      } else if (currentSwitch == 3) {
        // Set result to TRUE.
        result = true;
      } else if (currentSwitch == 4) {
        // Set result to TRUE.
        result = true;
      }
    } else {
      // Route switch 2, 3, and 4.
      if (currentSwitch == 2) {
        // Empty.
      } else if (currentSwitch == 3) {
        // Empty.
      } else if (currentSwitch == 4) {
        // Set result to TRUE.
        result = true;
      }
    }
  } else {
    // Route sudden death round, final round, and normal round.
    if (roundCurrent > 5) {
      // Set result to TRUE.
      result = true;
      // Set next state.
      isGameOver = true;
    } else if (roundCurrent == 5) {
      // Set result to TRUE.
      result = true;
      // Set next state.
      isFiveSecondTimerOn = true;
      // Set timers.
      timers[fiveSecond].total = 0L;
      //if (currentSwitch == 2) {
      //} else if (currentSwitch == 3) {
      //} else if (currentSwitch == 4) {
      //}
    } else {
      // Route switch 2, 3, and 4.
      if (currentSwitch == 2) {
        // Set result to TRUE.
        result = true;
        // Set next state.
        isTie = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 3) {
        // Set result to TRUE.
        result = true;
        // Set next state.
        isTie = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 4) {
        // Set result to TRUE.
        result = true;
        // Set next state.
        isTie = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
      }
    }
  }
  // Return result.
  return false;
}

void routeButtons() {
  // Route isReset, isCentering, isTugOn, catch plural switch error, isGameOver, and isSuddenDeath.
  if (isReset) {
    // If Start button is pressed and not-blocked.
    if (hotButtons[start] == LOW && !buttonBlocks[start]) {
      // Update debounce time.
      buttonDebounces[start] += delta;
      // If Start button is successfuly debounced.
      if (buttonDebounces[start] > DEBOUNCE_TIME_START) {
        // Print tracer.
        Serial.print(millis());
        Serial.println(": Start: $");
        // Set state.
        isReset = false;
        // Set next state.
        isToggleOn = true;
        isOneSecondTimerOn = true;
        isFiveSecondTimerOn = true;
        isReadyBlinking = true;
        isReadyTimerOn = true;
        // set timers.
        timers[toggle].total = 0L;
        timers[oneSecond].total = 0L;
        timers[fiveSecond].total = 0L;
        timers[fiveSecond].timeout = 2500L;
        timers[readySpecial].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(ready);
      }
    }
  } else if (isCentering) {
    // Route switches 1, 3, and 5.
    if (hotSwitches[left3] == LOW) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isCentering, left3");
      // Set motor.
      motor.moveRight();
    } else if (hotSwitches[right3] == LOW) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isCentering, right3");
      // Set motor.
      motor.moveLeft();
    } else if (hotSwitches[center] == LOW) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isCentering, center");
      // Set state.
      isCentering = false;
      // Set next state.
      isReset = true;
      // Set motor.
      motor.moveStop();
    }
  } else if (isTugOn) {
    // Route player1Left button PRESSED and RELEASED.
    if (hotButtons[player1Left] == LOW && !buttonBlocks[player1Left]) {
      // Update debounce.
      buttonDebounces[player1Left] += delta;
      // If debounce is successful.
      if (buttonDebounces[player1Left] > DEBOUNCE_TIME) {
        // Block input.
        buttonBlocks[player1Left] = true;
        // Update score.
        player1Taps[player1Index] = 0;
        player1Index++;
      }
    } else if (hotButtons[player1Left] == HIGH && buttonBlocks[player1Left]) {
      // Unblock input.
      buttonBlocks[player1Left] = false;
      // Reset debounce.
      buttonDebounces[player1Left] = 0;
    }
    // Route player1Right button PRESSED and RELEASED.
    if (hotButtons[player1Right] == LOW && !buttonBlocks[player1Right]) {
      // Update debounce.
      buttonDebounces[player1Right] += delta;
      // If debounce is successful.
      if (buttonDebounces[player1Right] > DEBOUNCE_TIME) {
        // Block input.
        buttonBlocks[player1Right] = true;
        // Update score.
        player1Taps[player1Index] = 1;
        player1Index++;
      }
    }
    else if (hotButtons[player1Right] == HIGH && buttonBlocks[player1Right]) {
      // Unblock input.
      buttonBlocks[player1Right] = false;
      // Reset debounce.
      buttonDebounces[player1Right] = 0;
    }

    // Route player2Left button PRESSED and RELEASED.
    if (hotButtons[player2Left] == LOW && !buttonBlocks[player2Left]) {
      // Update debounce.
      buttonDebounces[player2Left] += delta;
      // If debounce is successful.
      if (buttonDebounces[player2Left] > DEBOUNCE_TIME) {
        // Block input.
        buttonBlocks[player2Left] = true;
        // Update score.
        player2Taps[player2Index] = 0;
        player2Index++;
      }
    } else if (hotButtons[player2Left] && buttonBlocks[player2Left]) {
      // Unblock input.
      buttonBlocks[player2Left] = false;
      // Reset debounce.
      buttonDebounces[player2Left] = 0;
    }

    // Route player2Right button PRESSED and RELEASED.
    if (hotButtons[player2Right] == LOW && !buttonBlocks[player2Right]) {
      // Update debounce.
      buttonDebounces[player2Right] += delta;
      // If debounce is successful.
      if (buttonDebounces[player2Right] > DEBOUNCE_TIME) {
        // Block input.
        buttonBlocks[player2Right] = true;
        // Update score.
        player2Taps[player2Index] = 1;
        player2Index++;
      }
    } else if (hotButtons[player2Right] == HIGH && buttonBlocks[player2Right]) {
      // Unblock input.
      buttonBlocks[player2Right] = false;
      // Reset debounce.
      buttonDebounces[player2Right] = 0;
    }
  } else if (currentSwitch == previousSwitch) {
    // Print tracer.
    Serial.print(millis());
    Serial.print(": ");
    Serial.println("INPUT BLOCKED: same switch.");
  } else if ((isGameOver || isWinnerLeftBlinking || isWinnerRightBlinking || isChampionLeftBlinking || isChampionRightBlinking)
             && (!isSequenceOn)) {
    // Route switches 1, 2, 3, 4, and 5.
    if (hotSwitches[left3] == LOW && targets[1]) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isGameOver, left3");
      // Set state.
      isGameOver = false;
      // Set timers.
      timers[tenSecond].total = 0L;
      // Set motor.
      motor.moveStop();
      targets[1] = false;
    } else if (hotSwitches[left1] == LOW && targets[2]) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isGameOver, left1");
      // Set next state.
      isFiveSecondTimerOn = true;
      // Set timers.
      timers[fiveSecond].total = 0L;
      // Set motor.
      motor.moveStop();
      targets[2] = false;
    } else if (hotSwitches[center] == LOW && targets[3]) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isGameOver, center");
      // Set next state.
      isFiveSecondTimerOn = true;
      // Set timers.
      timers[fiveSecond].total = 0L;
      // Set motor.
      motor.moveStop();
      targets[3] = false;
    } else if (hotSwitches[right1] == LOW && targets[4]) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isGameOver, right1");
      // Set next state.
      isFiveSecondTimerOn = true;
      // Set timers.
      timers[fiveSecond].total = 0L;
      // Set motor.
      motor.moveStop();
      targets[4] = false;
    } else if (hotSwitches[right3] == LOW && targets[5]) {
      // Print tracer.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isGameOver, right3");
      // Set next state.
      isGameOver = false;
      // Set timers.
      timers[tenSecond].total = 0L;
      // Set motor.
      motor.moveStop();
      targets[5] = false;
    }
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    // Route switch 3.
    if (hotSwitches[center] == LOW && targets[3]) {
      // Print tracers.
      Serial.print(millis());
      Serial.print(": ");
      Serial.println("isSuddenDeath, center");
      // Set motor.
      motor.moveStop();
      targets[3] = false;
    }
  }
}

void routeResults() {
  if (player1Score > player2Score) {
    if (preRouteRoundCurrent > 5) {
      // Set motor.
      motor.moveLeft();
      setTarget(1);
    } else if (preRouteRoundCurrent == 5) {
      if (currentSwitch == 2) {
        // Set motor.
        motor.moveLeft();
        setTarget(1);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 4) {
        // Set motor.
        motor.moveLeft();
        setTarget(3);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 4) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(2);
      } else if (currentSwitch == 2) {
        // Set motor.
        setTarget(1);
      }
      // Set motor.
      motor.moveLeft();
    }
  } else if (player1Score < player2Score) {
    if (preRouteRoundCurrent > 5) {
      // Set motor.
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 5) {
      if (currentSwitch == 2) {
        // Set motor.
        motor.moveRight();
        setTarget(3);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 4) {
        // Set motor.
        motor.moveRight();
        setTarget(5);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(4);
      } else if (currentSwitch == 4) {
        // Set motor.
        setTarget(5);
      }
      motor.moveRight();
    }
  } else {
    if (preRouteRoundCurrent > 5) {
      // Set motor.
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 5) {
      if (currentSwitch == 2) {
        // Set motor.
        motor.moveRight();
        setTarget(3);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 4) {
        // Set motor.
        motor.moveLeft();
        setTarget(3);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      if (currentSwitch == 2) {
        // Set motor.
        setTarget(2);
      } else if (currentSwitch == 3) {
        // Set motor.
        setTarget(3);
      } else if (currentSwitch == 4) {
        // Set motor.
        setTarget(4);
      }
    }
    // Set five second timer.
    timers[fiveSecond].total = 0L;
    isFiveSecondTimerOn = true;
  }
}

void routeResults3() {
  // Route player 1 wins, player 2 wins, and tie.
  if (player1Score > player2Score) {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionLeftBlinking = true;
      // Set lights.
      digitalWrite(pinLightWinnerLeft, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set lights.
      playSound(catThird);
      // Set motor.
      motor.moveLeft();
      setTarget(1);
    } else if (preRouteRoundCurrent == 5) {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isChampionLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightWinnerLeft, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(catThird);
        // Set motor.
        motor.moveLeft();
        setTarget(1);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 4) {
        // Set lights.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
        // Set motor.
        motor.moveLeft();
        setTarget(3);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 4) {
        // Set next state.
        isWinnerTimerOn = true;
        isWinnerLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(catFirst);
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isWinnerTimerOn = true;
        isWinnerLeftBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(catFirst);
        // Set motor.
        setTarget(2);
      } else if (preRouteSwitch == 2) {
        // Set next state.
        isChampionLeftBlinking = true;
        // Set lights.
        digitalWrite(pinLightWinnerLeft, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(catThird);
        // Set motor.
        setTarget(1);
      }
      // Set motor.
      motor.moveLeft();
    }
  } else if (player1Score < player2Score) {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightWinnerRight, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set sound.
      playSound(dogThird);
      // Set motor.
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 5) {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set sound.
        playSound(suddenDeath);
        // Set motor.
        motor.moveRight();
        setTarget(3);
      } else if (preRouteSwitch == 3) {
        // Set lights.
        isSuddenDeathLeftBlinking = true;
        isSuddenDeathRightBlinking = true;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, HIGH);
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isChampionRightBlinking = true;
        // Set lights.
        digitalWrite(pinLightWinnerRight, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(dogThird);
        // Set motor.
        motor.moveRight();
        setTarget(5);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isWinnerRightBlinking = true;
        isWinnerTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(dogFirst);
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isWinnerRightBlinking = true;
        isWinnerTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[winnerSpecial].total = 0L;
        // Set sound.
        playSound(dogFirst);
        // Set motor.
        setTarget(4);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isChampionRightBlinking = true;
        // Set timers.
        timers[toggle].total = 0L;
        // Set lights.
        digitalWrite(pinLightWinnerRight, HIGH);
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(dogThird);
        // Set motor.
        setTarget(5);
      }
      // Set motor.
      motor.moveRight();
    }
  } else {
    // Route sudden death round, final round, and normal round.
    if (preRouteRoundCurrent > 5) {
      // Set next state.
      isGameOver = true;
      isChampionRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightWinnerRight, HIGH);
      digitalWrite(pinLightChampionRight, HIGH);
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
      // Set sound.
      playSound(dogThird);
      // Set motor.
      motor.moveRight();
      setTarget(5);
    } else if (preRouteRoundCurrent == 5) {
      // Set next state.
      isSuddenDeathLeftBlinking = true;
      isSuddenDeathRightBlinking = true;
      // Set timers.
      timers[toggle].total = 0L;
      // Set lights.
      digitalWrite(pinLightSuddenDeathLeft, HIGH);
      digitalWrite(pinLightSuddenDeathRight, HIGH);
      // Set sound.
      playSound(suddenDeath);
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set motor.
        motor.moveRight();
        setTarget(3);
      } else if (preRouteSwitch == 3) {
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 4) {
        // Set motor.
        motor.moveLeft();
        setTarget(3);
      }
      // Set five second timer.
      timers[fiveSecond].total = 0L;
      isFiveSecondTimerOn = true;
    } else {
      // Route switch 2, 3, and 4.
      if (preRouteSwitch == 2) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
        // Set motor.
        setTarget(2);
      } else if (preRouteSwitch == 3) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
        // Set motor.
        setTarget(3);
      } else if (preRouteSwitch == 4) {
        // Set next state.
        isTie = true;
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        // Set sound.
        playSound(tie);
        // Set motor.
        setTarget(4);
      }
    }
    // Set five second timer.
    timers[fiveSecond].total = 0L;
    isFiveSecondTimerOn = true;
  }
}

void startFunction() {
  // Print tracers.
  Serial.print("start(): ");
  Serial.print(millis()); Serial.print(": "); Serial.println(OUTGOING_START);
}

void stopStopTimer() {
  // Return is isStopTimerOn is FALSE.
  if (!isStopTimerOn) {
    return;
  }
  // Reset state.
  isStopTimerOn = false;
  // Set timers.
  timers[stopSpecial].total = 0L;
}

void stopWinnerTimer() {
  // Return if isWinnerTimerOn is FALSE.
  if (!isWinnerTimerOn) {
    return;
  }
  // Reset state.
  isWinnerTimerOn = false;
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  // Set next state.
  isToggleOn = true;
  isOneSecondTimerOn = true;
  isFiveSecondTimerOn = true;
  // Set timers.
  timers[toggle].total -= 200L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].total = 0L;
  timers[winnerSpecial].total = 0L;
  // Set lights.
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  // Set sound.
  playSound(ready);
  // Route hot switches.
  if (hotSwitches[left1] == LOW) {
    startReadyFromWinnerStop234();
  } else if (hotSwitches[center] == LOW) {
    startReadyFromWinnerStop234();
  } else if (hotSwitches[right1] == LOW) {
    startReadyFromWinnerStop234();
  } else if (hotSwitches[left3] == LOW) {
    startReadyFromWinnerStop15();
  } else if (hotSwitches[right3] == LOW) {
    startReadyFromWinnerStop15();
  }
}

void startReadyFromWinnerStop15() {
  // Set next state.
  isChampionLeftBlinking = true;
  // Set lights.
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
}

void startReadyFromWinnerStop234() {
  // Set next state.
  isReadyBlinking = true;
  isReadyTimerOn = true;
  // Set timers.
  timers[readySpecial].total = 0L;
  timers[fiveSecond].timeout = 2500L;
  // Set lights.
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
  // TODO: Remember to test this removal.
  //if (isChampionLeftBlinking || isChampionRightBlinking) {
  //  isReadyBlinking = false;
  //  digitalWrite(pinLightReady, LOW);
  //}
}

void stopChampion() {
  // Reset state.
  isReadyBlinking = false;
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  isChampionLeftBlinking = false;
  isChampionRightBlinking = false;
  isSuddenDeathLeftBlinking = false;
  isSuddenDeathRightBlinking = false;
  isReset = false;
  isOneOn = false;
  isTwoOn = false;
  isThreeOn = false;
  isTugOn = false;
  isStopOn = false;
  isReset = false;
  roundCurrent = 0;
  // Set next state.
  isCentering = true;
  isToggleOn = true;
  isOneSecondTimerOn = true;
  isFiveSecondTimerOn = true;
  // Set timers.
  timers[toggle].total -= 200L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].total = 0L;
  // Set lights.
  digitalWrite(pinLightChampionLeft, LOW);
  digitalWrite(pinLightChampionRight, LOW);
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
  digitalWrite(pinLightReady, LOW);
  digitalWrite(pinLightOne, LOW);
  digitalWrite(pinLightTwo, LOW);
  digitalWrite(pinLightThree, LOW);
  digitalWrite(pinLightTug, LOW);
  digitalWrite(pinLightStop, LOW);
}

void stopTenSecondTimer() {
  // Return if isTenSecondTimerOn is FALSE.
  if (!isTenSecondTimerOn) {
    return;
  }
  // Reset state.
  isTenSecondTimerOn = false;
  // Set timers.
  timers[tenSecond].total = 0L;
  // Route new state.
  if (isChampionLeftBlinking || isChampionRightBlinking) {
    stopChampion();
  }
}

void updateButtons() {
  // Update hotButtons array.
  hotButtons[start] = digitalRead(pinButtonStart);
  hotButtons[player1Left] = digitalRead(pinButtonPlayer1Left);
  hotButtons[player1Right] = digitalRead(pinButtonPlayer1Right);
  hotButtons[player2Left] = digitalRead(pinButtonPlayer2Left);
  hotButtons[player2Right] = digitalRead(pinButtonPlayer2Right);
}
