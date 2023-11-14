// https://docs.arduino.cc/built-in-examples/digital/Debounce

#include "super_tug_of_war.h"

/**
   - Instantiate local variables.
   - Setup the //Serial library.
   - Setup timers.
   - Setup taps.
   - Setup button debounces.
   - Setup sounds.
   - Setup lights.
   - Setup buttons.
   - Setup switches.
   - Setup motor.
*/
void setup() {
  // Instantiate local variables.
  int index = 0;
  // Setup the //Serial library.
  Serial.begin(BAUD_RATE);
  ////Serial.flush();
  // Setup timers.
  timers[toggle].timeout = 100L;
  timers[oneSecond].timeout = 1000L;
  timers[fiveSecond].timeout = 5000L;
  timers[tenSecond].timeout = 10000L;
  timers[sequence].timeout = random(SEQUENCE_MIN, SEQUENCE_MAX);
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
    //buttonDebounces[i] = current;
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
  // New. Not documented.
  pinMode(pinButtonTouch, INPUT_PULLUP);
  pinMode(pinLightError, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinReset, OUTPUT);
  digitalWrite(pinReset, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  /*
    for (val = 255; val > 0; val--)
    {
    analogWrite(RED, val);
    analogWrite(GREEN, 255 - val);
    analogWrite(BLUE, 128 - val);
    Serial.println(val, DEC);
    delay(5);
    }
    for (val = 0; val < 255; val++)
    {
    analogWrite(RED, val);
    analogWrite(GREEN, 255 - val);
    analogWrite(BLUE, 128 - val);
    Serial.println(val, DEC);
    delay(5);
    }
  */
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(1000);
  analogWrite(RED, 0);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 0);
  delay(1000);
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);
  //Serial.println(val, DEC);
  //Serial.println(millis());
  pinMode(pinLightDebug, OUTPUT);
}

/**
   - Bandage isCentering bool on first loop. This should not happen.
   - Update timers.
   - Update tug sequence.
   - Update input.
   - Update timers.
*/
void loop() {
  // New. Not documented.
  //Serial.println(millis());
  /*
    if (digitalRead(pinButtonTouch) == HIGH) {
    //Serial.println("ON");
    digitalWrite(pinLightError, HIGH);
    delay(1000);
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
    digitalWrite(pinReset, LOW);
    } else {
    //Serial.println("OFF");
    digitalWrite(pinLightError, LOW);
    digitalWrite(pinBuzzer, LOW);
    }
  */

  //Serial.println(millis());
  if (isFirstLoop) {
    isSequenceOn = false;
    isFirstLoop = false;
  }
  // Update timers.
  updateTimers();
  // Update tug sequence.
  if (timers[fiveSecond].total > 4999L && isSequenceOn) {
    isFiveSecondTimerBlocked = true;
    stopTugSequence();
    //isFiveSecondTimerBlocked = true;
    //stopTugSequence();
  } else if (timers[sequence].total >= timers[sequence].timeout && isSequenceOn) {
    stopTugSegment();
  }
  // Update input.
  updateButtons();
  if (!isSequenceOn) {
    timers[sequence].total = 0L;
    updateSwitches();
    debounceSwitchesByTime();
    if (errorCheckPluralInput()) {
      return;
    }
    debounceSwitchesByPosition();
  }

  // Update timers.
  if (timers[sound].total >= 1000L && soundCurrent != -1) {
    stopSoundTimer();
  }
  if (timers[toggle].total >= 200L) {
    stopToggleTimer();
  }
  if (timers[oneSecond].total >= 1000L) {
    stopOneSecondTimer();
  }
  if (timers[fiveSecond].total >= timers[fiveSecond].timeout /*5000L*/) {
    if (isFiveSecondTimerBlocked) {
      isFiveSecondTimerBlocked = false;
    } else {
      stopFiveSecondTimer();
    }
    //stopFiveSecondTimer();
  }
  //if (isStopTimerOn) {
  //  motor.moveStop();
  //}
  //if (timers[fiveSecond].total >= 4000L && isFiveSecondTimerOn) {
  //if (isFiveSecondTimerBlocked) {
  //  isFiveSecondTimerBlocked = false;
  //} else {
  //stopFiveSecondTimer2();
  //}
  //}
  if (timers[winnerSpecial].total >= 4000L) {
    stopWinnerTimer();
  }
  if (timers[tenSecond].total >= 10000L) {
    stopTenSecondTimer();
  }
  if (timers[readySpecial].total >= 2500L) {
    stopReadyTimer();
  }
  if (timers[stopSpecial].total >= stopSpecialTimeout) {
    stopStopTimer();
  } else if (isStopTimerOn && timers[stopSpecial].total > 1100L) {
    routeResults2();
    routeResults();
    digitalWrite(pinLightStop, LOW);
    //routeResults2();
  } else if (isStopTimerOn && timers[stopSpecial].total < stopSpecialTimeout) {
    motor.moveStop();
  }
  if (errorCheckContactSwitches()) {
    return;
  }
  // Route Buttons;
  routeButtons();
  /*
    // Discovery.
    if (Serial.available() > 0) {
    // WARNING: Remember to consume the incoming bytes.
    // The error does not occur when using the usb.c or usb.py files.
    // The error does occur when reading/writing in a PyGame application.
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
  */
}

