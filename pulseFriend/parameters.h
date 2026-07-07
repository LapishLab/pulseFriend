#ifndef PARAMETERS_H
#define PARAMETERS_H

const unsigned long us = 1;
const unsigned long ms = us * 1000;
const unsigned long s = ms * 1000;

struct Params {
  unsigned long sampleRate = 25000; // Hz
  unsigned long samplePeriod = s / sampleRate; // 40 us at 25 kHz

  unsigned long stimFreq = 100; // Hz
  unsigned long stimPeriod = s / stimFreq; // 10000 us at 100 Hz

  unsigned long pulseDur = 3 * samplePeriod;       // 3 samples = 120 us
  unsigned long interPhaseGap = 1 * samplePeriod;  // 1 sample = 40 us

  unsigned long biphasicPulseDur = 2 * pulseDur + interPhaseGap; // 7 samples = 280 us
  unsigned long idlePeriod = stimPeriod - biphasicPulseDur;

  unsigned long ephysGateDur = biphasicPulseDur; // gate covers full biphasic pulse

  unsigned long trainDur = 2 * s; // 2 seconds
  unsigned int pulseRepeats = stimFreq * (trainDur / s); // number of pulses in 2 s

  unsigned long trainDelay = 0 * ms;
  unsigned int trainRepeats = 1;
  bool shouldPrintPulse = false;
};

Params session1;

// Function declaration
void loadSettings();

#endif