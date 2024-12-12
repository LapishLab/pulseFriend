
#include "parameters.h"

// Pins
const int startButtonPin = 2;
const int outPin = 8; 
const int outWidePin = 9;

// State
// bool shouldContinue = TRUE

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
    Serial.println("running session1");
    runStim(session1);
    Serial.println("running session2");
    runStim(session2);
    Serial.println("running session3");
    runStim(session3);
    Serial.println("running session4");
    runStim(session4);
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
    delay(t/ms);
  }
}

void runStim(Params params) {
  for (int i=0; i<params.trainRepeats; i++){
    Serial.print("Running Train #"); Serial.print(i+1); Serial.print("/");Serial.println(params.trainRepeats);
    runTrain(params);
    flexibleDelay(params.trainDelay);
  }
}

void runTrain(Params params) {
  for (int i=0; i<params.pulseRepeats; i++){
    Serial.print("Running pulse #"); Serial.print(i+1); Serial.print("/");Serial.println(params.pulseRepeats);
    digitalWrite(outPin, HIGH);
    digitalWrite(outWidePin, HIGH);
    flexibleDelay(params.pulseDur);
    digitalWrite(outPin, LOW);
    flexibleDelay(params.widePulseDur);
    digitalWrite(outWidePin, LOW);
    flexibleDelay(params.pulseDelay);
  }
}