////////////////////////////////////////////////////////////////////////
// Private Functions ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction() {
  Serial.println("reset()");
}

void startFunction() {
  Serial.print("start(): ");
  Serial.println(OUTGOING_START);
}

void debounceSwitchByTime(int i) {
  if (hotSwitches[i] == LOW && !switchBlocks[i]) {
    switchDebounces[i] += delta;
    if (switchDebounces[i] > DEBOUNCE_TIME) {
      switchBlocks[i] = true;
      ////Serial.print("debounceSwitchByTime(");
      ////Serial.print(i);
      ////Serial.print(") - switchBlocks[");
      ////Serial.print(i);
      ////Serial.print("]: ");
      ////Serial.print(switchBlocks[i]);
      ////Serial.print(", switchDebounces[");
      ////Serial.print(i);
      ////Serial.print("]: ");
      //////Serial.println(switchDebounces[i]);
    }
  } else if (hotSwitches[i] && switchBlocks[i]) {
    switchBlocks[i] = false;
    switchDebounces[i] = 0;
    ////Serial.print("debounceSwitchByTime(");
    ////Serial.print(i);
    ////Serial.print(") - switchBlocks[");
    ////Serial.print(i);
    ////Serial.print("]: ");
    ////Serial.print(switchBlocks[i]);
    ////Serial.print(", switchDebounces[");
    ////Serial.print(i);
    ////Serial.print("]: ");
    //////Serial.println(switchDebounces[i]);
  }
}

void debounceSwitchesByTime() {
  for (unsigned int i = 0; i < SWITCH_SIZE; i++) {
    debounceSwitchByTime(i);
  }
}

/**
   - Update current/previous switches if a normal number (0 or 1) of switches are pressed.
*/
void debounceSwitchesByPosition() {
  // Update current/previous switches if a normal number (0 or 1) of switches are pressed.
  if (singleSwitch != currentSwitch) {
    previousSwitch = currentSwitch;
    currentSwitch = singleSwitch;
    ////Serial.print("debounceSwitchesByPosition() - ");
    ////Serial.print("currentSwitch: ");
    ////Serial.print(currentSwitch);
    ////Serial.print(", previousSwitch: ");
    ////Serial.print(previousSwitch);
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
    ////Serial.print("errorCheckPluralInput() - countSwitch");
    ////Serial.print(countSwitch);
    for (unsigned int i = 0; i < SWITCH_SIZE; i++) {
      if (hotSwitches[i] == LOW) {
        ////Serial.print(i);
      }
    }
    //////Serial.println("");
    return true;
  }
  return false;
}

