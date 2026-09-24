#include "SunTracker.h"

SunTracker suntracker(A0,A1,A2,A3,5,3);

void setup() {
  Serial.begin(115200);
  suntracker.initializeServos();
  suntracker.setPosition(180,180);
  
  
}

void loop() {

  // threshold = 200, top servo value = 120
  //suntracker.trackHorizontal(200,120);

  suntracker.trackDualAxis(100);
  

  suntracker.infoPrint();
  
  

  delay(20);
}


