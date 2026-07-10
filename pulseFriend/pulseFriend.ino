#include "parameters.h"

// Pins
const int startButtonPin = 2;
const int outPin = 8;       // TTL command pulse to WPI A365
const int outWidePin = 9;   // ephys trigger/gate covering the monophasic pulse

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
    Serial.println("---- Running stimulation protocol ----");

    runStim(session1);

    Serial.println("---- Stimulation protocol finished ----");

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
  while (t >= ms) {
    delay(1);
    t -= ms;
  }

  if (t > 0) {
    delayMicroseconds(t);
  }
}

void runStim(Params params) {
  for (unsigned int i = 0; i < params.trainRepeats; i++) {
    Serial.print("Running Train #");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.println(params.trainRepeats);

    runTrain(params);

    // Idle only between trains, not after the final train
    if (i < params.trainRepeats - 1) {
      Serial.println("Idling between trains...");
      flexibleDelay(params.trainDelay);
    }
  }
}

void runTrain(Params params) {
  for (unsigned int i = 0; i < params.pulseRepeats; i++) {
    if (params.shouldPrintPulse) {
      Serial.print("Running monophasic pulse #");
      Serial.print(i + 1);
      Serial.print("/");
      Serial.println(params.pulseRepeats);
    }

    // Monophasic command pulse.
    // Pin 8 HIGH sends the command pulse to the A365.
    // Pin 9 HIGH opens the ephys gate for the same duration.
    PORTB = B00000011;   // Turn on pin 8 and pin 9
    flexibleDelay(params.pulseDur);

    // End the pulse and close the ephys gate.
    PORTB = B00000000;   // Turn off pin 8 and pin 9

    // Quiet interval. pulseDur + idlePeriod = stimPeriod.
    // At 25 kHz sampling: 3 samples + 247 samples = 250 samples.
    flexibleDelay(params.idlePeriod);
  }
}

void loadSettings() {
  // Currently no extra settings need to be loaded.
  // session1 already uses the default values from parameters.h.
}