void hardReset() {
  isCentering = true;
  isReset = false;
  roundCurrent = 0;
  
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  digitalWrite(pinLightSuddenDeathLeft, LOW);
  digitalWrite(pinLightSuddenDeathRight, LOW);
  digitalWrite(pinLightChampionLeft, LOW);
  digitalWrite(pinLightChampionRight, LOW);
  digitalWrite(pinLightReady, LOW);
  digitalWrite(pinLightOne, LOW);
  digitalWrite(pinLightTwo, LOW);
  digitalWrite(pinLightThree, LOW);
  digitalWrite(pinLightTug, LOW);
  digitalWrite(pinLightStop, LOW);
  
  isOneOn = false;
  isTwoOn = false;
  isThreeOn = false;
  isTugOn = false;
  isStopOn = false;
  isGameOver = false;
  isToggleOn = false;
  isReadyBlinking = false;
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  isChampionLeftBlinking = false;
  isChampionRightBlinking = false;
  isSuddenDeathLeftBlinking = false;
  isSuddenDeathRightBlinking = false;
  
  isCentering = true;
  isReset = false;
  isTie = 0;

  /*

  //hotButtons[] = {false, false, false, false, false};
  hotButtons[0] = false;
  hotButtons[1] = false;
  hotButtons[2] = false;
  hotButtons[3] = false;
  hotButtons[4] = false;
  //buttonBlocks[] = {false, false, false, false, false};
  buttonBlocks[0] = false;
  buttonBlocks[1] = false;
  buttonBlocks[2] = false;
  buttonBlocks[3] = false;
  buttonBlocks[4] = false;
  //buttonDebounces[] = {0L, 0L, 0L, 0L, 0L};
  buttonDebounces[0] = 0L;
  buttonDebounces[1] = 0L;
  buttonDebounces[2] = 0L;
  buttonDebounces[3] = 0L;
  buttonDebounces[4] = 0L;

  //hotSwitches[] = {false, false, false, false, false, false, false};
  hotSwitches[0] = false;
  hotSwitches[1] = false;
  hotSwitches[2] = false;
  hotSwitches[3] = false;
  hotSwitches[4] = false;
  hotSwitches[5] = false;
  hotSwitches[6] = false;
  //switchBlocks[] = {false, false, false, false, false, false, false};
  switchBlocks[0] = false;
  switchBlocks[1] = false;
  switchBlocks[2] = false;
  switchBlocks[3] = false;
  switchBlocks[4] = false;
  switchBlocks[5] = false;
  switchBlocks[6] = false;
  //switchDebounces[] = {0L, 0L, 0L, 0L, 0L, 0L, 0L};
  switchDebounces[0] = 0L;
  switchDebounces[1] = 0L;
  switchDebounces[2] = 0L;
  switchDebounces[3] = 0L;
  switchDebounces[4] = 0L;
  switchDebounces[5] = 0L;
  switchDebounces[6] = 0L;
  //targets[] = {false, false, false, false, false, false, false};
  targets[0] = false;
  targets[1] = false;
  targets[2] = false;
  targets[3] = false;
  targets[4] = false;
  targets[5] = false;
  targets[6] = false;


  player1Score = 0;
  player2Score = 0;
  player1Taps[TAPS_MAX];
  player2Taps[TAPS_MAX];
  player1Index = 0;
  player2Index = 0;
  roundCurrent = 0;
  roundCurrent2 = 0;
  roundMax = 6;
  debounceCurrent = 0;

  currentSwitch = -1;
  previousSwitch = -1;
  countSwitch = -1;
  singleSwitch = -1;
  isSwitchAlreadyBlocked = false;

  isFirstLoop = true;

  result;

  testCurrent = 0;
  testMax = 2;

  int roundCurrent3 = 0;

  isSequenceLeft = true;
  isSequenceOn = false;
  sequenceI = 0;
  sequenceJ = 0;
  //SEQUENCE_MIN = 200L;
  //SEQUENCE_MAX = 400L;
  sequenceCounter = 2;
  isFiveSecondTimerBlocked = false;

  //message[] = {'a', 'b', 'c'};
  message[0] = 'a';
  message[1] = 'b';
  message[2] = 'c';

  readyCounter = 0;
  isReadyComplete = false;

  errorPluralInput = false;

  isSoundTimerOn = false;
  isOneSecondTimerOn = false;
  isFourSecondTimerOn = false;
  isFiveSecondTimerOn = false;
  isTenSecondTimerOn = false;
  isStopTimerOn = false;
  isReadyTimerOn = false;
  isWinnerTimerOn = false;
  isSequenceTimerOn = false;

  preRouteResult = false;
  preRouteSwitch;
  preRouteRoundCurrent;

  emergencyStop;

  stopSpecialTimeout = 1515L;

  emergencyLeft = false;
  emergencyRight = false;
  emergencyLeft2 = false;
  emergencyRight2 = false;

  ///

  // Instantiate local variables.
  int index = 0;
  // Setup the //Serial library.
  //Serial.begin(BAUD_RATE);
  ////Serial.flush();
  // Setup timers.
  timers[toggle].timeout = 100L;
  timers[oneSecond].timeout = 1000L;
  timers[fiveSecond].timeout = 5000L;
  timers[tenSecond].timeout = 10000L;
  timers[sequence].timeout = random(SEQUENCE_MIN, SEQUENCE_MAX);
  timers[tieSpecial].timeout = 4000L;
  timers[stopSpecial].timeout = 1.515L;
  timers[readySpecial].timeout = 2500L;
  timers[winnerSpecial].timeout = 4000L;
  */
}

