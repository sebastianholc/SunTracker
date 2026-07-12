#include "SunTracker.h"

SunTracker suntracker(A0,A1,A2,A3,5,3);

void setup() {
  
}

void loop() {
  uint16_t bl, br, tl, tr = suntracker.getPhotoresistorsValues();

  suntracker.trackHorizontal(200);

  delay(1000);


}


