// Include 2nd-party libraries.
#include "super_tug_of_war.h"
// Include 3rd-party libraries.
#include <MemoryFree.h>;

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
  timers[countSpecial].timeout = COUNT_TIMEOUT;
  // Setup taps.
  for (int i = 0; i < TAPS_MAX; ++i) {
    player1Taps[i] = 0;
  }
  // Setup button debounces.
  for (unsigned int i = 0; i < BUTTON_SIZE; ++i) {
    buttonDebounces[i] = 0L;
  }
  // Setup sounds.
  for (int i = FIRST_SOUND_PIN; i < LAST_SOUND_PIN + 1; ++i) {
    sounds[index].pin = i;
    pinMode(sounds[index].pin, OUTPUT);
    index++;
  }
  index = 0;
  // Setup lights.
  for (int i = FIRST_LIGHT_PIN; i < LAST_LIGHT_PIN + 1; ++i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  // Setup buttons.
  for (int i = FIRST_BUTTON_PIN; i < LAST_BUTTON_PIN + 1; ++i) {
    if (i == pinUnused1 || i == pinUnused2) {
      continue;
    }
    buttons[index].pin = i;
    pinMode(buttons[index].pin, INPUT_PULLUP);
    ++index;
  }
  // Setup switches.
  index = 0;
  for (int i = FIRST_SWITCH_PIN; i < LAST_SWITCH_PIN + 1; ++i) {
    if (i == pinUnused3 || i == pinUnused4) {
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
  pinMode(pinCount, OUTPUT);
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
  if (timers[countSpecial].total >= COUNT_TIMEOUT) {
    stopCount();
  }
  if (errorCheckContactSwitches()) {
    //  return;
  }
  // Route Buttons;
  routeButtons();
}

////////////////////////////////////////////////////////////////////////
// Sounds //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @param i The sound index to play.

   Play the sound at index.

   RUSCAL:
   - isSoundTimerOn <- TRUE
   - timers[sound].total <- 0
   - soundCurrent <- index
   - DigitalWrite (sounds[soundCurrent].pin, TRUE)
*/
void playSound(int index) {
  isSoundTimerOn = true;
  timers[sound].total = 0L;
  soundCurrent = index;
  digitalWrite(sounds[soundCurrent].pin, HIGH);
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Update the hot-buttons array.

   RUSCAL:
   - hotButtons[start] <- DigitalRead (pinButtonStart)
   - hotButtons[player1Left] <- DigitalRead (pinButtonPlayer1Left)
   - hotButtons[player1Right] <- DigitalRead (pinButtonPlayer1Right)
   - hotButtons[player2Left] <- DigitalRead (pinButtonPlayer2Left)
   - hotButtons[player2Right] <- DigitalRead (pinButtonPlayer2Right)
*/
void updateButtons() {
  hotButtons[start] = digitalRead(pinButtonStart);
  hotButtons[player1Left] = digitalRead(pinButtonPlayer1Left);
  hotButtons[player1Right] = digitalRead(pinButtonPlayer1Right);
  hotButtons[player2Left] = digitalRead(pinButtonPlayer2Left);
  hotButtons[player2Right] = digitalRead(pinButtonPlayer2Right);
}

////////////////////////////////////////////////////////////////////////
// Switches ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Perform digitalRead(int) calls, and read the results into the
   hotSwitches.

   RUSCAL:
   - i isoftype Num
   - loop
    + exitif (i >= SWITCH_SIZE)
    + i <- i + 1
    + debouncedSwitches[i] = TRUE
   - endloop
   - hotSwitches[leftMax] <- DigitalRead (pinSwitchLeftMax)
   - howSwitches[left3] <- DigitalRead (pinSwitchLeft3)
   - hotSwitches[left1] <- DigitalRead (pinSwitchLeft1)
   - howSwitches[center] <- DigitalRead (pinSwitchCenter)
   - howSwitches[right1] <- DigitalRead (pinSwitchRight1)
   - hotSwitches[right3] <- DigitalRead (pinSwitchRight3)
   - howSwitches[rightMax] <- DigitalRead (pinSwitchRightMax)
*/
void updateSwitches() {
  for (int i = 0; i < SWITCH_SIZE; ++i) {
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

////////////////////////////////////////////////////////////////////////
// Motor ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @param i The micro-switch index to target.

   Set the micro-switch target.

   RUSCAL:
   - isTenSecondTimerOn <- TRUE
   - timers[tenSecond].total = 0
   - i isoftype Num
   - loop
    + exitif (i >= SWITCH_SIZE)
    + i <- i + 1
    + targets[i] <- FALSE
   - endloop
   - targets[index] <- TRUE
*/
void setTarget(int index) {
  isTenSecondTimerOn = true;
  timers[tenSecond].total = 0L;
  for (int i = 0; i < SWITCH_SIZE; ++i) {
    targets[i] = false;
  }
  targets[index] = true;
}

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Debounce By Time ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   @param i The switch index to debounce.

   If the hot-switch is LOW and the block is FALSE, then update the
   debounce time. If the debounce time is greater than the timeout,
   then set the block to TRUE and the debounced-switch to LOW.

   If the hot-switch is HIGH and the block is FALSE, then set the block
   to FALSE and the debounce to ZERO.

   RUSCAL:
   - if ((hotSwitches[i] = LOW) AND NOT (switchBlocks[i]))
    + switchDebounces[i] <- switchDebounces + delta
    + if (switchDebounces[i] > DEBOUNCE_TIME_MICRO_SWITCHES)
     - print (Millis ())
     - print (": debounced switch by time: ")
     - print (i)
     - switchBlocks[i] <- TRUE
     - debouncedSwitches[i] <- FALSE
    + endif
   - elseif ((howSwitches[i] = TRUE) AND (switchBlocks[i]))
    + switchBlocks[i] <- FALSE
    + switchDebounces[i] <- 0
   - endif
*/
void debounceSwitchByTime(int i) {
  if (hotSwitches[i] == LOW && !switchBlocks[i]) {
    switchDebounces[i] += delta;
    if (switchDebounces[i] > DEBOUNCE_TIME_MICRO_SWITCHES) {
      Serial.print(millis());
      Serial.print(": debounced switch by time:  ");
      Serial.println(i);
      switchBlocks[i] = true;
      debouncedSwitches[i] = LOW;
    }
  } else if (hotSwitches[i] == HIGH && switchBlocks[i]) {
    switchBlocks[i] = false;
    switchDebounces[i] = 0;
  }
}

/**
   Debounce each switch.

   RUSCAL:
   - i isoftype Num
   - loop
    + exitif (i >= SWITCH_SIZE)
    + i <- i + 1
    + DebounceSwitchByTime (i)
   - endloop
*/
void debounceSwitchesByTime() {
  for (int i = 0; i < SWITCH_SIZE; ++i) {
    debounceSwitchByTime(i);
  }
}

////////////////////////////////////////////////////////////////////////
// Debounce By Position ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   If the single pressed micro-switch is not equal to the current
   micro-switch, then update the current and previous micro-switch. Set
   the previous micro-switch to the current micro-switch. Set the
   current micro-switch to the single pressed micro-switch.

   RUSCAL:
   - if NOT (singleSwitch = currentSwitch)
    + previousSwitch <- currentSwitch
    + currentSwitch <- singleSwitch
    + print (Millis ())
    + print (": debounced switch by position: ")
    + print (previousSwitch)
    + print (" to ")
    + print (currentSwitch)
   - endif
*/
void debounceSwitchesByPosition() {
  if (singleSwitch != currentSwitch) {
    previousSwitch = currentSwitch;
    currentSwitch = singleSwitch;
    Serial.print(millis());
    Serial.print(": debounced switch by position: ");
    Serial.print(previousSwitch);
    Serial.print(" to ");
    Serial.println(currentSwitch);
  }
}

////////////////////////////////////////////////////////////////////////
// Debounce by Frame ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// States //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Scores //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Calculate the Player 1 and Player 2 scores.

   Loops through each player's array of taps, and awards a point if the
   current index is zero and the next index is one.

   RUSCAL:
    - if (isDebug)
     + print (Millis ())
     + print (": round Current: ")
     + print (roundCurrent)
    - endif
    - if (player1Index > 0)
     + i isoftype Num
     + loop
      - exitif (i >= player1Index - 1)
      - i <- i + 1
      - if ((player1Taps[i] = 0) AND (player1Taps[i + 1] = 1))
       + playe1Score <- player1Score + 1
      - endif
     + endloop
    - endif
    - if (isDebug)
     + print (Millis ())
     + print (": player1Score: ")
     + print (player1Score)
    - endif
    - if (player2Index > 0)
     + i isoftype Num
     + loop
      - exitif (i >= player2Index - 1)
      - i <- i + 1
       + if ((player2Taps[i] = 0) AND (player2Taps[i + 1] = 1))
        - player2Score <- player2Score + 1
       + endif
     + endloop
    - endif
    - if (isDebug)
     + print (Millis ())
     + print (": player2Score: ")
     + print (player2Score)
    - endif
*/
void calculateResults() {
  if (isDebug) {
    Serial.print(millis());
    Serial.print(": roundCurrent: ");
    Serial.println(roundCurrent);
  }
  if (player1Index > 0) {
    for (int i = 0; i < player1Index - 1; ++i) {
      if ((player1Taps[i] == 0) && (player1Taps[i + 1] == 1)) {
        player1Score++;
      }
    }
  }
  if (isDebug) {
    Serial.print(millis());
    Serial.print(": player1Score: ");
    Serial.println(player1Score);
  }
  if (player2Index > 0) {
    for (int i = 0; i < player2Index - 1; ++i) {
      if ((player2Taps[i] == 0) && (player2Taps[i + 1] == 1)) {
        player2Score++;
      }
    }
  }
  if (isDebug) {
    Serial.print(millis());
    Serial.print(": player2Score: ");
    Serial.println(player2Score);
  }
}

/**
   Pre-route the results. Determine is the currentSwitch is valid, and
   timers[fiveSecond].totalupdate the isGameOver, isTie,
   isFiveSecondTimerOn, and timers[fiveSecond].total variables as
   needed.

   \return TRUE if currentSwitch is an expected position. Otherwise,
   FALSE.

   RUSCAL:
   - preRouteSwitch <- currentSwitch
   - preRouteRoundCurrent <- roundCurrent
   - if (player1Score > player2Score)
    + if (roundCurrent > 5)
     - result <- TRUE
     - isGameOver <- TRUE
    + elseif (roundCurrent = 4)
     - if (currentSwitch = 2)
      + result <- TRUE
     - elseif (currentSwitch = 3)
      + result <- TRUE
     - elseif (currentSwitch = 4)
      + result <- TRUE
     - endif
    + else
     - if (currentSwitch = 5)
*/
bool preRouteResults() {
  preRouteSwitch = currentSwitch;
  preRouteRoundCurrent = roundCurrent;
  bool result;
  if (player1Score > player2Score) {
    if (roundCurrent > ROUND_MAX) {
      /*
        if (currentSwitch == leftMax) {
        } else if (currentSwitch == left3) {
        } else if (currentSwitch == left1) {
        } else if (currentSwitch == center) {
        } else if (currentSwitch == right1) {
        } else if (currentSwitch == right3) {
        } else if (currentSwitch == rightMax) {
        }
      */
      /*
        switch (currentSwitch)
        {
        case leftMax:
          break;
        case left3:
          break;
        case left1:
          break;
        case center:
          break;
        case right1:
          break;
        case right3:
          break;
        case rightMax:
          break;
        default:
          break;
        }
      */
      result = true;
      //isGameOver = true;
    } else if (roundCurrent == ROUND_MAX) {
      if (currentSwitch == left1) {
        result = true;
      } else if (currentSwitch == center) {
        result = true;
      } else if (currentSwitch == right1) {
        result = true;
      }
    } else {
      if (currentSwitch == right3) {
      } else if (currentSwitch == center) {
      } else if (currentSwitch == left1) {
        result = true;
      }
    }
  } else if (player1Score < player2Score) {
    if (roundCurrent > ROUND_MAX) {
      result = true;
      //isGameOver = true;
    } else if (roundCurrent == ROUND_MAX) {
      if (currentSwitch == left1) {
        result = true;
      } else if (currentSwitch == center) {
        result = true;
      } else if (currentSwitch == right1) {
        result = true;
      }
    } else {
      if (currentSwitch == left1) {
      } else if (currentSwitch == center) {
      } else if (currentSwitch == right1) {
        result = true;
      }
    }
  } else {
    if (roundCurrent > ROUND_MAX) {
      result = true;
      //isGameOver = true;
    } else if (roundCurrent == ROUND_MAX) {
      result = true;
      //isFiveSecondTimerOn = true;
      //timers[fiveSecond].total = 0L;
    } else {
      if (currentSwitch == left1) {
        result = true;
        //isTie = true;
        //timers[fiveSecond].timeout = TIE_TIMEOUT;
      } else if (currentSwitch == center) {
        result = true;
        //isTie = true;
        //timers[fiveSecond].timeout = TIE_TIMEOUT;
      } else if (currentSwitch == right1) {
        result = true;
        //isTie = true;
        //timers[fiveSecond].timeout = TIE_TIMEOUT;
      }
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////
// Tug Sequences ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Stop the Tug Segment state.

   RUSCAL:
   - timers[sequence].total = 0
   - timers[sequence].timeout <- sequenceTimeout[0][sequenceI]
   - isSequenceLeft <- sequenceIsLeft[sequenceJ][sequenceI]
   - if (isSequenceLeft)
    + motor.MotorLeft ()
   - else
    + motor.MoveRight ()
   - endif
   - sequenceI <- sequenceI + 1
   - if (sequenceI >= SEQUENCE_I_MAX)
    + sequenceI <- 0
    + sequenceJ <- sequenceJ + 1
    + if (sequenceJ >= SEQUENCE_J_MAX)
     - sequenceJ <- 0
    + endif
   - endif
*/
void stopTugSegment() {
  timers[sequence].total = 0L;
  timers[sequence].timeout = sequenceTimeout[0][sequenceI];
  isSequenceLeft = sequenceIsLeft[sequenceJ][sequenceI];
  if (isSequenceLeft) {
    motor.moveLeft();
  } else {
    motor.moveRight();
  }
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
   Stop the Tug Sequence state.

   RUSCAL:
   - motor.MoveStop ()
   - isSequenceOn <- FALSE
   - timers[sequence].total <- 0
*/
void stopTugSequence() {
  motor.moveStop();
  isSequenceOn = false;
  timers[sequence].total = 0L;
}

////////////////////////////////////////////////////////////////////////
// Routing /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Start the Ready state from the Winner state when on the 1, or 5
   micro-switches.

   RUSCAL:
   - isChampionLeftBlinking <- TRUE
   - DigitalWrite (pinLightSuddenDeathLeft, FALSE)
   - DigitalWrite (pinLightSuddenDeathRight, FALSE)
*/
void startReadyFromWinnerStop15() {
  isChampionLeftBlinking = true;
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
}

/**
   Start the Ready state from the Winner state when on the 2, 3, or 4
   micro-switches.

   RUSCAL:
   - isReadyBlinking <- TRUE
   - isReadyTimerOn <- TRUE
   - timers[readySpecial].total <- 0
   - timers[fiveSeconds].timeout <- READY_TIMEOUT
   - DigitalWrite (pinLightSuddenDeathLeft, FALSE)
   - DigitalWrite (pinLightSuddenDeathRight, FALSE)
*/
void startReadyFromWinnerStop234() {
  isReadyBlinking = true;
  isReadyTimerOn = true;
  timers[readySpecial].total = 0L;
  timers[fiveSecond].timeout = READY_TIMEOUT; // TODO: Check this change. // 2500L;
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
}

/**
   Stop the Champion state.

   RUSCAL:
   - isWinnerLeftBlinking <- FALSE
   - isWinnerRightBlinking <- FALSE
   - isChampionLeftBlinking <- FALSE
   - isChampionRightBlinking <- FALSE
   - isReset <- FALSE
   - roundCurrent <- 0
   - isCentering <- TRUE
   - DigitalWrite (pinLightChampionLeft, FALSE)
   - DigitalWrite (pinLightChampionRight, FALSE)
   - DigitalWrite (pinLightWinnerLeft, FALSE)
   - DigitalWrite (pinLightWinnerRight, FALSE)
*/
void stopChampion() {
  // TODO: Check these changes.
  //isReadyBlinking = false;
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  isChampionLeftBlinking = false;
  isChampionRightBlinking = false;
  //isSuddenDeathLeftBlinking = false;
  //isSuddenDeathRightBlinking = false;
  isReset = false;
  //isOneOn = false;
  //isTwoOn = false;
  //isThreeOn = false;
  //isTugOn = false;
  //isStopOn = false;
  //isReset = false;
  roundCurrent = 0;
  isCentering = true;
  //isToggleOn = true;
  //isOneSecondTimerOn = true;
  //isFiveSecondTimerOn = true;
  //timers[toggle].total -= 200L;
  //timers[oneSecond].total = 0L;
  //timers[fiveSecond].total = 0L;
  digitalWrite(pinLightChampionLeft, LOW);
  digitalWrite(pinLightChampionRight, LOW);
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  //digitalWrite(pinLightSuddenDeathLeft, LOW);
  //digitalWrite(pinLightSuddenDeathRight, LOW);
  //digitalWrite(pinLightReady, LOW);
  //digitalWrite(pinLightOne, LOW);
  //digitalWrite(pinLightTwo, LOW);
  //digitalWrite(pinLightThree, LOW);
  //digitalWrite(pinLightTug, LOW);
  //digitalWrite(pinLightStop, LOW);
}

/**
   Stop holding the counter's relay's pin HIGH.

   RUSCAL:
   - DigitalWrite (pinCount, FALSE)
*/
void stopCount() {
  digitalWrite(pinCount, LOW);
}

/**
   Stop the Tug state.

   RUSCAL:
   - isTugOn <- FALSE
   - DigitalWrite (pinLightTug, FALSE)
   - CalculateResults ()
   - preRouteResult <- PreRouteResults ()
   - if (preRouteResult)
    + RouteResults3 ()
   - else
    + StartStop ()
   - endif
   - roundCurrent <- roundCurrent + 1
*/
void stopIsTugOn() {
  isTugOn = false;
  digitalWrite(pinLightTug, LOW);
  calculateResults();
  preRouteResult = preRouteResults();
  if (preRouteResult) {
    routeResults3();
  } else {
    startStop();
  }
  roundCurrent++;
}

/**
   Stop the Ready state.

   RUSCAL:
   - if NOT (isReadyTimerOn)
    + returns NIL
   - endif
   - isReadyTimerOn <- FALSE
   - isReadyBlinking <- FALSE
   - timers[readySpecial].total <- 0
   - timers[oneSecond].total <- 0
   - timers[fiveSecond].total <- FIVE_SECOND_TIMEOUT
   - DigitalWrite (pinLightReady, FALSE)
   - DigitalWrite (pinLightOne, TRUE)
   - PlaySound (one)
*/
void stopReadyTimer() {
  // TODO: Check these changes.
  if (!isReadyTimerOn) {
    return;
  }
  isReadyTimerOn = false;
  isReadyBlinking = false;
  //isOneOn = true;
  //isOneSecondTimerOn = true;
  timers[readySpecial].total = 0L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].timeout = FIVE_SECOND_TIMEOUT; // TODO: Check this change. // 5000L;
  digitalWrite(pinLightReady, LOW);
  digitalWrite(pinLightOne, HIGH);
  playSound(one);
}

/**
   Stop playing the current sound.

   RUSCAL:
   - if NOT (isSoundTimerOn)
    + returns NIL
   - endif
   - isSoundTimerOn <- FALSE
   - timers[sound].total <- 0
   - DigitalWrite (sounds[soundCurrent].pin, FALSE)
   - soundCurrent <- -1
*/
void stopSoundTimer() {
  if (!isSoundTimerOn) {
    return;
  }
  isSoundTimerOn = false;
  timers[sound].total = 0L;
  digitalWrite(sounds[soundCurrent].pin, LOW);
  soundCurrent = -1;
}

/**
   Stop the Stop state.

   RUSCAL:
   - if NOT (isStopTimerOn)
    + returns NIL
   - endif
   - isStopTimerOn <- FALSE
   - timers[stopSpecial].total <- 0
*/
void stopStopTimer() {
  if (!isStopTimerOn) {
    return;
  }
  isStopTimerOn = false;
  timers[stopSpecial].total = 0L;
}

/**
   Stop the Sudden Death Blinking state.

   RUSCAL:
   - isSuddenDeathLeftBlinking <- FALSE
   - isSuddenDeathRightBlinking <- FALSE
   - isToggleOn <- TRUE
   - isOneSecondTimerOn <- TRUE
   - isFiveSecondTimerOn <- TRUE
   - isReadyBlinking <- TRUE
   - isReadyTimerOn <- TRUE
   - timers[toggle].total <- timers[toggle].total - TOGGLE_TIMEOUT
   - timers[oneSecond].total <- 0
   - timers[fiveSecond].timeout <- READY_TIMEOUT
   - PlaySound (ready)
*/
void stopSuddenDeathBlinking() {
  isSuddenDeathLeftBlinking = false;
  isSuddenDeathRightBlinking = false;
  isToggleOn = true;
  isOneSecondTimerOn = true;
  isFiveSecondTimerOn = true;
  isReadyBlinking = true;
  isReadyTimerOn = true;
  timers[toggle].total -= TOGGLE_TIMEOUT; // TODO: Check this change. // 200L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].timeout = READY_TIMEOUT; // TODO: Check this change. // 2500L;
  playSound(ready);
}

/**
   Stop the Tie state.

   RUSCAL:
   - isTie <- FALSE
   - isFiveSecondTimerOn <- TRUE
   - isReadyBlinking <- TRUE
   - isReadyTimerOn <- TRUE
   - timers[fiveSecond].timeout <- READY_TIMEOUT
   - timers[readySpecial].total <- 0
   - PlaySound (ready)
*/
void stopTie() {
  isTie = false;
  isFiveSecondTimerOn = true;
  isReadyBlinking = true;
  isReadyTimerOn = true;
  timers[fiveSecond].timeout = READY_TIMEOUT; // TODO: Check this change. // 2500L;
  timers[readySpecial].total = 0L;
  playSound(ready);
}

/**
   Stop the Winner state.

   RUSCAL:
   - if NOT (isWinnerTimerOn)
    + returns NIL
   - endif
   - isWinnerTimerOn <- FALSE
   - isWinnerLeftBlinking <- FALSE
   - isWinnerRightBlinking <- FALSE
   - isToggleOn <- TRUE
   - isOneSecondTimerOn <- TRUE
   - isFiveSecondTimerOn <- TRUE
   - timers[toggle].total <- timers[toggle].total - TOGGLE_TIMER
   - timers[oneSecond].total <- 0
   - timers[fiveSecond].total <- 0
   - timers[winnerSpecial].total <- 0
   - DigitalWrite (pinLightWinnerLeft, FALSE)
   - DigitalWrite (pinLightWinnerRight, FALSE)
   - PlaySound (ready)
   - if (hotSwitches[left1] = FALSE)
    + StartReadyFromWinnerStop234 ()
   - elseif (hotSwitches[center] = FALSE)
    + StartReadyFromWinnerStop234 ()
   - elseif (hotSwitches[right1] = FALSE)
    + StartReadyFromWinnerStop234 ()
   - elseif (hotSwitches[left3] = FALSE)
    + StartReadyFromWinnerStop15 ()
   - elseif (hotSwitches[right3] = FALSE)
    + StartReadyFromWinnerStop15 ()
   - endif
*/
void stopWinnerTimer() {
  if (!isWinnerTimerOn) {
    return;
  }
  isWinnerTimerOn = false;
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  isToggleOn = true;
  isOneSecondTimerOn = true;
  isFiveSecondTimerOn = true;
  timers[toggle].total -= TOGGLE_TIMEOUT; // TODO: Test this change. // 200L;
  timers[oneSecond].total = 0L;
  timers[fiveSecond].total = 0L;
  timers[winnerSpecial].total = 0L;
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  playSound(ready);
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

////////////////////////////////////////////////////////////////////////
// Messages ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Empty. Reset the application.

   RUSCAL:
   - print (Millis ())
   - print (": ")
   - print ("reset()")
   - isSuper <- FALSE
*/
void resetFunction() {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println("reset()");
  isSuper = false;
}

/**
   Empty. Start the application.

   RUSCAL:
   - print (Millis ())
   - print (": reset(), ")
   - print (OUTGOING_START)
   - isSuper <- TRUE
*/
void startFunction() {
  Serial.print(millis());
  Serial.print(": reset(), ");
  Serial.println(OUTGOING_START);
  isSuper = true;
}

////////////////////////////////////////////////////////////////////////
// Multi-Color LED /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Errors //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   - if (hotSwitches[leftMax] = FALSE)
    + if NOT (emergencyLeft)
     - emergencyLeft <- TRUE
    + elseif ((emergencyLeft) AND NOT (emergencyLeft2))
     - emergencyLeft2 <- TRUE
    + else
     - emergencyLeft <- FALSE
     - emergencyLeft2 <- FALSE
     - print ("ERROR: emergency switches (left)")
     - returns TRUE
    + endif
   - else
    + emergencyLeft <- FALSE
    + emergencyLeft2 <- FALSE
   - endif
   - if (hotSwitches[rightMax] = FALSE)
    + if NOT (emergencyRight)
     - emergencyRight <- TRUE
    + elseif ((emergencyRight) AND NOT (emergencyRight2))
     - emergencyRight2 <- TRUE
    + else
     - emergencyRight <- FALSE
     - emergencyRight2 <- FALSE
     - print ("ERROR: emergency switches (right)")
     - returns TRUE
    + elseif
   - else
    + emergencyRight <- FALSE
    + emergencyRight2 <- FALSE
   - endif
   - returns FALSE
*/
bool errorCheckContactSwitches() {
  if (hotSwitches[leftMax] == LOW) {
    if (!emergencyLeft) {
      emergencyLeft = true;
    } else if (emergencyLeft && !emergencyLeft2) {
      emergencyLeft2 = true;
    } else {
      emergencyLeft = false;
      emergencyLeft2 = false;
      Serial.println("ERROR: emergency switches (left)");
      return true;
    }
  } else {
    emergencyLeft = false;
    emergencyLeft2 = false;
  }
  if (hotSwitches[rightMax] == LOW) {
    if (!emergencyRight) {
      emergencyRight = true;
    } else if (emergencyRight && !emergencyRight2) {
      emergencyRight2 = true;
    } else {
      emergencyRight = false;
      emergencyRight2 = false;
      Serial.println("ERROR: emergency switches (right)");
      return true;
    }
  } else {
    emergencyRight = false;
    emergencyRight2 = false;
  }
  return false;
}

/**
   Count the number of debounced-switches. If more than one
   debounced-switch is LOW, then return TRUE. Otherwise, return FALSE.

   RUSCAL:
   - countSwitch <- 0
   - i isoftype Num
   - loop
    + exitif (i >= SWITCH_SIZE)
    + i <- i + 1
    + if (debouncedSwitches[i] = FALSE)
     - singleSwitch <- i
     - countSwitch <- countSwitch + 1
    + endif
   - endloop
   - if (countSwitch > 1)
    + countSwitch2 <- 0
    + i isoftype Num
    + loop
     - exitif (i >= SWITCH_SIZE)
     - i <- i + 1
     - if (debouncedSwitches[i] = FALSE)
      + print (Millis ())
      + print (": ERROR: Plural input, ")
      + print (countSwitch2)
      + print (", ")
      + print (i)
      + countSwitch2 <- countSwitch + 1
     - endif
    + endloop
    + returns TRUE
   - endif
   - returns FALSE
*/
bool errorCheckPluralInput() {
  countSwitch = 0;
  for (int i = 0; i < SWITCH_SIZE; ++i) {
    if (debouncedSwitches[i] == LOW) {
      singleSwitch = i;
      countSwitch++;
    }
  }
  if (countSwitch > 1) {
    countSwitch2 = 0;
    for (int i = 0; i < SWITCH_SIZE; ++i) {
      if (debouncedSwitches[i] == LOW) {
        Serial.print(millis());
        Serial.print(": ERROR: Plural input, ");
        Serial.print(countSwitch2);
        Serial.print(", ");
        Serial.println(i);
        countSwitch2++;
      }
    }
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////////
// Debug ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
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
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[fiveSecond].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathRight, HIGH);
        // Set sound.
        playSound(suddenDeath);
      } else if (preRouteSwitch == 3) {
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[fiveSecond].total = 0L;
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
        isFiveSecondTimerOn = true;
        // Set timers.
        timers[toggle].total = 0L;
        timers[fiveSecond].total = 0L;
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
    for (int i = 0; i < TAPS_MAX; ++i) {
      player1Taps[i] = 0;
      player2Taps[i] = 0;
    }
  } else if (isStopOn) {
    digitalWrite(pinLightStop, LOW);
    isStopOn = false;
  }
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
  if (isCountOn) {
    timers[countSpecial].total += delta;
  }
  // Update sequence and toggle timers regardless of state.
  timers[sequence].total += delta;
  timers[toggle].total += delta;
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
        isCountOn = true;
        // set timers.
        timers[toggle].total = 0L;
        timers[oneSecond].total = 0L;
        timers[fiveSecond].total = 0L;
        timers[fiveSecond].timeout = 2500L;
        timers[readySpecial].total = 0L;
        timers[countSpecial].total = 0L;
        // Set lights.
        digitalWrite(pinLightSuddenDeathLeft, LOW);
        digitalWrite(pinLightSuddenDeathRight, LOW);
        // Set sound.
        playSound(ready);
        // Set count pin.
        digitalWrite(pinCount, HIGH);
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
      isFiveSecondTimerOn = true;
      // Set timers.
      timers[toggle].total = 0L;
      timers[fiveSecond].total = 0L;
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
