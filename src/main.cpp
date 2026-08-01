#include "SunTracker.h"

SunTracker suntracker(A0,A1,A2,A3,5,3);

void setup() {
  Serial.begin(115200);
  
}

void loop() {
  //uint16_t bl, br, tl, tr = suntracker.getPhotoresistorsValues();

  //suntracker.trackHorizontal(200,30);
  suntracker.measurePhotoresistorsValues();

  Serial.print(">Bottom Left:");
  Serial.println(suntracker.pr_BottomLeft_val);

  Serial.print(">Bottom Right:");
  Serial.println(suntracker.pr_BottomRight_val);

  Serial.print(">Top Left:");
  Serial.println(suntracker.pr_TopLeft_val);

  Serial.print(">Top Right:");
  Serial.println(suntracker.pr_TopRight_val);

  

  delay(1000);


}


