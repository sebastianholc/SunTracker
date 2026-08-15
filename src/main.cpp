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

  suntracker.trackDualAxis(200);
  

  // Serial.print(">Top Left:");
  // Serial.println(suntracker.pr_TopLeft_val);

  // Serial.print(">Top Right:");
  // Serial.println(suntracker.pr_TopRight_val);

  // Serial.print(">Bottom Left:");
  // Serial.println(suntracker.pr_BottomLeft_val);

  // Serial.print(">Bottom Right:");
  // Serial.println(suntracker.pr_BottomRight_val);

  // Serial.print(">Servo steer value:");
  // Serial.println(suntracker.servo_bottom_steer_val);
  
  

  delay(20);
}