bool errorCheckContactSwitches() {
  if (hotSwitches[0] == LOW) {
    if (!emergencyLeft) {
      emergencyLeft = true;
      //return false;
    } else if (emergencyLeft && !emergencyLeft2) {
      emergencyLeft2 = true;
    } else {
      emergencyLeft = false;
      emergencyLeft2 = false;
      motor.moveStop();
      motor.moveRight();
      hardReset();
      //ditigalWrite(resetPin, LOW);
      //delay(50);
      return true;
    }
  } else {
    emergencyLeft = false;
    emergencyLeft2 = false;
  }
  if (hotSwitches[6] == LOW) {
    if (!emergencyRight) {
      emergencyRight = true;
      //return false;
    } else if (emergencyRight && !emergencyRight2) {
      emergencyRight2 = true;
    } else {
      emergencyRight = false;
      emergencyRight2 = false;
      motor.moveStop();
      motor.moveLeft();
      hardReset();
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
  ////Serial.print("routeResults() - player1Score ?> player2Score: ");
  ////Serial.print(player1Score > player2Score);
  ////Serial.print(", player1Score ?= player2Score: ");
  ////Serial.print(player1Score == player2Score);
  ////Serial.print(", preRouteRoundCurrent: ");
  ////Serial.print(preRouteRoundCurrent);
  ////Serial.print(", currentSwitch: ");
  //////Serial.println(currentSwitch);
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
  //randomWinner();
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
        //isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        setTarget(3);
      } else if (currentSwitch == 3) {
        //isWinnerLeftBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
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
        //isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
        setTarget(3);
      } else if (currentSwitch == 3) {
        //isWinnerRightBlinking = true; timers[winnerSpecial].total = 0L; isWinnerTimerOn = true;
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
      //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
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
  ////Serial.print("routeResults2() - player1Score ?> player2Score: ");
  ////Serial.print(player1Score > player2Score);
  ////Serial.print(", player1Score ?= player2Score: ");
  ////Serial.print(player1Score == player2Score);
  ////Serial.print(", preRouteRoundCurrent: ");
  ////Serial.print(preRouteRoundCurrent);
  ////Serial.print(", preRouteSwitch: ");
  //////Serial.println(preRouteSwitch);
  //randomWinner();
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
      //digitalWrite(pinLightWinnerRight, HIGH);
      timers[toggle].total = 0L;
      digitalWrite(pinLightChampionRight, HIGH);
      isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //isGameOver = true;
      //motor.moveRight();
      playSound(dogThird);
    } else if (preRouteRoundCurrent == 4) {
      //isToggleOn = true;
      //digitalWrite(pinLightSuddenDeathLeft, HIGH);
      timers[toggle].total = 0L;
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
        //isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("000");
      } else if (preRouteSwitch == 3) {
        //isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("111");
      } else if (preRouteSwitch == 4) {
        //isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("222");
      }
    }
  }
}

void routeResults3() {
  ////Serial.print("routeResults3() - player1Score ?> player2Score: ");
  ////Serial.print(player1Score > player2Score);
  ////Serial.print(", player1Score ?= player2Score: ");
  ////Serial.print(player1Score == player2Score);
  ////Serial.print(", roundCurrent: ");
  ////Serial.print(roundCurrent);
  ////Serial.print(", currentSwitch: ");
  //////Serial.println(currentSwitch);
  //randomWinner();
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
        //////Serial.println("YOU ARE HERE");
        playSound(catThird);
        //////Serial.println("YOU ARE THERE");
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
        isTie = 1;
        timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("333");
      } else if (currentSwitch == 3) {
        setTarget(3);
        isTie = 1; timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("444");
      } else if (currentSwitch == 4) {
        setTarget(4);
        isTie = 1; timers[fiveSecond].timeout = 3500L;
        timers[fiveSecond].total = 0L;
        isFiveSecondTimerOn = true;
        playSound(tie);
        //////Serial.println("555");
      }
    }
    timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
  }
}

bool preRouteResults() {
  ////Serial.print("preRouteResults() - player1Score ?> player2Score: ");
  ////Serial.print(player1Score > player2Score);
  ////Serial.print(", player1Score ?= player2Score: ");
  ////Serial.print(player1Score == player2Score);
  ////Serial.print(", roundCurrent: ");
  ////Serial.print(roundCurrent);
  ////Serial.print(", currentSwitch: ");
  //////Serial.println(currentSwitch);
  preRouteSwitch = currentSwitch;
  preRouteRoundCurrent = roundCurrent;
  bool result = false;
  //randomWinner();
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
        isTie = 1; timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 3) {
        result = true;
        isTie = 1; timers[fiveSecond].timeout = 3500L;
      } else if (currentSwitch == 4) {
        result = true;
        isTie = 1; timers[fiveSecond].timeout = 3500L;
      }
    }
  }
  ////Serial.print("result: ");
  //////Serial.println(result);
  //return result; Uncomment this to turn the results code back on.
  return false;
}

void playSound(int index) {
  soundCurrent = index;
  digitalWrite(sounds[soundCurrent].pin, HIGH);
  timers[sound].total = 0L;
  isSoundTimerOn = true;
}

/**
   - Set all elements of targets to FALSE;
   - Set the element of targets[index] to TRUE.
*/
void setTarget(int index) {
  ////Serial.print("setTarget(");
  ////Serial.print(index);
  //////Serial.println(")");
  isTenSecondTimerOn = true;
  timers[tenSecond].total = 0L;
  // Set all elements of targs to FALSE.
  for (unsigned int i = 0; i < SWITCH_SIZE; ++i) {
    targets[i] = false;
  }
  // Set the element of targets[index] to TRUE.
  targets[index] = true;
}

