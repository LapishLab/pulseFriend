//// All parameter times are in microseconds, but I've defined larger time units for your convenience.
// Use them like this: session1.pulseDur = 1*ms;
const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms*1000;
const unsigned long minute = s*60;

//// Define a structure to hold session parameters and set default values ////
struct Params {
  unsigned long pulseDur = 200*us;
  unsigned long pulseDelay = 1000*ms; 
  byte pulseRepeats = 1;
  unsigned long trainDelay = 0*s;
  byte trainRepeats = 1;
  unsigned long widePulseDur = 10*ms; //This needs to be equal or longer than pulseDur or you will get weird results
};

//// Create an instance for each session
Params session1;


////////////// Define custom parameters for each setting ///////////////////////////////
void loadSettings(){

  
}
