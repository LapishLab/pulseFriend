#ifndef PARAMETERS_H
#define PARAMETERS_H

const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms * 1000;

struct Params {
  unsigned long pulseDur = 60 * us;
  unsigned long interPhaseGap = 10 * us;
  unsigned long pulsePeriod = 9870 * us; // 10 ms - 60 us - 10 us - 60 us
  unsigned long widePulseDur = 130 * us; // ephys gate duration covering the full biphasic pair: 60 us + 10 us + 60 us

  unsigned int pulseRepeats = 1000;
  unsigned long trainDelay = 0 * ms;
  unsigned int trainRepeats = 1;
  bool shouldPrintPulse = false;
};

Params session1;

// Function declaration
void loadSettings();

#endif