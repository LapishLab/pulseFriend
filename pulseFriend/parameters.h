//// All parameter times are in microseconds, but I've defined larger time units for your convenience.
// Use them like this: session1.pulseDur = 1*ms;
const unsigned long us = 1;
const unsigned long ms = 1000;
const unsigned long s = ms*1000;
const unsigned long minute = s*60;

//// Define a structure to hold session parameters and set default values ////
struct Params {
  unsigned long pulseDur = 200*us;
  unsigned long pulseDelay = 20*s; 
  byte pulseRepeats = 60;
  unsigned long trainDelay = 0*s;
  byte trainRepeats = 1;
  unsigned long widePulseDur = 100*ms; //This needs to be equal or longer than pulseDur or you will get weird results
};

//// Create an instance for each session
Params session1;
Params session2;
Params session3;
Params session4;
Params session5;


////////////// Define custom parameters for each setting ///////////////////////////////
void loadSettings(){

  /// Session 1 ///
  //session1.pulseDur = 100*ms;

  /// Session 2 ///
  session2.pulseRepeats = 90;

  /// Session 3 ///
  session3.pulseDelay = 3800*us;
  session3.pulseRepeats = 50;
  session3.trainDelay = 10*s;
  session3.trainRepeats = 10;

  //pause for 10minutes

  /// Session 4 ///
  session4.pulseDelay =3800*us;
  session4.pulseRepeats = 50;
  session4.trainDelay = 10*s;
  session4.trainRepeats = 10;

  /// Session 5 ///
  session5.pulseRepeats = 100; 
  
}
