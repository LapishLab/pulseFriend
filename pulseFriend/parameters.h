//// All parameter times are in microseconds, but I've defined larger time units for your convenience.
// Use them like this: session1.pulseDur = 1*ms;
const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms*1000;
const unsigned long minute = s*60;

struct Params {
  unsigned long pulseDur = 20*us;       // pulse to trigger the stimulator
  unsigned long widePulseDur = 50*us;   // pulse to open ephys
  unsigned long pulseDelay = 10*ms;     // interpulse interval
  unsigned int pulseRepeats = 1000;     // total number of pulses
  unsigned long trainDelay = 0*ms;
  unsigned int trainRepeats = 1;
  bool shouldPrintPulse = false;
};

Params session1;


void loadSettings(){
  session1.pulseDur = 20*us;
  session1.widePulseDur = 50*us;
  session1.pulseDelay = 10*ms;
  session1.pulseRepeats = 1000;
  session1.trainDelay = 0*ms;
  session1.trainRepeats = 1;
  session1.shouldPrintPulse = false;
}