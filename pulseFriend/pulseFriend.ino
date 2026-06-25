#include "parameters.h"

// Pins
const int startButtonPin = 2;
const int outPin = 8;       // TTL command pulse to WPI A365
const int outWidePin = 9;   // wider pulse, for ephys trigger/gate

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");

  pinMode(outPin, OUTPUT);
  pinMode(outWidePin, OUTPUT);
  pinMode(startButtonPin, INPUT);

  digitalWrite(outPin, LOW);
  digitalWrite(outWidePin, LOW);

  loadSettings();

  Serial.println("Setup finished");
}

void loop() {
  if (buttonIsPressed()) {
    Serial.println("Button pressed!");
    Serial.println("---- Running biphasic pulse train ----");

    runStim(session1);

    Serial.println("---- Pulse train finished ----");

    // Prevent repeated stimulation while button is still held down
    while (buttonIsPressed()) {
      delay(10);
    }
  }
}

bool buttonIsPressed() {
  int buttonState = digitalRead(startButtonPin);
  return buttonState == HIGH;
}

void flexibleDelay(unsigned long t) {
  if (t < 4000) {
    delayMicroseconds(t);
  } else {
    delay(t / ms);
  }
}

void runStim(Params params) {
  for (unsigned int i = 0; i < params.trainRepeats; i++) {
    Serial.print("Running Train #");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.println(params.trainRepeats);

    runTrain(params);

    flexibleDelay(params.trainDelay);
  }
}

void runTrain(Params params) {
  for (unsigned int i = 0; i < params.pulseRepeats; i++) {
    if (params.shouldPrintPulse) {
      Serial.print("Running biphasic pulse pair #");
      Serial.print(i + 1);
      Serial.print("/");
      Serial.println(params.pulseRepeats);
    }

    // Phase 1
    // Pin 8 HIGH sends command pulse to A365.
    // Pin 9 HIGH opens the wider ephys gate.
    PORTB = B00000011;   // Turn on pin 8 and pin 9
    flexibleDelay(params.pulseDur);

    // Inter-phase gap
    // Pin 8 LOW, pin 9 remains HIGH.
    PORTB = B00000010;   // Turn off pin 8, keep pin 9 on
    flexibleDelay(params.interPhaseGap);

    // Phase 2
    // In A365 Bipolar mode, this second command pulse should produce the opposite polarity.
    PORTB = B00000011;   // Turn on pin 8 and pin 9
    flexibleDelay(params.pulseDur);

    // End of biphasic pair
    PORTB = B00000000;   // Turn off pin 8 and pin 9

    // Delay after the biphasic pair.
    // 60 us + 10 us + 60 us + 9870 us = 10 ms total from phase-1 start to next phase-1 start.
    flexibleDelay(params.pulsePeriod);
  }
}