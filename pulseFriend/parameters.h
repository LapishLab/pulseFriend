//// All parameter times are in microseconds, but I've defined larger time units for your convenience.
// Use them like this: session1.pulseDur = 1*ms;
const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms*1000;
const unsigned long minute = s*60;

//// Define a structure to hold session parameters and set default values ////
struct Params {
  unsigned long pulseDur = 200*us;
  unsigned long pulseDelay = 500*ms; 
  byte pulseRepeats = 5;
  unsigned long trainDelay = 1*s;
  byte trainRepeats = 2;
  unsigned long widePulseDur = 100*ms; //Actually implemented as additional time on top of pulse duration
};

//// Create an instance for each session
Params session1;
Params session2;
Params session3;
Params session4;


////////////// Define custom parameters for each setting ///////////////////////////////
void loadSettings(){

  /// Session 1 ///
  session1.pulseDur = 100*ms;

  /// Session 2 ///
  session2.pulseRepeats = 10;

  /// Session 3 ///

  /// Session 4 ///
  
}
