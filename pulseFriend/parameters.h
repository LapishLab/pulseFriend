//// All parameter times are in microseconds, but I've defined larger time units for your convenience.
// Use them like this: session1.pulseDur = 1*ms;
const byte us = 1;
const unsigned int ms = 1000;
const unsigned long s = ms*1000;
const unsigned long minute = s*60;

//// Define a structure to hold session parameters and set default values ////
struct Params {
  int pulseDur = 200*us;
  int pulseDelay = 400*ms; 
  int pulseRepeats = 10;
  int trainDelay = 2*s;
  int trainRepeats = 2;
  int widePulseDur = 200*ms; //Actually implemented as additional time on top of pulse duration
};

//// Create an instance for each session
Params session1;
Params session2;
Params session3;
Params session4;


////////////// Define custom parameters for each setting ///////////////////////////////
void loadSettings(){

  /// Session 1 ///
  session1.pulseDur = 1;

  /// Session 2 ///

  /// Session 3 ///

  /// Session 4 ///
  
}
