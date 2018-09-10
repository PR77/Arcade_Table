#include <Arduino.h>
#include <Metro.h>

#define LED_DRIVE_OUTPUT  1

typedef enum {
  slowFlashSingle = 0,
  slowFlashMultiple,
  slowFlashRandom,
  fastFlashSingle,
  fastFlashMultiple,
  fastFlashRandom,
  fadeOnFadeOff,
  fadeOnFastOff,
  fastOnFadeOff,
  determineNextPattern
} ledPattern_t;

typedef enum {
  fadeOn = 0,
  fadeOff,
  fastOn,
  fastOff,
  multipleFlash,
  holdDelay
} subLedPattern_t;

typedef enum {
  patternNotYetRunning = 0,
  patternRunning,
  patternDone
} patternHandlerState_t;

patternHandlerState_t flashHandler(byte flashCount, byte *outputState);
patternHandlerState_t fadeOnHandler(byte *outputState);
patternHandlerState_t fastOnHandler(byte *outputState);
patternHandlerState_t fadeOffHandler(byte *outputState);
patternHandlerState_t fastOffHandler(byte *outputState);

Metro slowTimer = Metro(250);
Metro fastTimer = Metro(125);
Metro fadeTimer = Metro(5);
Metro holdTimer = Metro(500);

patternHandlerState_t flashHandler(byte flashCount, byte *outputState) {
  static patternHandlerState_t patternHandlerState = patternNotYetRunning;
  static byte currentFlashCount = 0;
  static boolean intermediateCycle = false;

  if (patternNotYetRunning == patternHandlerState) {
    currentFlashCount = 0;
    intermediateCycle = false;
    patternHandlerState = patternRunning;
  }
  else if (patternRunning == patternHandlerState) {
    if ((currentFlashCount < flashCount) && (false == intermediateCycle)) {
      intermediateCycle = true;
      *outputState = 255;
    }
    else if ((currentFlashCount < flashCount) && (true == intermediateCycle)) {
      intermediateCycle = false;
      currentFlashCount++;
      *outputState = 0;
    }
  }

  if (currentFlashCount == flashCount) {
    patternHandlerState = patternDone;
  }

  if (patternDone == patternHandlerState) {
    patternHandlerState = patternNotYetRunning;
    return (patternDone);
  }

  return (patternHandlerState);
}

patternHandlerState_t fadeOnHandler(byte *outputState) {
  static patternHandlerState_t patternHandlerState = patternNotYetRunning;
  static byte currentOutputState = 0;

  if (patternNotYetRunning == patternHandlerState) {
    currentOutputState = 0;
    *outputState = 0;
    patternHandlerState = patternRunning;
  }
  else if (patternRunning == patternHandlerState) {
    if (255 == ++currentOutputState) {
      patternHandlerState = patternDone;
    }
    *outputState = currentOutputState;
  }

  if (patternDone == patternHandlerState) {
    patternHandlerState = patternNotYetRunning;
    return (patternDone);
  }

  return (patternHandlerState);
}

patternHandlerState_t fastOnHandler(byte *outputState) {
  static patternHandlerState_t patternHandlerState = patternNotYetRunning;

  if (patternNotYetRunning == patternHandlerState) {
    *outputState = 255;
    patternHandlerState = patternDone;
  }

  if (patternDone == patternHandlerState) {
    patternHandlerState = patternNotYetRunning;
    return (patternDone);
  }

  return (patternHandlerState);
}

patternHandlerState_t fadeOffHandler(byte *outputState) {
  static patternHandlerState_t patternHandlerState = patternNotYetRunning;
  static byte currentOutputState = 0;

  if (patternNotYetRunning == patternHandlerState) {
    currentOutputState = 255;
    *outputState = 255;
    patternHandlerState = patternRunning;
  }
  else if (patternRunning == patternHandlerState) {
    if (0 == --currentOutputState) {
      patternHandlerState = patternDone;
    }
    *outputState = currentOutputState;
  }

  if (patternDone == patternHandlerState) {
    patternHandlerState = patternNotYetRunning;
    return (patternDone);
  }

  return (patternHandlerState);
}