void stopOneSecondTimer() {
  if (!isOneSecondTimerOn) {
    return;
  }
  isOneSecondTimerOn = false;
  timers[oneSecond].total = 0L;// isOneSecondTimerOn = true;
  if (isOneOn) {
    ////Serial.print(", isOneOn: ");
    ////Serial.print(isOneOn);
    digitalWrite(pinLightOne, LOW);
    isOneOn = false;
    digitalWrite(pinLightTwo, HIGH);
    playSound(9);
    isTwoOn = true;
    timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
  } else if (isTwoOn) {
    ////Serial.print(", isTwoOn: ");
    ////Serial.print(isTwoOn);
    digitalWrite(pinLightTwo, LOW);
    isTwoOn = false;
    digitalWrite(pinLightThree, HIGH);
    playSound(10);
    isThreeOn = true;
    timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
  } else if (isThreeOn) {
    ////Serial.print(", isThreeOn: ");
    ////Serial.print(isThreeOn);
    digitalWrite(pinLightThree, LOW);
    isThreeOn = false;
    digitalWrite(pinLightTug, HIGH);
    playSound(7);
    isTugOn = true;
    isSequenceOn = true;
    timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    player1Index = 0;
    player2Index = 0;
    player1Score = 0;
    player2Score = 0;
    for (int i = 0; i < TAPS_MAX; i++) {
      player1Taps[i] = 0;
      player2Taps[i] = 0;
    }
  } else if (isStopOn) {
    ////Serial.print(", isStopOn: ");
    //////Serial.println(isStopOn);
    digitalWrite(pinLightStop, LOW);
    isStopOn = false;
    //calculateResults();
    //routeResults();
    //roundCurrent++;
  }
}

void calculateResults() {
  ////Serial.print("player1Taps: ");
  if (player1Index > 0) {
    for (int i = 0; i < player1Index - 1; i++) {
      ////Serial.print(player1Taps[i]);
      if ((player1Taps[i] == 0) && (player1Taps[i + 1] == 1)) {
        player1Score++;
        ////Serial.print("+");
      }
      ////Serial.print(",");
    }
  }
  ////Serial.print(player1Taps[player1Index - 1]);
  ////Serial.println();
  ////Serial.print("player2Taps: ");
  if (player2Index > 0) {
    for (int i = 0; i < player2Index - 1; i++) {
      ////Serial.print(player2Taps[i]);
      if ((player2Taps[i] == 0) && (player2Taps[i + 1] == 1)) {
        player2Score++;
        ////Serial.print("+");
      }
      ////Serial.print(",");
    }
  }
  ////Serial.print(player2Taps[player2Index - 1]);
  ////Serial.println();
  ////Serial.print("*** round: ");
  ////Serial.print(roundCurrent);
  ////Serial.print(", Player1Score: ");
  ////Serial.print(player1Score);
  ////Serial.print(", Player2Score: ");
  ////Serial.print(player2Score);
  ////Serial.println(" ***");
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
    //////Serial.println(", isTugOn");
    digitalWrite(pinLightTug, LOW);
    isTugOn = false;
    calculateResults();
    preRouteResult = preRouteResults();
    if (preRouteResult) {
      routeResults3();
    } else {
      ////Serial.print("preRouteResult: ");
      //////Serial.println(preRouteResult);
      playSound(stop);
      digitalWrite(pinLightStop, HIGH);
      isStopTimerOn = true;
      timers[stopSpecial].total = 0L;
      routeResults();
      isStopOn = true;
      //roundCurrent++;
    }
    roundCurrent++;
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    //////Serial.println(", isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking");
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
  } else if (isTie == 1/* && roundCurrent < 4*/) {
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
    isTie = 0;
  }
}

/*
  void stopFiveSecondTimer2() {
  if (!isFiveSecondTimerOn) {
    return;
  }
  isFiveSecondTimerOn = false;
  ////Serial.print("stopFiveSecondTimer2() - ");
  ////Serial.print("timers[");
  ////Serial.print(fiveSecond);
  ////Serial.print("]: ");
  ////Serial.print(timers[fiveSecond].total);
  timers[fiveSecond].total = 0L;
  if (isReadyBlinking) {
    //////Serial.println("HERE");
    isReadyTimerOn = true;
    stopReadyTimer();
  }
  }
*/

void stopTugSegment() {
  //////Serial.print("stopTugSegment() - timers[");
  //////Serial.print(sequence);
  //////Serial.print("].timeout: ");
  //////Serial.print(sequenceTimeout[sequenceJ][sequenceI]);
  //////Serial.print(", sequenceIsLeft[sequenceJ][sequenceI]: ");
  //////Serial.print(sequenceIsLeft[sequenceJ][sequenceI]);
  //////Serial.print(", sequenceI: ");
  ////////Serial.println(sequenceI);

  // Comment this out if using the randomized tug sequence code-block below.
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

  // Uncomment to enable a randomized tug sequence.
  /*
    if (isSequenceLeft) {
    motor.moveLeft();
    isSequenceLeft = false;
    } else {
    motor.moveRight();
    isSequenceLeft = true;
    timers[sequence].timeout = random(SEQUENCE_MIN, SEQUENCE_MAX);
    }
  */
  //////Serial.print(", timers[sequence].timeout: ");
  ////////Serial.println(timers[sequence].timeout);
}

