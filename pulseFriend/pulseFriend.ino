// User Settings %%
const int pulseDur = 200; // In microseconds
const int pulseDelay = 400; 
const int pulseRepeats = 10;
const int trainDelay = 2000;
const int trainRepeats = 2;

// Developer Settings %%
const int widePulseDur = 200; //Currently additional time on top of pulse duration

// Pins
const int startButtonPin = 53;
//const int stopButtonPin = 2;
const int outPin = 45; 
const int outWidePin = 43;

// State
// bool shouldContinue = TRUE

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");
  pinMode(outPin, OUTPUT);
  pinMode(outWidePin, OUTPUT);
  pinMode(startButtonPin, INPUT);
  Serial.println("Setup finished");
}

void loop() {
  if (buttonIsPressed()) {
    Serial.println("Button pressed!, running stim");
    runStim();
  }
}

bool buttonIsPressed() {
  int buttonState = digitalRead(startButtonPin);
  return buttonState == HIGH;
}

void runStim() {
  for (int i=0; i<trainRepeats; i++){
    Serial.print("Running Train #"); Serial.print(i+1); Serial.print("/");Serial.println(trainRepeats);
    runTrain();
    delay(trainDelay);
  }
}

void runTrain() {
  for (int i=0; i<pulseRepeats; i++){
    Serial.print("Running pulse #"); Serial.print(i+1); Serial.print("/");Serial.println(pulseRepeats);

    // This is just to trigger the oscilloscipe ///
    digitalWrite(outPin, HIGH);
    delay(5);
    digitalWrite(outPin, LOW);
    delayMicroseconds(200);
    //////////////////////////////////////////////
    digitalWrite(outPin, HIGH);
    digitalWrite(outWidePin, HIGH);
    delayMicroseconds(pulseDur);
    digitalWrite(outPin, LOW);
    delay(widePulseDur);
    digitalWrite(outWidePin, LOW);
    delay(pulseDelay);
  }
}
