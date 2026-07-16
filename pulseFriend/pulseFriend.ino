#include "parameters.h"

// Pins (Arduino Uno/Nano ATmega328P)
const uint8_t startButtonPin = 2;
const uint8_t outPin = 8;       // TTL command to WPI A365 (PORTB bit 0)
const uint8_t outWidePin = 9;   // Ephys gate for the full biphasic pulse (PORTB bit 1)

// Direct-port masks for pins 8 and 9.
const uint8_t commandMask = _BV(PB0);
const uint8_t gateMask = _BV(PB1);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");

  pinMode(outPin, OUTPUT);
  pinMode(outWidePin, OUTPUT);
  pinMode(startButtonPin, INPUT);

  PORTB &= ~(commandMask | gateMask);

  loadSettings();

  Serial.print("Stim frequency: ");
  Serial.print(session1.stimFreq);
  Serial.println(" Hz");
  Serial.print("Pulses per train: ");
  Serial.println(session1.pulseRepeats);
  Serial.print("Train duration: ");
  Serial.print(session1.trainDur / 1000.0);
  Serial.println(" ms");
  Serial.println("Setup finished");
}

void loop() {
  if (buttonIsPressed()) {
    Serial.println("Button pressed!");
    Serial.println("---- Running stimulation protocol ----");

    runStim(session1);

    Serial.println("---- Stimulation protocol finished ----");

    // Prevent repeated stimulation while the button remains pressed.
    while (buttonIsPressed()) {
      delay(10);
    }
  }
}

bool buttonIsPressed() {
  return digitalRead(startButtonPin) == HIGH;
}

// Handles delays longer than delayMicroseconds() reliably accepts.
void flexibleDelay(uint32_t durationUs) {
  if (durationUs >= 1000UL) {
    delay(durationUs / 1000UL);
    durationUs %= 1000UL;
  }

  if (durationUs > 0) {
    delayMicroseconds(durationUs);
  }
}

// Wait until an absolute micros() timestamp. Signed subtraction makes this
// safe across micros() rollover, provided waits are shorter than ~35 minutes.
void waitUntil(uint32_t targetTimeUs) {
  while ((int32_t)(micros() - targetTimeUs) < 0) {
    // Busy wait for precise pulse timing.
  }
}

void runStim(const Params &params) {
  for (uint16_t train = 0; train < params.trainRepeats; ++train) {
    Serial.print("Running Train #");
    Serial.print(train + 1);
    Serial.print("/");
    Serial.println(params.trainRepeats);

    runTrain(params);

    // Idle only between trains, not after the final train.
    if (train + 1 < params.trainRepeats) {
      Serial.println("Idling between trains...");
      flexibleDelay(params.trainDelay);
    }
  }
}

void runTrain(const Params &params) {
  const uint32_t trainStartUs = micros();
  const uint32_t trainEndUs = trainStartUs + params.trainDur;

  for (uint32_t pulse = 0; pulse < params.pulseRepeats; ++pulse) {
    // Schedule every onset from the original train start. This prevents
    // execution time and delay rounding from accumulating across pulses.
    const uint32_t pulseStartUs = trainStartUs + pulse * params.stimPeriod;
    waitUntil(pulseStartUs);

    if (params.shouldPrintPulse) {
      Serial.print("Running biphasic pulse #");
      Serial.print(pulse + 1);
      Serial.print("/");
      Serial.println(params.pulseRepeats);
    }

    // Keep the ephys gate HIGH for both phases and the inter-phase gap.
    PORTB |= gateMask;

    // Phase 1 command pulse.
    PORTB |= commandMask;
    flexibleDelay(params.pulseDur);
    PORTB &= ~commandMask;

    // Inter-phase gap.
    flexibleDelay(params.interPhaseGap);

    // Phase 2 command pulse.
    // This produces a second TTL command pulse. Actual polarity reversal must
    // be configured in the stimulator or implemented with separate hardware.
    PORTB |= commandMask;
    flexibleDelay(params.pulseDur);
    PORTB &= ~commandMask;

    // Close the ephys gate after the complete biphasic event.
    PORTB &= ~gateMask;
  }

  // Keep the train boundary fixed at trainDur (2 s by default).
  waitUntil(trainEndUs);
}

void loadSettings() {
  // Recalculate every value derived from stimFreq, sampleRate, or trainDur.
  // This guarantees consistency after changing a base value in parameters.h.
  session1.samplePeriod = s / session1.sampleRate;
  session1.stimPeriod = s / session1.stimFreq;
  session1.pulseDur = 3UL * session1.samplePeriod;
  session1.interPhaseGap = session1.samplePeriod;
  session1.biphasicPulseDur =
      2UL * session1.pulseDur + session1.interPhaseGap;
  session1.ephysGateDur = session1.biphasicPulseDur;

  // Use 64-bit arithmetic so multiplication cannot overflow first.
  session1.pulseRepeats =
      (uint32_t)(((uint64_t)session1.stimFreq * session1.trainDur) / s);

  // A stimulation event must fit inside one stimulation period.
  if (session1.biphasicPulseDur >= session1.stimPeriod) {
    Serial.println("ERROR: biphasic pulse duration must be shorter than stimPeriod.");
    session1.idlePeriod = 0;
  } else {
    session1.idlePeriod = session1.stimPeriod - session1.biphasicPulseDur;
  }
}