void stopSoundTimer() {
  if (!isSoundTimerOn) {
    return;
  }
  isSoundTimerOn = false;
  ////Serial.print("stopSoundTimer() - timers[");
  ////Serial.print(sound);
  ////Serial.print("].total: ");
  ////Serial.print(timers[sound].total);
  timers[sound].total = 0L;
  digitalWrite(sounds[soundCurrent].pin, LOW);
  ////Serial.print(", sounds[");
  ////Serial.print(soundCurrent);
  ////Serial.print("].pin: ");
  //////Serial.println(digitalRead(sounds[soundCurrent].pin));
  soundCurrent = -1;
}

void stopToggleTimer() {
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
  //////Serial.print("stopToggleTimer() - timers[");
  //////Serial.print(toggle);
  //////Serial.print("].total: ");
  //////Serial.print(timers[toggle].total);
  timers[toggle].total = 0L;
  if (isReadyBlinking) {
    //////Serial.print(", isReadyBlinking: ");
    //////Serial.print(isReadyBlinking);
    //////Serial.print(", readyCounter: ");
    //////Serial.print(readyCounter);
    if (isToggleOn) {
      digitalWrite(pinLightReady, HIGH);
      ++readyCounter;
    } else {
      digitalWrite(pinLightReady, LOW);
      if (readyCounter == 3) {
        isReadyComplete = true;
      }
    }
  } else if (isWinnerLeftBlinking) {
    //////Serial.print(", isWinnerLeftBlinking: ");
    //////Serial.print(isWinnerLeftBlinking);
    if (isToggleOn) {
      //Serial.println("ON");
      digitalWrite(pinLightWinnerLeft, HIGH);
    } else {
      //Serial.println("OFF");
      digitalWrite(pinLightWinnerLeft, LOW);
    }
  } else if (isWinnerRightBlinking) {
    //////Serial.print(", isWinnerRightBlinking: ");
    //////Serial.print(isWinnerRightBlinking);
    if (isToggleOn) {
      digitalWrite(pinLightWinnerRight, HIGH);
    } else {
      digitalWrite(pinLightWinnerRight, LOW);
    }
  } else if (isChampionLeftBlinking) {
    //////Serial.print(", isChampionLeftBlinking: ");
    //////Serial.print(isChampionLeftBlinking);
    if (isToggleOn) {
      digitalWrite(pinLightChampionLeft, HIGH);
    } else {
      digitalWrite(pinLightChampionLeft, LOW);
    }

  } else if (isChampionRightBlinking) {
    //////Serial.print(", isChampionRightBlinking: ");
    //////Serial.print(isChampionRightBlinking);
    if (isToggleOn) {
      digitalWrite(pinLightChampionRight, HIGH);
    } else {
      digitalWrite(pinLightChampionRight, LOW);
    }
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    //////Serial.print(", isSuddenDeathLeftBlinking: ");
    //////Serial.print(isSuddenDeathLeftBlinking);
    //////Serial.print(", isSuddenDeathRightBlinking: ");
    //////Serial.print(isSuddenDeathRightBlinking);
    if (isToggleOn) {
      digitalWrite(pinLightSuddenDeathLeft, HIGH);
      digitalWrite(pinLightSuddenDeathRight, HIGH);
    } else {
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
    }
  }
  //////Serial.print(", isToggleOn: ");
  ////////Serial.println(isToggleOn);
  if (isToggleOn) {
    isToggleOn = false;
  } else {
    isToggleOn = true;
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

void stopTugSequence() {
  motor.moveStop();
  isSequenceOn = false;
  ////Serial.print("stopTugSequence() - timers[");
  ////Serial.print(sequence);
  ////Serial.print("].total: ");
  ////Serial.print(timers[sequence].total);
  ////Serial.print(", isSequenceOn: ");
  //////Serial.println(isSequenceOn);
  timers[sequence].total = 0L;
}

void stopStopTimer() {
  if (!isStopTimerOn) {
    return;
  }
  //////Serial.println("stopStopTimer() - ");
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
  //////Serial.println("stopReadyTimer() - ");
  timers[readySpecial].total = 0L;
  if (isReadyBlinking) {
    //////Serial.println(", isReadyBlinking");
    isReadyBlinking = false;
    digitalWrite(pinLightReady, LOW);
    digitalWrite(pinLightOne, HIGH);
    playSound(8);
    isOneOn = true;
    timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
    isReadyComplete = false;
    readyCounter = 0;
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
    if (hotButtons[start] == LOW && !buttonBlocks[start]) {
      buttonDebounces[start] += delta;
      if (buttonDebounces[start] > 10L) {
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
        ////Serial.println("$");
      }
    }
  } else if (isCentering) {
    if (hotSwitches[1] == LOW) {
      //////Serial.println("isCentering 1");
      motor.moveRight();
    } else if (hotSwitches[5] == LOW) {
      //////Serial.println("isCentering 5");
      motor.moveLeft();
    } else if (hotSwitches[3] == LOW) {
      //////Serial.println("isCentering 3");
      motor.moveStop();
      isCentering = false;
      isReset = true;
      //////Serial.println("########## NEW GAME ##########");
    }
  } else if (isTugOn) {

    if (hotButtons[player1Left] == LOW && !buttonBlocks[player1Left]) {
      buttonDebounces[player1Left] += delta;
      if (buttonDebounces[player1Left] > DEBOUNCE_TIME) {
        buttonBlocks[player1Left] = true;
        player1Taps[player1Index] = 0;
        ////Serial.print("player1Taps[");
        ////Serial.print(player1Index);
        ////Serial.print("] (L): ");
        ////Serial.println(player1Taps[player1Index]);
        ////Serial.print(", buttonDebounces[player1Left]: ");
        ////Serial.println(buttonDebounces[player1Left]);
        player1Index++;
      }
    } else if (hotButtons[player1Left] == HIGH && buttonBlocks[player1Left]) {
      buttonBlocks[player1Left] = false;
      buttonDebounces[player1Left] = 0;
    }

    if (hotButtons[player1Right] == LOW && !buttonBlocks[player1Right]) {
      buttonDebounces[player1Right] += delta;
      if (buttonDebounces[player1Right] > DEBOUNCE_TIME) {
        buttonBlocks[player1Right] = true;
        player1Taps[player1Index] = 1;
        ////Serial.print("player1Taps[");
        ////Serial.print(player1Index);
        ////Serial.print("] (R): ");
        ////Serial.println(player1Taps[player1Index]);
        ////Serial.print(", buttonDebounces[player1Index]:");
        ////Serial.println(buttonDebounces[player1Right]);
        player1Index++;
      }
    }
    else if (hotButtons[player1Right] == HIGH && buttonBlocks[player1Right]) {
      buttonBlocks[player1Right] = false;
      buttonDebounces[player1Right] = 0;
    }


    if (hotButtons[player2Left] == LOW && !buttonBlocks[player2Left]) {
      buttonDebounces[player2Left] += delta;
      if (buttonDebounces[player2Left] > DEBOUNCE_TIME) {
        buttonBlocks[player2Left] = true;
        player2Taps[player2Index] = 0;
        ////Serial.print("player2Taps[");
        ////Serial.print(player2Index);
        ////Serial.print("] (L): ");
        ////Serial.println(player2Taps[player2Index]);
        ////Serial.print(", buttonDebounces[player2Left]: ");
        ////Serial.println(buttonDebounces[player2Left]);
        player2Index++;
      }
    } else if (hotButtons[player2Left] && buttonBlocks[player2Left]) {
      buttonBlocks[player2Left] = false;
      buttonDebounces[player2Left] = 0;
    }

    if (hotButtons[player2Right] == LOW && !buttonBlocks[player2Right]) {
      buttonDebounces[player2Right] += delta;
      if (buttonDebounces[player2Right] > DEBOUNCE_TIME) {
        buttonBlocks[player2Right] = true;
        player2Taps[player2Index] = 1;
        ////Serial.print("player2Taps[");
        ////Serial.print(player2Index);
        ////Serial.print("] (R): ");
        ////Serial.println(player2Taps[player2Index]);
        ////Serial.print(", buttonDebounces[player1Right]: ");
        ////Serial.println(buttonDebounces[player2Right]);
        player2Index++;
      }
    } else if (hotButtons[player2Right] == HIGH && buttonBlocks[player2Right]) {
      buttonBlocks[player2Right] = false;
      buttonDebounces[player2Right] = 0;
    }

  } else if (currentSwitch == previousSwitch) {
    //////Serial.println("INPUT BLOCKED: same switch.");
  } else if ((isGameOver || isWinnerLeftBlinking || isWinnerRightBlinking || isChampionLeftBlinking || isChampionRightBlinking)
             && (!isSequenceOn)) {
    if (hotSwitches[1] == LOW && targets[1]) {
      //////Serial.println("REACHED TARGET 1");
      motor.moveStop();
      targets[1] = false;
      //isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //digitalWrite(pinLightWinnerLeft, LOW);
      isGameOver = false;
      timers[tenSecond].total = 0L;
    } else if (hotSwitches[2] == LOW && targets[2]) {
      //////Serial.println("REACHED TARGET 2");
      motor.moveStop();
      targets[2] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[3] == LOW && targets[3]) {
      //////Serial.println("REACHED TARGET 3");
      motor.moveStop();
      targets[3] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[4] == LOW && targets[4]) {
      //////Serial.println("REACHED TARGET 4");
      motor.moveStop();
      targets[4] = false;
      timers[fiveSecond].total = 0L; isFiveSecondTimerOn = true;
    } else if (hotSwitches[5] == LOW && targets[5]) {
      //////Serial.println("REACHED TARGET 5");
      motor.moveStop();
      targets[5] = false;
      //isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
      //digitalWrite(pinLightWinnerLeft, LOW);
      isGameOver = false;
      timers[tenSecond].total = 0L;
    }
  } else if (isSuddenDeathLeftBlinking || isSuddenDeathRightBlinking) {
    if (hotSwitches[3] == LOW && targets[3]) {
      motor.moveStop();
      targets[3] = false;
      digitalWrite(pinLightSuddenDeathLeft, LOW);
      digitalWrite(pinLightSuddenDeathRight, LOW);
    }
  }
}

void updateTimers() {
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0L) {
    Serial.println("LESS THAN ZERO");
    return;
  }
  if (current < previous) {
    Serial.println("LESS THAN PREVIOUS");
    return;
  }
  //Serial.println(current);
  debugTimer += delta;
  //Serial.println(debugTimer);
  if (debugTimer >= DEBUG_TIMEOUT) {
    Serial.println(current);
    debugTimer = 0L;
    digitalWrite(pinLightDebug, !digitalRead(pinLightDebug));
  }
  //Serial.println(millis());
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
  timers[sequence].total += delta;
  timers[toggle].total += delta;
  ////Serial.print(timers[sound].total);
  ////Serial.print(", ");
  ////Serial.print(timers[oneSecond].total);
  ////Serial.print(", ");
  ////Serial.print(timers[fiveSecond].total);
  ////Serial.print(", ");
  ////Serial.print(timers[tenSecond].total);
  ////Serial.print(", ");
  ////Serial.print(timers[stopSpecial].total);
  ////Serial.print(", ");
  ////Serial.print(timers[readySpecial].total);
  ////Serial.print(", ");
  ////Serial.print(timers[winnerSpecial].total);
  ////Serial.print(", ");
  ////Serial.print(timers[sequence].total);
  ////Serial.print(", ");
  //Serial.println(timers[toggle].total);
  ////Serial.println("");
}

void updateSwitches() {
  hotSwitches[0] = digitalRead(leftMax);
  hotSwitches[1] = digitalRead(left3);
  hotSwitches[2] = digitalRead(left1);
  hotSwitches[3] = digitalRead(center);
  hotSwitches[4] = digitalRead(right1);
  hotSwitches[5] = digitalRead(right3);
  hotSwitches[6] = digitalRead(rightMax);
}

void stopWinnerTimer() {
  if (!isWinnerTimerOn) {
    return;
  }
  isWinnerTimerOn = false;
  ////Serial.print("stopWinnerTimer() - ");
  ////Serial.print("timers[winnerSpecial].total: ");
  //////Serial.println(timers[winnerSpecial].total);
  timers[winnerSpecial].total = 0L;
  //if (isWinnerLeftBlinking || isWinnerRightBlinking) {
  ////////Serial.println(", isWinnerLeftBlinking or isWinnerRightBlinking");
  timers[toggle].total -= 200L;
  isToggleOn = true;
  timers[oneSecond].total = 0L; isOneSecondTimerOn = true;
  timers[fiveSecond].total = 0L;
  //timers[fiveSecond].total -= 5000L;
  isFiveSecondTimerOn = true;
  if (hotSwitches[2] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[3] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[4] == LOW) {
    isReadyBlinking = true; timers[fiveSecond].timeout = 2500L; isReadyTimerOn = true; timers[readySpecial].total = 0L;// digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
    playSound(ready);
    if (isChampionLeftBlinking || isChampionRightBlinking) {
      isReadyBlinking = false;
      digitalWrite(pinLightReady, LOW);
    }
  } else if (hotSwitches[1] == LOW) {
    isChampionLeftBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
  } else if (hotSwitches[5] == LOW) {
    isChampionRightBlinking = true; digitalWrite(pinLightSuddenDeathLeft, LOW); digitalWrite(pinLightSuddenDeathRight, LOW);
  }
  digitalWrite(pinLightWinnerLeft, LOW);
  digitalWrite(pinLightWinnerRight, LOW);
  isWinnerLeftBlinking = false;
  isWinnerRightBlinking = false;
  //}
}

void randomWinner() {
  ////Serial.println("---");
  ////Serial.println(player1Score == player2Score);
  ////Serial.println(player1Index > 0);
  ////Serial.println(player2Index > 0);
  int randomNumber = random(0, 1);
  ////Serial.println();
  if (player1Score == player2Score && player1Index > 0 && player2Index > 0) {
    if (randomNumber == 0) {
      if (random(0, 1) == 0) {
        player1Score = 1;
        player2Score = 0;
      } else {
        player1Score = 0;
        player2Score = 1;
      }
    }
  }
}
