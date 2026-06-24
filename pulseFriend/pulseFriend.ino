#include "parameters.h"

// Pins
const int startButtonPin = 2;
const int outPin = 8; 
const int outWidePin = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");

  pinMode(outPin, OUTPUT);
  pinMode(outWidePin, OUTPUT);
  pinMode(startButtonPin, INPUT);

  loadSettings();

  Serial.println("Setup finished");
}

void loop() {
  if (buttonIsPressed()) {
    Serial.println("Button pressed!");
    Serial.println("---- Running simple 10-second pulse train ----");

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
      Serial.print("Running pulse #");
      Serial.print(i + 1);
      Serial.print("/");
      Serial.println(params.pulseRepeats);
    }

    PORTB = B00000011; // Turn on pin 8 and pin 9
    flexibleDelay(params.pulseDur);

    PORTB = B00000010; // Turn off pin 8, keep pin 9 on
    flexibleDelay(params.widePulseDur - params.pulseDur);

    PORTB = B00000000; // Turn off pin 9

    // Wait until the next pulse start
    flexibleDelay(params.pulseDelay - params.widePulseDur);
  }
}