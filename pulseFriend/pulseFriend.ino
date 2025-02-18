
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
    Serial.println("---- Session 1 (Baseline pre-injection)----");
    runStim(session1);
    Serial.println("---- GIVE INJECTION!!!!!----");
    flexibleDelay(20*s);
    Serial.println("---- Session 2 (Baseline post-injection)----");
    runStim(session2);
    Serial.println("---- Session 3 (High-frequency #1) ----");
    runStim(session3);

    Serial.println("---- Waiting for 10 minutes ----");
    flexibleDelay(10*minute);

    Serial.println("---- Session 4 (High-frequency #2) ----");
    runStim(session4);
    Serial.println("---- Session 5 (Test post-high-frequency) ----");
    runStim(session5);
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
    Serial.print("    Running Train #"); Serial.print(i+1); Serial.print("/");Serial.println(params.trainRepeats);
    runTrain(params);
    flexibleDelay(params.trainDelay);
  }
}

void runTrain(Params params) {
  for (int i=0; i<params.pulseRepeats; i++){
    if (params.shouldPrintPulse){
      Serial.print("        Running pulse #"); Serial.print(i+1); Serial.print("/");Serial.println(params.pulseRepeats);
    }
    PORTB = B00000011; // Turn on pin 8 and 9 (direct port manipulation)
    flexibleDelay(params.pulseDur);
    PORTB = B00000010; // turn off pin 8 (direct port manipulation)
    flexibleDelay(params.widePulseDur-params.pulseDur);
    PORTB = B00000000; // turn off pin 9 (direct port manipulation)
    //flexibleDelay(params.pulseDelay);// Not what we really want. Actually want to start wait timer after the end of the short pulse.  
    flexibleDelay(params.pulseDelay+params.pulseDur-params.widePulseDur); //Need to make sure pulseDelay is bigger than wide PulseDur
  }
}