patternHandlerState_t fastOffHandler(byte *outputState) {
  static patternHandlerState_t patternHandlerState = patternNotYetRunning;

  if (patternNotYetRunning == patternHandlerState) {
    *outputState = 0;
    patternHandlerState = patternDone;
  }

  if (patternDone == patternHandlerState) {
    patternHandlerState = patternNotYetRunning;
    return (patternDone);
  }

  return (patternHandlerState);
}

void setup() {
  pinMode(LED_DRIVE_OUTPUT, OUTPUT);
}

void loop() {
  ledPattern_t ledPattern = determineNextPattern;
  subLedPattern_t subLedPattern = fadeOn;
  byte ledDriveValue = 0, previousLedDriveValue = 0, randomFlashCount;
  int i;

  randomFlashCount = random() % 16;

  while (1) {
    switch (ledPattern) {
      case (slowFlashSingle):
        if (slowTimer.check()) {
          if (patternDone == flashHandler(1, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (slowFlashMultiple):
        if (slowTimer.check()) {
          if (patternDone == flashHandler(3, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (slowFlashRandom):
        if (slowTimer.check()) {
          if (patternDone == flashHandler(randomFlashCount, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (fastFlashSingle):
       if (fastTimer.check()) {
          if (patternDone == flashHandler(1, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (fastFlashMultiple):
        if (fastTimer.check()) {
          if (patternDone == flashHandler(9, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (fastFlashRandom):
        if (fastTimer.check()) {
          if (patternDone == flashHandler(randomFlashCount, &ledDriveValue)) {
            ledPattern = determineNextPattern;
          }
        }
        break;

      case (fadeOnFadeOff):
        if (fadeTimer.check()) {
          switch (subLedPattern) {
            case (fadeOn):
              if (patternDone == fadeOnHandler(&ledDriveValue)) {
                holdTimer.reset();
                subLedPattern = holdDelay;
              }
              break;
            case (holdDelay):
              if (holdTimer.check()) {
                subLedPattern = fadeOff;
              }
              break;
            case (fadeOff):
              if (patternDone == fadeOffHandler(&ledDriveValue)) {
                ledPattern = determineNextPattern;
                subLedPattern = fadeOn;
              }
              break;
          }
        }
        break;

      case (fadeOnFastOff):
        if (fadeTimer.check()) {
          switch (subLedPattern) {
            case (fadeOn):
              if (patternDone == fadeOnHandler(&ledDriveValue)) {
                holdTimer.reset();
                subLedPattern = holdDelay;
              }
              break;
            case (holdDelay):
              if (holdTimer.check()) {
                subLedPattern = fadeOff;
              }
              break;
            case (fadeOff):
              if (patternDone == fastOffHandler(&ledDriveValue)) {
                ledPattern = determineNextPattern;
                subLedPattern = fadeOn;
              }
              break;
          }
        }
        break;

      case (fastOnFadeOff):
        if (fadeTimer.check()) {
          switch (subLedPattern) {
            case (fadeOn):
              if (patternDone == fastOnHandler(&ledDriveValue)) {
                holdTimer.reset();
                subLedPattern = holdDelay;
              }
              break;
            case (holdDelay):
              if (holdTimer.check()) {
                subLedPattern = fadeOff;
              }
              break;
            case (fadeOff):
              if (patternDone == fadeOffHandler(&ledDriveValue)) {
                ledPattern = determineNextPattern;
                subLedPattern = fadeOn;
              }
              break;
          }
        }
        break;

      case (determineNextPattern):
        slowTimer.reset();
        fastTimer.reset();
        fadeTimer.reset();
        i = random() % 9;
        ledPattern = (ledPattern_t)i;
        break;
    }

    if (previousLedDriveValue != ledDriveValue) {
      previousLedDriveValue = ledDriveValue;
      analogWrite(LED_DRIVE_OUTPUT, ledDriveValue);
    }
  }
}
