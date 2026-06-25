#ifndef PARAMETERS_H
#define PARAMETERS_H

const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms * 1000;
const unsigned long minute = s * 60;

struct Params {
  unsigned long pulseDur = 60 * us;
  unsigned long interPhaseGap = 10 * us;
  unsigned long pulsePeriod = 9870 * us;
  unsigned long widePulseDur = 130 * us;

  unsigned int pulseRepeats = 1000;
  unsigned long trainDelay = 0 * ms;
  unsigned int trainRepeats = 1;
  bool shouldPrintPulse = false;
};

Params session1;

#endif